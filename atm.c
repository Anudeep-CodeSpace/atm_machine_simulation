#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#define TRANSACTION_LIMIT 10
#define WITHDRAWL_LIMIT 3

enum transaction_type {
	DR = 1, CR = 0,
};

void getTimeString(char t_time[]) {
	time_t raw_time;
	time(&raw_time);
	struct tm *local_time = localtime(&raw_time);
	strftime(t_time, 30, "%Y/%m/%d %H:%M:%S", local_time);
}

struct user {
	char name[30];
	char pin[7];
	float balance;
	struct transaction {
		char t_time[30];
		int amount;
		enum transaction_type type;
	}transactions[TRANSACTION_LIMIT];
	int n_trans;
	int n_wd;
}customer = {.name = "Anudeep", .pin = "111111", .balance = 0.0f, .n_trans = 0, .n_wd = 0};

void deposit();
void withdrawl();
void balance(int n);
void transaction_history();
void pin_change();

void main() {
	int ch;
	while(1) {
		system("cls");
		printf("\n\n\n\n\t\t\t##########################################");
		printf("\n\t\t\t#             Welcome to ATM             #");
		printf("\n\t\t\t##########################################");
		
		printf("\n\n\t\t\t1>> Deposit");
		printf("\n\t\t\t2>> Withdrawl");
		printf("\n\t\t\t3>> Balance Enquiry");
		printf("\n\t\t\t4>> Transaction History");
		printf("\n\t\t\t5>> Change your PIN");
		printf("\n\t\t\t6>> Cancel");
		printf("\n\n\t\t\tEnter Your Choice: ");
		scanf("%d", &ch);
		getchar();
		switch(ch) {
			case 1:
				deposit();
				break;
			case 2:
				withdrawl();
				break;
			case 3:
				balance(0);
				break;
			case 4:
				transaction_history();
				break;
			case 5:
				pin_change();
				break;
			case 6:
				exit(0);
				break;
			default:
				printf("\n\t\t\tInvalid Choice\n\t\t\tPress any key to try again...");
				getchar();
		}
	}
}

void deposit() {
	system("cls");
	printf("\n\n\n\n\t\t\t##########################################");
	printf("\n\t\t\t#             Deposit Section            #");
	printf("\n\t\t\t##########################################");
	if(customer.n_trans == TRANSACTION_LIMIT) {
		printf("\n\t\t\tTransaction limit Exceeded.");
		return;
	}
	printf("\n\n\t\t\tEnter Deposit Amount: ");
	int dep;
	scanf("%d", &dep);
	getchar();
	if(dep % 100 > 0) {
		printf("\n\t\t\tPlease enter the amount in MULTIPLE OF 100");
		deposit();
		return;
	} else {
		printf("\n\t\t\tPlease Enter your PIN: ");
		char pass[10], ch;
		fgets(pass, 10, stdin);
		pass[strcspn(pass, "\n")] = '\0';
		if(strcmp(customer.pin, pass)) {
			printf("\n\t\t\tIncorrect PIN. Transaction Cancelled");
			sleep(1);
			return;
		} else {
			if(customer.n_trans == TRANSACTION_LIMIT) {
				printf("\n\t\t\tTransaction Limit Exceeded...\n\t\t\tTransaction Cancelled");
				sleep(5);
				return;
			}
			getTimeString(customer.transactions[customer.n_trans].t_time);
			customer.transactions[customer.n_trans].amount = dep;
			//printf("%d %d", customer.transactions[customer.n_trans].amount, dep);
			customer.balance += dep;
			customer.transactions[customer.n_trans].type = CR;
			customer.n_trans++;
			printf("\n\t\t\tDeposit Successful\n\t\t\t");
			printf("\n\t\t\tDo you want to display your balance? (Y/N): ");
			ch = getchar();
			if(ch == 'Y' || ch == 'y')
				balance(1);
			printf("\n\t\t\tTransaction completed.");
			sleep(5);
		}
	}
}

void balance(int n) {
	if(n == 1) {
		printf("\n\t\t\tYour Balance: %.2f", customer.balance);
	} else {
		printf("\n\t\t\tPlease Enter your PIN: ");
		char pass[10];
		fgets(pass, 10, stdin);
		pass[strcspn(pass, "\n")] = '\0';
		if(strcmp(customer.pin, pass)) {
			printf("\n\t\t\tIncorrect PIN. Transaction Cancelled");
			sleep(5);
			return;
		} else {
			printf("\n\t\t\tYour Balance: %.2f", customer.balance);
			printf("\n\n\t\t\tTransaction completed.");
			sleep(5);
		}
	}
}

