#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>


int select_option(int, int);
int g_id();
void create_acc();
bool check_login(int, int);
void login();
void home();
void withdrawal();
void deposit();
void acc_info();
void edit_info();
void write_to_file();
bool read_from_file(int);
void delete_acc();

struct ACCOUNT {
	int id;
	int pin;
	char fname[20];
	char lname[20];
	char birth_date[11];
	double balance;
} acc = {};


int main()
{
	int opt;
	system("cls");
	do {
		printf("\t Welcome to the \"Bank managment system\"\n\n");
		printf("1. Create account\n");
		printf("2. Log in\n");
		printf("3. Exit\n");
		opt = select_option(1, 3);

		switch (opt) {
		case 1:
			create_acc();
			break;
		case 2:
			login();
			break;
		}
	} while (opt != 3);

}

int select_option(int from, int to) {
	int opt;

	do {
		printf("Please select an option: ");
		scanf("%d", &opt);
		if (opt >= from && opt <= to) {
			return opt;
		}
	} while (true);
}



int g_id() {
	int lower = 1001, upper = 1999, id;
	srand(time(NULL));
	do {
		id = (rand() % (upper - lower + 1)) + lower;
		// Make sure this number is not used before
		char file_name[9];
		sprintf(file_name, "%d.dat", id);
		FILE* fh = fopen(file_name, "r");
		if (fh == NULL) {
			// The id doesn't exist
			return id;
		}
		else {
			fclose(fh);
		}
	} while (true);
}

void write_to_file() {
	char file_name[9];
	sprintf(file_name, "%d.dat", acc.id);
	FILE* fh = fopen(file_name, "w");

	if (fh != NULL) {
		fwrite(&acc, sizeof(struct ACCOUNT), 1, fh);
		fclose(fh);
	}
}

void create_acc() {
	int pin, repin;
	system("cls");
	printf("\t\tCreating new account\n\n");
	printf("Enter your:\n");
	printf("Name: ");
	scanf("%s", acc.fname);
	printf("Surname: ");
	scanf("%s", acc.lname);
	printf("Birthdate like dd.mm.yyyy : ");
	scanf("%s", acc.birth_date);
	printf("-----------\n");
	do {
		printf("Create login PIN: ");
		scanf("%d", &pin);
		printf("Re-enter the PIN: ");
		scanf("%d", &repin);
		if (repin == pin) {
			acc.pin = pin;
			printf("The account has been created successfully\n");
			acc.id = g_id();
			write_to_file();
			printf("Your account ID is: %d\n", acc.id);
			printf("Press ENTER to continue\n");
			getch();
			break;
		}
		else
			printf("The PIN doesn't match\n");
	} while (true);
	//*****
	system("cls");
}

bool read_from_file(int id) {
	char file_name[9];
	sprintf(file_name, "%d.dat", id);
	FILE* fh = fopen(file_name, "r");
	if (fh == NULL) {
		// This account id doesn't exist
		return false;
	}
	fread(&acc, sizeof(struct ACCOUNT), 1, fh);
	fclose(fh);
	return true;
}

bool check_login(int id, int pin) {
	return read_from_file(id) && acc.pin == pin;
}

void login() {
	int id, pin;
	system("cls");
	printf("\t Log in PAGE\n\n");

	
		for (int i = 0; i < 3; i++) {
			printf("Enter id: ");
			scanf("%d", &id);
			printf("\n");
			printf("Enter PIN: ");
			scanf("%d", &pin);
			printf("\n");

			if (check_login(id, pin)) {
				home();
				break;
			}
			else {
				printf("Invalid ID or PIN\n");
			}
			//Qs
			if (i == 2) {
		create_acc();
		break;
			}
		}
}

