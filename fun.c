#include "fun.h"
void GeneratePassword(char*password){
	for(int i=0;i<7;i++){
		password[i]='A'+rand()%26;
	}
	password[7]='\0';
}

int AdminMainChoice;
int AdminSubChoice;
void AdminMenu(){
	printf("please choose from this list\n");
	printf("1-create new acount\n");
	printf("2-open existing acount\n");
	printf("3-exit\n");
	scanf("%d",&AdminMainChoice);
	if(AdminMainChoice==1){
		CreateNewAcc();
	}
	else if(AdminMainChoice==2){
		BankAcount* ClientIndex=ClientVerification();
		if(ClientIndex!=NULL){
        AdminSubMenu(ClientIndex);}		
	}
	else if(AdminMainChoice==3){
		exit(0);
	}
}

void AdminSubMenu(BankAcount* ClientIndex){
	printf("please choose from this list\n");
	    printf("1-make transaction\n");
	    printf("2-change acount status\n");
	    printf("3-get cash\n");
		printf("4-deposit in acount\n");
		printf("5-return to main menu\n");
	    scanf("%d",&AdminSubChoice);
		if(AdminSubChoice==1){
			MakeTransaction(ClientIndex);
		}
		if(AdminSubChoice==2){
			ChangeAccStatus(ClientIndex);
		}
		if(AdminSubChoice==3){
			GetCash(ClientIndex);
		}
		if(AdminSubChoice==4){
			Deposit(ClientIndex);
		}
		if(AdminSubChoice==5){
			AdminMenu();
		}
}

void ModeMenu(){
printf("please choose mode\n1-admin\n2-client\n3-exit\n");
int mode; 	
scanf("%d",&mode);
if(mode==1){
AdminVerification();	
	
} 
else if(mode==2){
BankAcount* ClientIndex=ClientVerification();
if(ClientIndex!=NULL){
    ClientMenu(ClientIndex);}	
}
else if(mode==3){
exit(0);	
}
else{printf("invalid input");}	
}

int ClientChoice;
void ClientMenu(BankAcount* ClientIndex){
	printf("please choose from this list\n");
	    printf("1-make transaction\n");
	    printf("2-change acount password\n");
	    printf("3-get cash\n");
		printf("4-deposit in acount\n");
		printf("5-return to main menu\n");
	    scanf("%d",&ClientChoice);
		if(ClientChoice==1){
			MakeTransaction(ClientIndex);
		}
		if(ClientChoice==2){
			ChangePassword(ClientIndex);
		}
		if(ClientChoice==3){
			GetCash(ClientIndex);
		}
		if(ClientChoice==4){
			Deposit(ClientIndex);
		}
		if(ClientChoice==5){
			ModeMenu();
		}
}

int NumOfAcounts=0;
BankAcount acounts[100];
static int acountIDcounter=30000;

void CreateNewAcc(){BankAcount acc;
    acc.status=A; 
	
	GeneratePassword(acc.password);
	
	acc.BankAcountID=acountIDcounter++;
	
	printf("please enter your full name\n");	
    getchar(); // ask about these 3 lines
    fgets(acc.name, 100, stdin);
    acc.name[strcspn(acc.name, "\n")] = '\0';
	
	printf("please enter your address\n");	
    getchar(); // 
    fgets(acc.address, 100, stdin);
    acc.address[strcspn(acc.address, "\n")] = '\0';
	
    printf("please enter your age\n");
	scanf("%d",&acc.age);
	
	printf("please enter your National ID\n");
	scanf("%d",&acc.NationalID);
	
	printf("please enter your Balance\n");
	scanf("%f",&acc.balance);	
	
    acounts[NumOfAcounts++] = acc;

    printf("acount created\nyour password is %s\nyour bank acount ID is %d\n",acc.password,acc.BankAcountID);
}

char username[10],adminpass[10];
void AdminVerification(){
	printf("enter admin username\n");
	scanf("%s",username);
	printf("enter admin password\n");
	scanf("%s",adminpass);
	if(strcmp(username,ADMIN_USERNAME)==0&&strcmp(adminpass,ADMIN_PASSWORD)==0){
		AdminMenu();
	}
else printf("invalid\n");}

	
BankAcount* ClientVerification(){
	int clientID;
    char clientPass[8];
    int valid=0;
	printf("enter client ID\n");
	scanf("%d",&clientID);
	printf("enter Client password\n");
	scanf("%s",clientPass);
	for(int i=0;i<100;i++){
		if (acounts[i].BankAcountID==clientID&&strcmp(acounts[i].password,clientPass)==0){
			if(acounts[i].status==A){
				valid=1;
				//SubMenu(&acounts[i]);
				return &acounts[i];
			}
		}
	}		
	if(!valid) {printf("invalid\n");
	return NULL;}
}	

void MakeTransaction(BankAcount* ClientIndex){
	
int valid=0;
int RecieverID;
int RecieverIndex;
float amount;
printf("enter receiver ID\n");
	scanf("%d",&RecieverID);	
	for(int i=0;i<100;i++){
		if (acounts[i].BankAcountID==RecieverID){
			if(acounts[i].status==A){
				valid=1;
				RecieverIndex=i;
			}
		}
	}
if(valid){
printf("enter the amount you want to transfer");
scanf("%f",&amount);
if(amount>ClientIndex->balance){printf("you dont have enough money");}
else{
	ClientIndex->balance -=amount;
	acounts[RecieverIndex].balance +=amount;
	printf("your new balance is:%f",ClientIndex->balance);
}	
}
else if(!valid) printf("invalid receiver data\n");	
};

void ChangeAccStatus(BankAcount* ClientIndex){
	
	char NewAccStat; 
	printf("please enter your new acount status:\nA for active\nR for restricted\nC for closed\n");
	scanf("%s",&NewAccStat);
	if (NewAccStat == 'A') ClientIndex->status = A;
    else if (NewAccStat == 'R') ClientIndex->status = R;
    else if (NewAccStat == 'C') ClientIndex->status = C;
    else printf("Invalid input.\n");
}

void GetCash(BankAcount* ClientIndex){
	float amount;
	
	printf("enter the amount you want to get");
    scanf("%f",&amount);
    if(amount>ClientIndex->balance){printf("you dont have enough money");}
else{
	ClientIndex->balance -=amount;	
	printf("your new balance is:%f",ClientIndex->balance);
}	
}

void Deposit(BankAcount* ClientIndex){
	float amount;
	
	printf("enter the amount you want to deposit");
    scanf("%f",&amount);
	ClientIndex->balance +=amount;	
	printf("your new balance is:%f",ClientIndex->balance);
}	

void ChangePassword(BankAcount* client) {
    char oldPass[8];
    char newPass[8];
    char confirmPass[8];
    printf("Enter current password: ");
    scanf("%s", oldPass);
    if (strcmp(client->password, oldPass) != 0) {
        printf(" Wrong password.\n");
        return;    }
    printf("Enter new password (7 characters max): ");
    scanf("%s", newPass);    
    strncpy(client->password, newPass, 7);
    client->password[7] = '\0'; 
    printf(" Password changed successfully.\n");
}