void withdrawl() {
	system("cls");
	printf("\n\n\n\n\t\t\t##########################################");
	printf("\n\t\t\t#            Withdrawl Section           #");
	printf("\n\t\t\t##########################################");
	if(customer.n_trans == TRANSACTION_LIMIT) {
		printf("\n\t\t\tTransaction limit Exceeded.");
		sleep(5);
		return;
	} else if(customer.n_wd == WITHDRAWL_LIMIT) {
		printf("\n\t\t\tWithdrawl limit exceeded.\n\t\t\tTransaction Cancelled.");
		sleep(5);
		return;
	}
	int wd;
	printf("\n\n\t\t\tEnter Withdrawl Amount: ");
	scanf("%d", &wd);
	getchar();
	if(wd % 100 > 0) {
		printf("\n\t\t\tPlease enter the amount in MULTIPLE OF 100");
		sleep(2);
		withdrawl();
		return;
	} else {
		printf("\n\t\t\tPlease Enter your PIN: ");
		char pass[10];
		fgets(pass, 10, stdin);
		pass[strcspn(pass, "\n")] = '\0';
		if(strcmp(customer.pin, pass)) {
			printf("\n\t\t\tIncorrect PIN. Transaction Cancelled");
			sleep(5);
			return;
		} else {
			if(wd > customer.balance) {
				printf("\n\t\t\tInsufficient balance.\n\t\t\tTransaction Cancelled.");
				sleep(5);
				return;
			} else {
				getTimeString(customer.transactions[customer.n_trans].t_time);
				customer.transactions[customer.n_trans].amount = wd;
				customer.balance -= wd;
				customer.transactions[customer.n_trans].type = DR;
				customer.n_trans++;
				customer.n_wd++;
				printf("\n\t\t\tPlease collect your cash...");
				sleep(3);
				printf("\n\t\t\tTransaction completed.");
				sleep(5);
				return;
			}
		}
	}
}

void pin_change() {
	system("cls");
	printf("\n\n\n\n\t\t\t##########################################");
	printf("\n\t\t\t#            Pin Change Section          #");
	printf("\n\t\t\t##########################################");
	printf("\n\n\t\t\tPlease Enter your PIN: ");
	char pass[10];
	fgets(pass, 10, stdin);
	pass[strcspn(pass, "\n")] = '\0';
	if(strcmp(customer.pin, pass)) {
		printf("\n\t\t\tIncorrect PIN. Transaction Cancelled");
		sleep(5);
		return;
	} else {
		char new_pin[7], verify[7];
		try_again: printf("\n\n\t\t\t Enter New PIN: ");
		scanf("%[^\n]s", new_pin);
		printf("\t\t\t Re-enter New PIN: ");
		while(getchar() != '\n');
		scanf("%[^\n]s", verify);
		if(strcmp(verify, new_pin) != 0) {
			goto try_again;
		} else {
			strcpy(customer.pin,new_pin);
			printf("\n\t\t\tPIN updated successfully.");
			sleep(5);
			return;
		}
	}
}

void transaction_history() {
	system("cls||clear");
	printf("\n\n\n\n\t\t\t##########################################");
	printf("\n\t\t\t#           Transaction History          #");
	printf("\n\t\t\t##########################################");
	printf("\n\n\t\t\tPlease Enter your PIN: ");
	char pass[10];
	fgets(pass, 10, stdin);
	pass[strcspn(pass, "\n")] = '\0';
	if(strcmp(customer.pin, pass)) {
		printf("\n\t\t\tIncorrect PIN. Transaction Cancelled");
		sleep(5);
		return;
	} else {
		printf("\n\tS.No\tAmount\tType\tTime");
		for(int i = 0; i < TRANSACTION_LIMIT && customer.transactions[i].amount != 0; i++) {
			printf("\n\t%d)\t\t", i + 1);
			printf("%d\t\t%s\t\t%s\n", customer.transactions[i].amount, customer.transactions[i].type == 1?"DR":"CR", customer.transactions[i].t_time);
		}
		printf("\n\n\t\t\tYour Balance: %.2f", customer.balance);
		printf("\n\n\t\t\tPress Enter to exit.");
		getchar();
	}
}