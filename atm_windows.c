#include <stdio.h>
#include <stdlib.h>		// using by memset(), rand(), srand()
#include <string.h>		// using by strcmp()
#include <time.h>		// using by srand()’s argument
#include <ctype.h>		// using by isdigit()
#define MAX_USER 255

typedef struct{
	char name[10];
	char passwd[16];
	unsigned int account;
	unsigned int balance;
}user_Data;

int login_info(user_Data *user);		// login
int check_info(user_Data *user, int cnt);	// when you login or sign up, you must check a name and a password
void sign_up(user_Data *user);			// sign up
int depo_info(char *pw);			// deposit
int withdraw_info(char *pw, int bal);		// withdraw
void transfer(user_Data *user, int cnt);	// account transfer
void change_pw(user_Data *user);		// change password
int check_password(char *pw);			// check password
void datas(user_Data *user, char *sel);		// save or load data using file I/O

FILE *fp;

int main() {
	int sel_num = 0, count, i;
	user_Data *user = (user_Data*)malloc(sizeof(user_Data) * MAX_USER);

	for(i = 0; i < MAX_USER; i++) {			// initialize users data
		memset((user+i)->name, NULL, sizeof(user->name));
		memset((user+i)->passwd, NULL, sizeof(user->passwd));
		(user+i)->account = 0;
		(user+i)->balance = 0;
	}
	datas(user, "load");

	while(1) {
		count = 0;
		printf("****************************************\n*\tWhat do you want to do?\n*\t1. Login\n*\t2. Sign up\n*\t3. Exit\n*\t--> ");
		scanf_s("%d", &sel_num);
		fflush(stdin);
		system("cls");
		switch(sel_num) {
		case 1:			// insert info(name, passwd)
			count = login_info(user);
			if(count != 0) {		// insert menu --> menu select (check balance / deposit / withdraw / transfer balance / passwd change)
				while(1) {
					system("cls");
					printf("****************************************\n*\tWelcome %s !!\n*\tWhat do you want to do?\n*\t1. Check balance\n*\t2.Deposit\n*\t3. Withdraw\n*\t4. Account transfer\n*\t5. Change password\n*\t6. Exit\n*\t--> ", (user+count)->name);
					scanf_s("%d", &sel_num);
					system("cls");
					printf("****************************************\n*");
					fflush(stdin);
					switch(sel_num) {
					case 1:		// confirm account number and balance
						printf("\t%s sir, your account number is\n*\taccount : %d\n*\tand your balance is\n*\tbalance : %d won\n", (user+count)->name, (user+count)->account, (user+count)->balance);
						break;
					case 2:		// deposit
						i = depo_info((user+count)->passwd);
						if(i != 0) printf("*\tNow your balance is %d won\n", (user+count)->balance+=i);
						break;
					case 3:		// withdraw
						i = withdraw_info((user+count)->passwd, (user+count)->balance);
						if(i != 0) printf("*\tNow your balance is %d won\n", (user+count)->balance-=i);
						break;
					case 4:		// account transfer
						transfer(user+count, count+1);
						break;
					case 5:		// change password
						change_pw(user+count);
						break;
					case 6:		// exit
						count = -2;
						system("cls");
						break;
					default:
						printf("\t%d is wrong number!\n*\tPlease try again\n", sel_num);
						break;
					}
					if(count == -2) {
						datas(user, "save");
						break;
					}
					system("pause");
				}
			}
			break;
		case 2:			// check info(name, passwd) --> if info doesn't exist, return insert info, else make a account
			sign_up(user);
			break;
		default:
			count = -1;
			break;
		}
	
		if(count < 0) {
			printf("****************************************\n*\tATM is done!!\n*\tHave a nice day!!\n****************************************\n");
			if(count != -2) break;
		}

		system("pause");
		system("cls");
	}

	free(user);

	return 0;
}
// login function
int login_info(user_Data *user) {
	printf("****************************************\n*\tID : ");
	gets(user->name);
	printf("*\tPW : ");
	gets(user->passwd);
	return check_info(user, 0);
}
// ID and PW check function
int check_info(user_Data *user, int cnt) {
	int i;
	for(i = 1; i < MAX_USER; i++) {
		if(i == cnt) {
			i++;
			continue;
		}
		if(!strcmp((user-cnt+i)->name, user->name)) break;
	}
	// If you enter to login mode, this is check whether or not account is exist.
	if(i == MAX_USER && cnt == 0) {
		printf("*\tAccount doesn't exist!!\n*\tPlease sign up.\n");
		memset(user->name, 0, sizeof(user->name));
		i = 0;
	}
	// If you enter to sign up mode, this is check whether or not same name is exist.
	else if(i != MAX_USER && cnt != 0) {
		printf("*\tThis ID is already exist.\n*\tPlease sign up again.\n");
		i = 0;
	}
	// Login password check. When enter to sign up mode, user->passwd is empty. So strcmp(user->passwd, "") have false value.
	// If between user->passwd and (user+i)->passwd is correct, strcmp() value is false. If that is incorrect, this condition is work!
	if(strcmp(user->passwd, "") && strcmp(user->passwd, (user+i)->passwd)) {
		printf("*\tWrong password!\n*\tPlease try again.\n");
		i = 0;
	}
	return i;
}
// New sign up function
void sign_up(user_Data *user) {
	int i, tmp, count;
	// Find out empty space
	for(i = 1; i < MAX_USER; i++) if(!strcmp((user+i)->name, "")) break;
	count = i;
	srand(time(NULL));			// Randomize using time
	printf("****************************************\n*\tEnter to your ID : ");
	gets((user+count)->name);
	if(check_info(user+count, count+1) == 0) {
		memset((user+count)->name, 0, sizeof(user->name));		// Memory setting to zero
		return;
	}
	printf("*\tEnter to your PW : ");
	gets((user+count)->passwd);
	// Insert into account number randomize for each of member
	while(1) {
		if((tmp = (rand() % 10000)) > 999) {			// over 1000, maximum 9999
			for(i = 1; i < MAX_USER; i++) if((user+i)->account == tmp) break;	// can't same account number
			if(i == MAX_USER) {
				(user+count)->account = tmp;
				break;
			}
		}
	}
	printf("*\tYour Account Number : %d\n", (user+count)->account);
}
// Deposit after login function
int depo_info(char *pw) {
	int chk_bal = 0;
	if(check_password(pw) == 1) {
		system("cls");
		printf("****************************************\n*\tHow much do you deposit?\n*\tAmount : ");
		scanf_s("%d", &chk_bal);
		fflush(stdin);
		if (chk_bal < 0) {
			printf("*\tDon't use minus sign!\n*\tPlease try again.\n");
			chk_bal = 0;
		}
	}
	else printf("*\tWrong password!\n*\tPlease try again.\n");
	return chk_bal;
}
// Withdraw after login function
int withdraw_info(char *pw, int bal) {
	int chk_bal = 0;
	if(check_password(pw) == 1) {
		system("cls");
		printf("****************************************\n*\tHow much do you withdraw?\n*\tAmount : ");
		scanf_s("%d", &chk_bal);
		fflush(stdin);
		if (chk_bal < 0) {
			printf("*\tDon't use minus sign!\n*\tPlease try again.\n");
			chk_bal = 0;
		}
		else if(bal < chk_bal) {
			printf("*\tYou don't have enough money!\n*\tYour balance is %d won\n", bal);
			chk_bal = 0;
		}
	}
	else printf("*\tWrong password!\n*\tPlease try again.\n");
	return chk_bal;
}
// transfer account after login function
void transfer(user_Data *user, int cnt) {
	int chk_bal = 0, chk_acc = 0, i;
	if(check_password(user->passwd) == 1) {
		system("cls");
		printf("****************************************\n*\tHow much are you going to spend?\n*\tYour Account : ");
		scanf_s("%d", &chk_acc);
		fflush(stdin);
		if(chk_acc == user->account) {			// user's account check
			printf("*\tOther Account : ");
			scanf_s("%d", &chk_acc);
			fflush(stdin);
			for(i = 0; i < MAX_USER; i++) {
				if(chk_acc == (user-cnt+i)->account) {		// other's account check
					printf("*\tSend Money : ");
					scanf_s("%d", &chk_bal);
					fflush(stdin);
					if (chk_bal < 0) {
						printf("*\tDon't use minus sign!\n*\tPlease try again.\n");
						chk_bal = 0;
					}
					else if(user->balance < chk_bal) printf("*\tYou don't have enough money!\n*\tYour balance is %d won\n", user->balance);
					else {
						printf("*\tSuccessful transfer!\n*\tNow your balance is %d won\n", user->balance-=chk_bal);	// deduct user's balance
						(user-cnt+i)->balance+=chk_bal;	// increase other's balance
					}
					return;
				}
			}
			printf("*\tOther Account doesn't exist!\n*\tPlease check other account.\n");
		}
		else printf("*\tYour Account number is wrong!\n*\tPlease try again.\n");
	}
	else printf("*\tWrong password!\n*\tPlease try again.\n");
}
// Change password after login function
void change_pw(user_Data *user) {
	if(check_password(user->passwd) == 1) {
		system("cls");
		memset(user->passwd, 0, sizeof(user->passwd));
		printf("****************************************\n*\tPlease input your new password.\n*\tNew PW : ");
		gets(user->passwd);
		printf("*\tDon't forget your new password.\n*\tNew password is %s\n", user->passwd);
	}
	else printf("*\tWrong password!\n*\tPlease try again.\n");
}
// One more check password after login function
int check_password(char *pw) {
	char chk_pw[16] = {0,};
	int ret = 0;
	printf("\tPlease, input your password again.\n*\tPassword : ");
	gets(chk_pw);
	if(!strcmp(chk_pw, pw)) ret = 1;
	return ret;
}
// Save or load user data using file I/O
void datas(user_Data *user, char *sel) {
	int i = 1, cnt = 0, cur = 0;
	char *tmp = (char*)malloc(sizeof(int));
	memset(tmp, 0, sizeof(int));
	fp = fopen("D:\\user_data.txt", "a+");			// If you don't have file, it works make a file.
	if(!strncmp(sel, "load", 4)) {				// load file and save data in user structure.
		sel = (char*)malloc(MAX_USER);
		fp = fopen("D:\\user_data.txt", "r");
		while(1) {
			memset(sel, 0, sizeof(sel));
			fseek(fp, cur, SEEK_CUR);
			fgets(sel, MAX_USER, fp);
			if(strlen(sel) < 5) break;
			cur += strlen(sel)+1;
			strcpy((user+i)->name, strtok(sel, ","));	// divide tokenized ',' using strtok(). name, password, account number, balance
			strcpy((user+i)->passwd, strtok(NULL, ","));
			strcpy(tmp, strtok(NULL, ","));
			while(1) {
				if(isdigit(*(tmp+cnt))) {
					(user+i)->account *= 10;
					(user+i)->account += *(tmp+(cnt++)) - '0';
				}
				else {
					cnt = 0;
					break;
				}
			}
			strcpy(tmp, strtok(NULL, ","));
			while(1) {
				if(isdigit(*(tmp+cnt))) {
					(user+i)->balance *= 10;
					(user+i)->balance += *(tmp+(cnt++)) - '0';
				}
				else {
					cnt = 0;
					break;
				}
			}
			i++;
			rewind(fp);
		}
	}
	else if(!strncmp(sel, "save", 4)) {			// save data in a file.
		sel = (char*)malloc(MAX_USER);
		fp = fopen("D:\\user_data.txt", "w+");
		while(1) {
			if(i == MAX_USER || (user+i)->account == NULL) break;
			memset(sel, 0, sizeof(sel));
			fprintf(fp, "%s,%s,%d,%d\n", (user+i)->name, (user+i)->passwd, (user+i)->account, (user+i)->balance);
			i++;
		}
	}
	fclose(fp);
}
