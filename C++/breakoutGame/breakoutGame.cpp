#include <iostream>
#include <sstream>
#include <cstdlib>
#include <sys/time.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <vector>
#include <string.h>

using namespace std;

int BufferSize = 10;
int bricks_size = 60;
int FPS = 60;
int screen_x = 1280;
int screen_y = 800;
bool startPlay = false;
int score = 0;
int speed = 6;

struct XInfo {
  Display	*display;
  Window	window;
  Pixmap	pixmap;
  GC            gc[8];
  int		screen;
  int		width;		
  int		height;
  int           ball_speed;
};

unsigned long now() {
  timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}

class Displayable {
public:
  virtual void paint(XInfo &xinfo) = 0; 
};       

class Splash : public Displayable {
public:
  bool first;
  int box_width;
  int box_height;
  int x; 
  int y; 
  virtual void paint(XInfo &xinfo) {   
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[1], x, 150, "Instruction:", strlen("Instruction:"));
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[1], x, 200, "1. Use LEFT/RIGHT arrow to move paddle", strlen("1. Use LEFT/RIGHT arrow to move paddle"));
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[1], x, 250, "2. Press SPACE BAR to release ball", strlen("2. Press SPACE BAR to release ball"));
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[1], x, 300, "3. Press Q to quit game", strlen("3. Press Q to quit game"));
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[1], x, 450, "Ready?", strlen("Ready?"));    
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[1], x, 500, "Click anywhere to start the game", strlen("Click anywhere to start the game"));
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[1], 2, xinfo.height-30, "Name: Hui Ling", strlen("Name: Hui Ling"));
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[1], 2, xinfo.height-15, "UserID: 007", strlen("UserID: 007"));
    XCopyArea(xinfo.display, xinfo.pixmap, xinfo.window, xinfo.gc[0], 
	      0, 0, xinfo.width, xinfo.height,
	      0, 0); 
    XFlush(xinfo.display);
  }
  Splash(XInfo &xinfo) {
    first = true;
    x = xinfo.width / 3;
    y = xinfo.height / 4 * 3;
    box_width = x;
    box_height = xinfo.height / 15;
  }
};

class Main : public Displayable {
public:
  string box;
  string scored;
  int brick_start;
  int x;
  virtual void paint(XInfo &xinfo) {
    std::string scored;
    std::stringstream out;
    out << score;
    scored = out.str();
    box = "SCORE: " + scored;
    XDrawString(xinfo.display, xinfo.pixmap, xinfo.gc[1], 0, xinfo.height-20, box.c_str(), box.length());
  }   
  Main(int scored, int brick_start, int x) {
    this->scored = score;
    this->brick_start = brick_start;
    this->x = x;                          
    box = "SCORE: " + this->scored;
  }
};


class Paddle : public Displayable {
public:
  int x;
  int y;
  int width;
  int height;
  virtual void paint(XInfo &xinfo) {
    XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[4], x-width/2, y-height/2, width, height);
  }
  void move_key(char c) {
    if(c=='L') { 
      this->x -= 100; 
    }
    else if(c=='R') {
      this->x += 100; 
    }
  }			
  Paddle(int x, int y, int width, int height): x(x), y(y), width(width), height(height) { }
};

class Brick : public Displayable {
public:
  int x;
  int y;
  int width;
  int height;
  GC* gc;
  virtual void paint(XInfo &xinfo) {
    XFillRectangle(xinfo.display, xinfo.pixmap, *gc, x, y, width, height);        
  }
  Brick(int x, int y, GC* gc, int brick_width, int brick_height)  {
    this->x = x;
    this->y = y;
    this->gc = gc;
    width = brick_width;
    height = brick_height;
  }
};

