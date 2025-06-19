#ifndef FUN_H
#define FUN_H
#include <string.h>
#include<stdio.h>
#include <stdlib.h>


#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "1234"

typedef enum{A,C,R}AccStat;

typedef struct{
	char name[100];
	char address[100];
	int age;
	int NationalID;
	float balance;
	AccStat status;
	char password[8];
	int BankAcountID;
}BankAcount;

void GeneratePassword(char*password);

BankAcount* ClientVerification();
void CreateNewAcc();
void AdminMenu();
void ModeMenu();
void ClientMenu(BankAcount* ClientIndex);
void ChangePassword();
void AdminSubMenu();
void AdminVerification();
void Deposit(BankAcount* ClientIndex);
void GetCash(BankAcount* ClientIndex);

void MakeTransaction(BankAcount* ClientIndex);
void ChangeAccStatus(BankAcount* ClientIndex);
#endif