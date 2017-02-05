import java.util.Scanner;

public class MainProgram {
	public static void main(String[] args){
	
		Calculator cal;
		int optionum;//user's option
		String inputval;//values to operate
		double result;
		int memonum;//which "memory" to store
		Scanner scan = new Scanner(System.in);
		cal = new Calculator(); 
		System.out.println("Welcome to the 'Simple Calculator System'.");
		
		do{
			System.out.println("Choose 1 to add the numbers");
			System.out.println("Choose 2 to subtract the numbers");
			System.out.println("Choose 3 to multiply the numbers");
			System.out.println("Choose 4 to divide the numbers");
			System.out.println("Choose 5 to clear current value");
			System.out.println("Choose 6 to store a value");
			System.out.println("Choose 7 to retrieve a value");
			System.out.println("Choose 8 to display number sequence");
			System.out.println("Choose 9 to quit the program");
			System.out.println("Please enter your option: ");
			optionum = scan.nextInt();
			scan.nextLine();
		
			//I used switch-case rather than nested-if as it's more convenient in this case
			switch(optionum){

				case 1: 
						do{
						System.out.println("Number to add: ");
						inputval = scan.nextLine();
						if (cal.isnum(inputval)){
							result = cal.add(inputval);
							System.out.println("Result: " + result);
						}else{	
							System.out.println("Error: Non-numeric input!");
							}
						}while(!(cal.isnum(inputval)));
						break;
						
					
				case 2: 
						do{
						System.out.println("Number to subtract: ");
						inputval = scan.nextLine();
						if (cal.isnum(inputval)){
							result = cal.subtract(inputval);
							System.out.println("Result: " + result);
						}else{
							System.out.println("Error: Non-numeric input!");
							}
						}while(!(cal.isnum(inputval)));
						break;
						
				case 3: 
						do{
						System.out.println("Number to multiply: ");
						inputval = scan.nextLine();
						if (cal.isnum(inputval)){
							result = cal.multiply(inputval);
							System.out.println("Result: " + result);
						}else{
							System.out.println("Error: Non-numeric input!");
							}
						}while(!(cal.isnum(inputval)));
						break;
				
						
				case 4: 
						
						do{
						System.out.println("Number to divide by(non-zero): ");
						inputval = scan.nextLine();
						
						if (!cal.isnum(inputval)){
							System.out.println("Error: Non-numeric input!");
						}else if (Double.parseDouble(inputval)==0.0){
						System.out.println("Error: Cannot be 0, Please try again.");
							}
						}while(!(cal.isnum(inputval))||Double.parseDouble(inputval) == 0.0);
						result = cal.division(inputval);
						System.out.println("Result: "+ result);
						
						break;
						
				case 5: 
						cal.reset();
						System.out.println("Restarted. Current value has become zero.");
						break;
						
				case 6: 
						do{
							System.out.println("Where do you want to store?(1 , 2 or 3)");
							memonum = scan.nextInt();
							if (memonum < 1 || memonum > 3)
								System.out.println("Invalid input, please try again!");
						} 
						while (memonum < 1 || memonum > 3);
						if (cal.tomemory(memonum)){
							System.out.println("Successful. Stored to memory: " + memonum);
						}else
							System.out.println("Error occured");
						break;
						
				case 7: 
						do{
							System.out.println("Where do you want to retrive?(1 , 2 or 3)");
							memonum = scan.nextInt();
							if (memonum < 1 || memonum > 3)
								System.out.println("Invalid input, please try again!");
						} 
						while (memonum < 1 || memonum > 3);
						if (cal.frommemory(memonum)){
							System.out.println("Successful. Retrived from memory: " + memonum);
							System.out.println("Current value is: " + cal.currval());
						}else
							System.out.println("Error occured");
						break;
			}	
		}while (optionum !=9);
		scan.close();
	}
	
}