class Ball: public Displayable {
public:
  int x;
  int y;
  int radius;
  int direction;
  int speed;
  int width;
  int height;
  vector<Brick>* brick_list;
  bool breaking;
  bool stop;
  virtual void paint(XInfo &xinfo) {
    XFillArc(xinfo.display, xinfo.pixmap, xinfo.gc[4], x-radius, y-radius, radius*2, radius*2, 0, 360*64); 
  }
  void collision(XInfo &xinfo, XEvent &event, Paddle* paddle) {
    if(y+radius > xinfo.height) {
      stop = true;
      this->x = paddle->x;
      this->y = paddle->y-paddle->height/2 - speed * 2;
      direction = 1;
    } else { 
      if(direction ==1) { 
	if(y-radius< 0 && x+radius > xinfo.width) { 
	  direction = 3;
	}else if(y-radius < 0) { 
	  direction = 2;
	}else if(x+radius > xinfo.width) { 
	  direction = 4;
	}else {
	  if (!breaking){
	    score += 50;
	    breaking = true;
	    brick_list->erase(brick_list->begin()+y);//TODO: Should check if hit brick
	  }
	}
	//keep moving
	x += speed;
	y -= speed;
      } else if(direction == 2) {
	if(x+radius > xinfo.width) {
	  direction = 3;
	} else if(y+radius>paddle->width &&  x+radius > paddle->x-paddle->width/2 && y+radius<paddle->height && x <= paddle->x) {
	  direction = 4;
	} else if(y+radius<paddle->height && x-radius<paddle->height+paddle->width/2) {
	  direction = 1;
	} else {
	  if (!breaking){
	    score += 50;
	    breaking = true;
	    brick_list->erase(brick_list->begin()+y);
	  }
	}
	//keep moving
	x += speed;
	y += speed;
      } else if(direction == 3) {
	if(x-radius < 0) {
	  direction = 2;
	}else if(x>paddle->x && y+radius<paddle->y+paddle->height && x-radius<paddle->x+paddle->width/2) {
	  direction = 1;
	}else if(x+radius>paddle->x-paddle->width/2 && y+radius<paddle->y+paddle->height && x<paddle->x) {
	  direction = 4;
	}else {
	  if (!breaking){
	    score += 50;
	    breaking = true;
	    brick_list->erase(brick_list->begin()+y);
	  }
	}
	//keep moving
	x -= speed;
	y += speed;
      } else if(direction == 4) {
	if(y-radius<0 && x-radius<0) {
	  direction = 2;
	}else if(y-radius<0) {
	  direction = 3;
	}else if(x-radius<0) {
	  direction = 1;
	}else {
	  if (!breaking){
	    score += 50;
	    breaking = true;
	    brick_list->erase(brick_list->begin()+y);
	  }
	}
	//keep moving
	x -= speed;
	y -= speed;
      }
    }
    
  }
  Ball(int x, int y, int radius, int speed, vector<Brick>* brick_list, int brick_width, int brick_height) {
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->speed = speed;
    this->brick_list = brick_list;
    width = brick_width;
    height = brick_height;
    direction = 1;
    stop = true;     
  }
};

void initX(int argc, char *argv[], XInfo &xInfo) {
  XSizeHints hints;
  unsigned long white, black;
  xInfo.display = XOpenDisplay( "" );
  xInfo.screen = DefaultScreen(xInfo.display);
  white = XWhitePixel(xInfo.display, xInfo.screen);
  black = XBlackPixel(xInfo.display, xInfo.screen);
  hints.width = screen_x;
  hints.height = screen_y;
  xInfo.width = screen_x;
  xInfo.height = screen_y;
  hints.x = 100;
  hints.y = 100;
  hints.flags = PPosition | PSize; 
  xInfo.window = XCreateSimpleWindow(xInfo.display, DefaultRootWindow(xInfo.display), hints.x, hints.y, hints.width, hints.height, 10, black, white );						
  XSetStandardProperties(xInfo.display, xInfo.window, "Breakout", "Breakout", None, argv, argc, &hints );
  XSetWMNormalHints(xInfo.display, xInfo.window, &hints);
  //Black
  xInfo.gc[0] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
  XSetForeground(xInfo.display, xInfo.gc[0], BlackPixel(xInfo.display, xInfo.screen));
  XSetBackground(xInfo.display, xInfo.gc[0], WhitePixel(xInfo.display, xInfo.screen));
  XSetFillStyle(xInfo.display, xInfo.gc[0], FillSolid);
  XSetLineAttributes(xInfo.display, xInfo.gc[0], 1, LineSolid, CapButt, JoinRound);
  //White
  xInfo.gc[1] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
  XSetForeground(xInfo.display, xInfo.gc[1], WhitePixel(xInfo.display, xInfo.screen));
  XSetBackground(xInfo.display, xInfo.gc[1], BlackPixel(xInfo.display, xInfo.screen));
  XSetFillStyle(xInfo.display, xInfo.gc[1], FillSolid);
  XSetLineAttributes(xInfo.display, xInfo.gc[1], 1, LineSolid, CapButt, JoinRound);
  //Bricks colours
  Colormap screen_colormap;
  XColor red, orange, yellow, green, blue, purple;
  screen_colormap = DefaultColormap(xInfo.display, xInfo.screen);

  xInfo.gc[2] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
  XAllocNamedColor(xInfo.display, screen_colormap, "red", &red, &red);
  XSetForeground(xInfo.display, xInfo.gc[2], red.pixel);

  xInfo.gc[3] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
  XAllocNamedColor(xInfo.display, screen_colormap, "orange", &orange, &orange);
  XSetForeground(xInfo.display, xInfo.gc[3], orange.pixel);

  xInfo.gc[4] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
  XAllocNamedColor(xInfo.display, screen_colormap, "yellow", &yellow, &yellow);
  XSetForeground(xInfo.display, xInfo.gc[4], yellow.pixel);

  xInfo.gc[5] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
  XAllocNamedColor(xInfo.display, screen_colormap, "green", &green, &green);
  XSetForeground(xInfo.display, xInfo.gc[5], green.pixel);

  xInfo.gc[6] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
  XAllocNamedColor(xInfo.display, screen_colormap, "blue", &blue, &blue);
  XSetForeground(xInfo.display, xInfo.gc[6], blue.pixel);

  xInfo.gc[7] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
  XAllocNamedColor(xInfo.display, screen_colormap, "purple", &purple, &purple);
  XSetForeground(xInfo.display, xInfo.gc[7], purple.pixel);
	
  int depth = DefaultDepth(xInfo.display, DefaultScreen(xInfo.display));
  xInfo.pixmap = XCreatePixmap(xInfo.display, xInfo.window, xInfo.width, xInfo.height, depth);
  XSelectInput(xInfo.display, xInfo.window, 
	       ButtonPressMask | KeyPressMask | 
	       PointerMotionMask | 
	       EnterWindowMask | LeaveWindowMask |
	       StructureNotifyMask);  
  XMapRaised( xInfo.display, xInfo.window );
  XFlush(xInfo.display);
}