void home() {
	int opt;
	system("cls");
	do {
		printf("\t Welcome to the system\n\n");
		printf("\t   Hi %s\n", acc.fname);
		printf("\t   Your balance is: %.2f\n\n", acc.balance);
		printf("1. Account information\n");
		printf("2. Money Withdrawal\n");
		printf("3. Money Deposit\n");
		printf("0. Logout\n");
		opt = select_option(0, 3);
		switch (opt)
		{
		case 1:
			acc_info();
			break;
		case 2:
			withdrawal();
			break;
		case 3:
			deposit();
			break;
		}
	} while (opt != 0 && acc.id != 0);
	system("cls");
}

void edit_info() {
	int opt;
	system("cls");
	do {
		printf("\t\tEditing Account Information\n\n");
		printf("1. Name\n2. Surname\n3. Birthdate\n4. PIN\n0. Return\n");
		opt = select_option(0, 4);
		switch (opt) {
		case 1:
			printf("Name: ");
			scanf("%s", acc.fname);
			break;
		case 2:
			printf("Surname: ");
			scanf("%s", acc.lname);
			break;
		case 3:
			printf("Birthdate: ");
			scanf("%s", acc.birth_date);
			break;
		case 4:
			printf("PIN: ");
			scanf("%d", &acc.pin);
			break;
		}
		printf("\n");
	} while (opt != 0);
	write_to_file();
}

void acc_info() {
	int opt;
	system("cls");
	do {
		printf("\t\tAccount Information\n\n");
		printf("Account Id: %d\n", acc.id);
		printf("Name: %s\n", acc.fname);
		printf("Surname: %s\n", acc.lname);
		printf("Birthdate: %s\n", acc.birth_date);
		printf("Balance: %.2f\n", acc.balance);
		printf("\n-----------\n");

		printf("1. Edit your account info\n");
		printf("2. Delete your account\n");
		printf("0. Return\n");
		opt = select_option(0, 2);
		switch (opt) {
		case 1:
			edit_info();
			break;
		case 2:
			delete_acc();
			break;
		case 0:
			home();
			break;
		default:
			printf("\nInvalid choice\n");
			continue;
		}
	} while (opt != 0 && acc.id != 0);
	system("cls");
}

void withdrawal() {
	double value;
	system("cls");
	printf("\t\tMoney Withdrawal\n\n");
	printf("Your account balance: %.2f\n", acc.balance);
	do {
		printf("Amount: ");
		scanf("%lf", &value);
		if (value <= acc.balance) {
			acc.balance -= value;
			write_to_file();
			printf("Your new account balance: %.2f\n", acc.balance);
			break;
		}
		else {
			printf("\nNot enough balance, you need to enter an amount less than or equal to: %.2f\n", acc.balance);
		}
	} while (true);
}

void deposit() {
	double value;
	system("cls");
	printf("\t\tMoney Deposit\n\n");
	printf("Your account balance: %.2f\n", acc.balance);
	do {
		printf("Amount: ");
		scanf("%lf", &value);
		if (value > 0) {
			acc.balance += value;
			printf("\nYour new account balance is: %.2f\n", acc.balance);
			write_to_file();
			break;
		}
		else {
			printf("\nInvalid amount, you need to enter a positive amount value\n");
		}
	} while (true);
}

void delete_acc() {
	char opt[2];
	system("cls");
	printf("\t\tDeleting Account\n\n");
	if (acc.balance == 0) {
		printf("Are you sure you want to delete the account? (y = yes, n = no): ");
		scanf("%s", opt);
		if (opt[0] == 'y' || opt[0] == 'Y') {
			//Deleting account
			char file_name[9];
			sprintf(file_name, "%d.dat", acc.id);
			remove(file_name);
			acc.id = 0;
			printf("Your account has been deleted\n");
			printf("Press ENTER to continue\n");
			getch();
		}
	}
	else {
		printf("You have a balance in your account\nYou should empty your account from any value to delete it, please use the withdrwal menu to empty your account\n");
		printf("Press ENTER to continue\n");
		getch();
	}
}


