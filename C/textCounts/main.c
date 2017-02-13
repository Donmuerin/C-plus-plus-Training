#include <stdio.h>

int main()
{
     FILE *fp;
     char ch;
     int line = 0, word = 0;

     fp = fopen("example.txt","w");
     printf("Enter text: \n");
     do{
        ch = getchar();
        putc(ch,fp);
     }
     while(ch != EOF);
        fclose(fp);

     fp = fopen("example.txt","r");
     if(fp){
        while ((ch = getc(fp)) != EOF) {
            if (ch == '\n')
                ++line;

            if (ch == ' ' || ch == '\t' || ch == '\n')
                ++word;
        }
     }else{
        printf("Failed to open the file\n");
     }


    printf("Lines : %d \n", line);
    printf("Words : %d \n", word);

    getchar();

    return(0);
}
