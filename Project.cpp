#include<iostream>
#include<fstream>
#include "conio.h" //GCC conio.h , File attached in project
#include<iomanip>
#include<windows.h>

using namespace std;

/* **************************************************
                  	CLASSES
***************************************************** */

class Account
{
	public:
	int acno;
	char name[20];
	int amt;
	char type;
	
	
		void makeacc(int ac)
		{
			acno=ac;
			cin.ignore();
			cout<<"\nEnter Name : ";
			cin.getline(name,20);
			cout<<"\nEnter Account Type [(C)urrent||(S)avings] : ";
			cin>>type;
			type=toupper(type);
			X:
			cout<<"\nEnter Amount to be deposited [Current(>5000)||Saving(>1000)] :";
			cin>>amt;
			if(amt<5000)
			{
				if(type=='C')
				{
					cout<<"\nError . Minimum amount = 5000 \n\n";
					cin.ignore();
					goto X;
				}
				else if(type=='S'&& amt<1000)
				{
					cout<<"\nError . Minimum amount = 1000 \n\n";
					cin.ignore();
					goto X;
				}
				
			}
			system("cls");
					
		}
		
		void modify(int acno)
		{
			int flag=0;
			char ch,ch2;
			cout<<"The Selected account is "<<acno;
			cout<<"\nDo you want to modify this account? (Y/N)";
			cin>>ch;
			if(ch=='y'||ch=='Y')
			{
				cin.ignore();
				cout<<"Update Name ? (Y/N)";
				cin>>ch2;		
				if(ch2=='y'||ch2=='Y')
				{	
					cin.ignore();
					cout<<"Enter new name : ";					
					cin.getline(name,20);
					flag=1;
					
				}
				cout<<"Update Account Type? (Y/N)";
				cin>>ch2;
				 if(ch2=='y'||ch2=='Y')
				{
					cout<<"Enter new account type : ";
					cin>>type;
					type=toupper(type);
					flag=1;
					
			    }
						
			}
		   		
		
			else if(flag==0 && ch=='n' || ch=='N')
		   		{
		   			
					cout<<"Nothing has been modified. Exiting...Press Any Key... ";
		  			getch();		   
	      		}  
			system("cls");
		}
		void draw(int x)
		{
			amt-=x;						
		}
		void add(int x)
		{
			amt+=x;	
		}
		int retamt()
		{
			return amt;
		}
		int retacc()
		{
			return acno;
		}
		void showacc()
		{
			cout<<"\n\nAccount Number : ";
			cout<<acno;
			
			cout<<"\n\nName : ";
			cout<<name;
			cout<<"\n\nAccount Type [(C)urrent||(S)avings] : ";
			
			cout<<type;
			cout<<"\n\nBalance : ";
			cout<<amt;				
		}
		void display()
		{
			cout<<"\n\t\t\t   "<<acno<<setw(28)<<name<<setw(21)<<amt<<setw(15)<<type;
		}
};
/**END OF CLASS**/

/****function Declarations*****/
void file_makeacc(int);
void file_del(int);
void file_modify(int);
void file_draw(int);
void file_display(int);
void file_deposit(int);
void file_displayAll();
/***End***/


int main()
{	
	int n,num;
	cout<<"\t\t\t\t\t\t    LOADING\n\n";
	for(int i=1;i<120;i++)
	{
		if(i%5==0)
		Sleep(100);
		cout<<"0";		
	}
	system("cls");
	cout<<"\n\n\t\t\t\t\t\tBankSystem2k16 v6.9";
	
	do{
	system("Color 0A");
	cout<<"\n\n\n\t1.ADD ACCOUNT ";
	cout<<"\n\n\t2.CLOSE ACCOUNT ";
	cout<<"\n\n\t3.MODIFY ACCOUNT ";
	cout<<"\n\n\t4.WITHDRAWAL ";
	cout<<"\n\n\t5.DEPOSIT ";
	cout<<"\n\n\t6.BALANCE INQUIRY ";
	cout<<"\n\n\t7.DISPLAY ALL A/C DETAILS ";
	cout<<"\n\n\t8.EXIT \n";
	cout<<"\n\n\tEnter Choice (1-7) : ";
	cin>>n;
	system("cls");
		switch(n)
		{
		case 1:	
					cout<<"\n\n\tEnter the A/C no : ";
					cin>>num;
					file_makeacc(num);
					break;
		case 2:
					cout<<"\n\n\tEnter the A/C no. : "; 
					cin>>num;
					file_del(num);
					break;
		case 3:
					cout<<"\n\n\tEnter the A/C no. : ";  
					cin>>num;
					file_modify(num);
					break;
		case 4:
					cout<<"\n\n\tEnter the A/C no. : ";  
					cin>>num;
					file_draw(num);
					break;
		case 5:
					cout<<"\n\n\tEnter the A/C no. : ";  
					cin>>num;
					file_deposit(num);
					break;
		case 6:
					cout<<"\n\n\tEnter the A/C no. : ";
					cin>>num;
					file_display(num);
					break;
		case 7:
					file_displayAll();
					break;
	    case 8:  
	    			cout<<"\n\n\tThanks for working with BankersDelightV6.9";
					return 0;
					exit(0);
								
				    default :
					cout<<"\nInvalid Input...";
					getch();
					system("cls");
			     	
		}
		
	}while(1==1);
	

}

/***********************
		FUNCTIONS
***********************/

