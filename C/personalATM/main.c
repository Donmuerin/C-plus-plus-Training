#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

void printMenu(){
    printf("\n-----------Your Personal ATM Service--------------\n");
    printf("1. Withdraw\n");
    printf("2. Deposit\n");
    printf("3. Check Balance\n");
    printf("4. Print Receipt\n\n");
    printf("Enter your choice: ");
}

int main()
{
    double amount = 5000, deposit, withdraw, totalWithdraw, totalDeposit;
    int i, j, count, exit, choice, account;
    j = 0;
    count = 0;

    char transaction;
    char valid[] = "abc123";
    char password[6], ch;

    printf("Enter your account number: ");
    while (scanf("%d", &account) != 1){
        while (getchar() != '\n');//cannot use getch() as it will not recognize the error
        printf ("Try again: ");
    }
    printf ("Hello, %d\n", account, "\n");

    printf("\nEnter the password: ");
    for(i = 0; i < 6; ++i){
        ch = getch();//cannot use getchar() as the rest will show up on screen
        password[i] = ch;
        if (valid[i] != ch)
            ++j;
        ch = '*' ;
        printf("%c",ch);
        }

    while (j != 0){
        printf("\nWrong Password. Try again: ");
        ++count;
        j = 0;
        for(i = 0; i < 6; ++i){
            ch = getch();//cannot use getchar() as the rest will show up on screen
            password[i] = ch;
            if (valid[i] != ch)
                ++j;
            ch = '*' ;
            printf("%c",ch);
            }
        if (count > 2 && j != 0){
            printf("\nFailed to log in.");
            return 0;
            }
        }


    do{
    printMenu();
    scanf("%d", &choice);

    switch (choice){
		case 1:
			printf("\nAmount?: $");
			scanf("%lf", &withdraw);
			while (amount < withdraw){
                printf("\nInvalid! Please enter again: ");
                scanf("%lf", &withdraw);
			}
			amount = amount - withdraw;
			totalWithdraw += withdraw;
			printf("\nBalance: $ %0.2lf ", amount);
			break;
		case 2:
			printf("\nAmount?: $");
			scanf("%lf", &deposit);
            amount = amount + deposit;
            totalDeposit += deposit;
            printf("\nBalance: $ %0.2lf ", amount);
			break;
		case 3:
		    printf("\nAvailable Balance: $ %0.2lf ", amount);
			break;
        case 4:
            printf("\t-----------Print receipt-----------");
            printf("\n\tTotal Cash Withdrawal Amount: $ %0.2lf", totalWithdraw);
            printf("\n\tTotal Cash Deposit Amount: $ %0.2lf", totalDeposit);
            printf("\n\tAvailable Balance: $ %0.2lf", amount);
            break;
		default:
			printf("\nInvalid!");
		}
		printf("\nDo you want to do another transaction?(Press N/n for NO): ");
		fflush(stdin);
		scanf("%c", &transaction);
		if (transaction == 'N'|| transaction == 'n')
            exit = 0;
        else
            exit = 1;
    }while(exit == 1);

    printf("\nGoodbye!");

    return 0;

}