void handleButtonPress(XInfo &xinfo, XEvent &event, Ball *ball, Splash *menu) {
  if(!startPlay && event.xbutton.button == Button1) {
    startPlay = true;  
    bool first = false; 
    menu->first;
  }
}
void handleKeyPress(XInfo &xinfo, XEvent &event, Paddle* paddle, Ball* ball) {
  KeySym key;
  char text[BufferSize];
  int i = XLookupString( 
			(XKeyEvent *)&event, 	
			text, 			
			BufferSize, 			
			&key, 					
			NULL );				
  switch(key) {//spacebar
  case XK_space:
    ball->stop = false;  
    break;
  case XK_Left: //left arrow move
    paddle->move_key('L');     
    break;
  case XK_Right: //right arrow move
    paddle->move_key('R');           
    break;
  case XK_q:
    XCloseDisplay(xinfo.display);
    exit(0);
  }     
}

void repaint(vector<Displayable *> dVector, XInfo &xinfo) {
  XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 0, 0, xinfo.width, xinfo.height);
  for(int i=0; i<dVector.size(); i++) {
    dVector.at(i)->paint(xinfo);
  }
  XCopyArea(xinfo.display, xinfo.pixmap, xinfo.window, xinfo.gc[0], 
	    0, 0, xinfo.width, xinfo.height,
	    0, 0);
  XFlush(xinfo.display);
}

void eventLoop(XInfo &xinfo, int FPS, int speed) {
  vector<Displayable *> dVector;
  vector<Brick> brick_list;
  int start_x = xinfo.width/15-20;
  int start_y = xinfo.height/15;
  int brick_width = xinfo.width/11;
  int brick_height = xinfo.height/18;
  int brick_colour=2; //start from red
  XEvent event;
  unsigned long lastRepaint = 0;
  bool first = false;
  Splash menu(xinfo);//Splash
  Main main(score, xinfo.height/50, xinfo.width/100);//Main game environment
  Paddle paddle(600, 700, 160, 20);//Paddle
  for(int i=0; i<bricks_size; i++) {//Creating bricks
    if(i > 0) { 
      start_x += brick_width + 2;//add space 
    }
    if(i!=0 && i%10==0) { 
      start_x = xinfo.width/15-20;//second role first one
      start_y += brick_height; 
      brick_colour++;
    }
    Brick one(start_x, start_y, &xinfo.gc[brick_colour], brick_width, brick_height);
    brick_list.push_back(one);
  }
  Ball ball(paddle.x, paddle.y-paddle.height/2 - speed * 2, 10, speed, &brick_list, brick_width, brick_height);
  dVector.push_back(&main);
  dVector.push_back(&paddle);
  dVector.push_back(&ball);
  for(int i=0; i<bricks_size; i++) {
    dVector.push_back(&brick_list[i]);
  }
  while(true) {		
    if (XPending(xinfo.display) > 0) {
      XNextEvent(xinfo.display, &event);
      switch(event.type) {
      case ButtonPress://for menu
	handleButtonPress(xinfo, event, &ball, &menu);
	break;
      case KeyPress://for in game
	handleKeyPress(xinfo, event, &paddle, &ball);
	break;
      } 
    } 
    usleep(10000);
    unsigned long time_n2 = now();
    int start = 0;
    if(!startPlay) {
      menu.paint(xinfo);
      continue;   
    }
    if(!ball.stop) {  
      ball.collision(xinfo, event, &paddle);
    } else {
      ball.x = paddle.x;
      ball.y = ball.y;
    }
    if(!first) {
      repaint(dVector, xinfo);
      first = true;
    }
    if(time_n2 - lastRepaint > 1000000/ FPS) {
      repaint(dVector, xinfo); 
      lastRepaint = now();    
    }
    // IMPORTANT: sleep for a bit to let other processes work
    if (XPending(xinfo.display) == 0) {
      usleep(1000000 / FPS - (now() - lastRepaint));
    }
  }
}

int main ( int argc, char *argv[] ) {
  XInfo xInfo;
  initX(argc, argv, xInfo);
  eventLoop(xInfo, FPS, speed);
  XCloseDisplay(xInfo.display);
}