void file_makeacc(int n)
{
	int flag=0;
	Account ac;
	fstream file,File;
	file.open("Accounts.txt",ios::in|ios::binary);
	
	if(file.peek()!=-1) 
	{	
		while(!file.eof())
		{		
			file.read((char *)&ac , sizeof (Account));
			
			if(ac.retacc()==n)				
			{
				cout<<"Same Account Exists ... Add Account with a different number!";
				flag=1;  
				break;
		    }
			 
		}
			    	 		 		
	}
	file.close();
	
	if(flag==0)
	{
		File.open("Accounts.txt",ios::in|ios::binary|ios::app);
	  	ac.makeacc(n);
		File.write((char *)&ac , sizeof (Account));
		File.close();
	} 
	
}

void file_modify(int n)
{	
	bool flag=false;
	Account ac;
	fstream file;
	file.open("Accounts.txt",ios::in|ios::out|ios::binary);
		if(!file)
	{
		cout<<"No Accounts Found! ";
		getch();
	}
	
	while(!file.eof()&&flag==false)
	{
	  file.read((char *)&ac , sizeof (Account));
		
   	if(ac.retacc()==n)
   	{
   		ac.showacc();   	
		getch()	;		
		cout<<"\n\nEnter New Details\n\n";
		ac.modify(n) ; 
	
			file.seekp(-(sizeof(Account)),ios::cur);
			file.write((char *) &ac, sizeof(Account));
			cout<<"\n\nRecord Updated";
			flag=true;
	   
	}
}
	file.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist!";
		getch();
		system("cls");
	system("cls");
}
void file_del(int n)
{
	Account ac;
	fstream file,file2;
	file.open("Accounts.txt",ios::in|ios::binary);
	file2.open("Temp.txt",ios::out|ios::binary);
	
	if(!file)
	{
		cout<<"No Accounts Found! ";
		getch();
	}
	while(!file.eof())
	{
		file.read((char *)&ac,sizeof(Account));
		
			if(ac.retacc()!=n)
		{
			file2.write((char *) &ac, sizeof(Account));
		}
	}
	file.close();
	file2.close();	
	remove("Accounts.txt");
	rename("Temp.txt","Accounts.txt");
	cout<<"Processing...";
	Sleep(500);
	cout<<"\nAccount has been removed! ";
	getch();
	system("cls");
}
void file_draw(int n)
{
	int amt,flag=0,flag2=0;
	Account ac;
	fstream file;
	file.open("Accounts.txt",ios::in|ios::out|ios::binary);
	if(!file)
	{
		cout<<"No Accounts Found! ";
		getch();
	}
	
	while(!file.eof())	
	{	
		file.read((char *)&ac,sizeof(Account));
		
		if(ac.retacc()==n)
		{
			flag=1;
			ac.showacc();
			cout<<"\n\nEnter the amount to be withdrawn : ";
			cin>>amt;
			if(ac.retamt()>=amt)
			ac.draw(amt);
			else
			{
			flag2=1;
		    }
			int pos=(-1)*(int)(sizeof(ac));
			file.seekp(pos,ios::cur);
			file.write((char *) &ac, sizeof(Account));
			if(flag2==0)
			cout<<"\n\n\t Success! The current balance ="<<ac.retamt();
			else
			cout<<"Sorry! Insufficient Balance...";
			getch();
			system("cls");	
			break;
		}
		
	}
	file.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist!";
		getch();
		system("cls");
}
void file_deposit(int n)
{
	int amt,flag=0;
	Account ac;
	fstream file;
	file.open("Accounts.txt",ios::in|ios::binary|ios::out);
	if(!file)
	{
		cout<<"No Accounts Found! ";
		getch();
	}
	
	while(!file.eof())	
	{  
		file.read((char *)&ac,sizeof(Account));
	
		if(ac.retacc()==n)
		{	
			flag=1;
			ac.showacc();
			cout<<"\n\nEnter the amount to be deposited : ";
			cin>>amt;
			ac.add(amt);
			int pos=(-1)*(int)(sizeof(ac));
			file.seekp(pos,ios::cur);
			file.write((char *) &ac, sizeof(Account));
			cout<<"\n\n\t Success! The current balance ="<<ac.retamt();
			getch();
			system("cls");	
			break;
		}		
	}
	file.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist!";
		getch();
		system("cls");	
}
void file_display(int n)
{
	Account ac;
	int flag=0;
	fstream file;
	file.open("Accounts.txt",ios::binary|ios::out|ios::in);
	if(!file)
	{
		cout<<"No Accounts Found! ";
		getch();
	}	
	
	while(!file.eof())
	{		
		file.read((char *)&ac , sizeof (Account));   	
		
		if(ac.retacc()==n)
		{
			cout<<"\nBALANCE DETAILS\n";
			ac.showacc();
			flag=1;
			getch();
			break;
			
		}
	}
	file.close();
	
	if(flag==0)
		cout<<"\n\nAccount number does not exist!";
		getch();
		system("cls");
}
void file_displayAll()
{	
	
	Account ac;
	fstream file;
	file.open("Accounts.txt",ios::binary|ios::out|ios::in);
	if(!file)
	{
		cout<<"No Accounts Found! ";
		getch();
	}	
	else
	{
	cout<<"Displaying all A/C information...";	
	cout<<"\n\n\n\n\t\t|=_______________________________________________________________________________=|";
	cout<<"\n\t\t|        A/C No.                  Name               Balance          Type        |";
	cout<<"\n\t\t|=================================================================================|\n";
	
	
	while(!file.eof())
	{		
		file.read((char *)&ac , sizeof (Account));   	
		
		if(file.eof())
		break;	

		ac.display();
		cout<<"\n";
			
	}
	file.close();
}
	getch();
	system("cls");
   
}
/******************END OF PROJECT*************************/
		

