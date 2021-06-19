/************************************************
 * Banking Project with C++ and .dat file
 * Using classes, basic file handling techniques
 * Used basic OOP concepts like Data Abstraction
************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
using namespace std;

/****************************
 * Class used for User Data
****************************/

const int adminpin = 6399;
class account
{
	long int acno;
	char name[50];
	double deposit;
	int pin;
	char type;
public:
	int create_account();	
	void show_account() const;	//Balance Enquiry
	void modify();	//Agent access of data correction
	void dep(double);	
	void draw(double);	
	void report() const;	//Agent access of complete data file
	long int retacno() const;    
	int retpin() const;	
	double retdeposit() const;	
	char rettype() const;	
};         //class ends here

int account::create_account()
{
	cout<<"\nEnter The account No. :";
	cin>>acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	if( type != 'C' && type != 'S' )
	{
	 cout<<"\n Invalild\n";
	 return (-1);
	}
	cout<<"\nEnter the Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	if(( type =='C') && ( deposit < 1000 ) )
	{
		cout<<"\n\n\nInsufficient balance to create account !!..";
		return (-1);
	}
	else if (( type =='S') && ( deposit < 500 ) )
	{
		cout<<"Insufficient balance to create account !!..";
		return (-1);
	}
	cout<<"\nEnter the 4digit pin number : ";
	cin>>pin;
	

	cout<<"\n\n\nAccount Created..";
	return 0;
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	start:
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	if( type != 'C' && type != 'S' )
	{
	 cout<<"\n Invalild\n";
	 goto start;
	}
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
	cout<<"\nModify pin number : ";
	cin>>pin;
}

	
void account::dep(double x)
{
	deposit+=x;
}
	
void account::draw(double x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<acno<<setw(10)<<"\t"<<name<<setw(10)<<"\t"<<type<<setw(6)<<" "<<deposit<<endl;
}

	
long int account::retacno() const
{
	return acno;
}

int account::retpin() const
{
	return pin;
}

double account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


/***************************************************************
    	       Function declarations
***************************************************************/
void write_account();	//function to write record in binary file
void display_sp(long int);	//Balance Enquiry
void modify_account(long int);	//Agent access modification of data
void delete_account(long int);	//Agent access data deletion
void display_all();		//Agaent access complete data set
void deposit_withdraw(double,double); 
void intro();	// Banner

/***************************************************************
           	Heart of the program
***************************************************************/


int main()
{
	system("color E0");
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		system("color F1");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) and Press Enter : ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			system("color F1");
			write_account();
			break;
		case '2':
			system("color B0");
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			system("color B0");
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			system("color B0");
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			system("color A0");
			display_all();
			break;
		case '6':
			system("color A0");
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			system("color A0");
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			system("color E0");
			cout<<"\n\n\tThanks Happy Banking ";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


/***************************************************************
    	           Add Data to system
***************************************************************/

void write_account()
{
	account ac;
	int checker;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	checker = ac.create_account();
	if( checker == 0 )
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

/***************************************************************
   	                      Balance Enquiry	
***************************************************************/

void display_sp(long int n)
{
	account ac;
	int pass;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			cout<<"\nEnter the 4digit pin Number : ";
			cin>>pass;
			if( pass == ac.retpin() )
			ac.show_account();
			else
			cout<<"\nInvalid pin number\n Be truthful to yourself\n";
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


/***************************************************************
 *               Modifying records by Agent
***************************************************************/

void modify_account(long int n)
{
	bool found=false;
	account ac;
	char c;
	int pass;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			cout<<"\nEnter the admin pin Number : ";
			cin>>pass;
			if( pass == adminpin )
			{
				ac.show_account();
				cout<<"\n\nEnter The New Details of account"<<endl;
				ac.modify();
				int pos=(-1)*static_cast<int>(sizeof(account));
				File.seekp(pos,ios::cur);
				File.write(reinterpret_cast<char *> (&ac), sizeof(account));
				cout<<"\n\n\t Record Updated";
			}
			else
			{
				cout<<"\nInvalid pin number\n Be truthful to yourself\n";
			}
			found=true;
		  }
	}
	File.close();
	if(found==false)
	{
		cout<<"\n\n Record Not Found ";
		cout<<"\n\n Do you want to create one ? \n\n( Y - Yes ; N - No ):  ";
		cin>>c;
		c = toupper(c);
		if( c == 'Y' )
		{
			write_account();
		}
		return;
	}
}

/***************************************************************
     	     Bank Agent deletion of account
***************************************************************/


void delete_account(long int n)
{
	account ac;
	int pass;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			cout<<"\nEnter Admin pin Number : ";
			cin>>pass;
			if( pass == adminpin )			
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
			else
			{
				cout<<"\nWarning!! Invalid Input \n";
				return;
			}
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

/***************************************************************
    	   Bank Agent Access of Complete Data
***************************************************************/

void display_all()
{
	account ac;
	int pass;
	cout<<"\nEnter Admin pin Number : ";
	cin>>pass;
	if( pass == adminpin )	
	{
		ifstream inFile;
		inFile.open("account.dat",ios::binary);
		if(!inFile)
		{
			cout<<"File could not be open !! Press any Key...";
			return;
		}
		cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
		cout<<"====================================================\n";
		cout<<"A/c no.         NAME           Type    Balance\n";
		cout<<"====================================================\n";
		while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
		{
			ac.report();
		}
		inFile.close();
	}
	else
	    cout<<"\nInvalid Entry ! ";
}

/***************************************************************
    	            Withdraw and Deposit
***************************************************************/

void deposit_withdraw(double n, double option)
{
	double amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			int pass;
			cout<<"\nEnter Admin pin Number : ";
			cin>>pass;
			if( pass == adminpin )
			{	
				ac.show_account();
				if(option==1)
				{
					cout<<"\n\n\tTO DEPOSITE AMOUNT ";
					cout<<"\n\nEnter The amount to be deposited";
					cin>>amt;
					ac.dep(amt);
				}
				if(option==2)
				{
					cout<<"\n\n\tTO WITHDRAW AMOUNT ";
					cout<<"\n\nEnter The amount to be withdraw";
					cin>>amt;
					int bal=ac.retdeposit()-amt;
					if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
						cout<<"Insufficience balance";
					else
						ac.draw(amt);
				}
				int pos=(-1)*static_cast<int>(sizeof(ac));
				File.seekp(pos,ios::cur);
				File.write(reinterpret_cast<char *> (&ac), sizeof(account));
				cout<<"\n\n\t Record Updated";
			}
			else
			   cout<<"\nInvalid\n";
				found=true;
	       
         }
	 }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


/***************************************************************
    	            Front page Banner
****************************************************************/


void intro()
{
	cout<<"\n\n\n\t  BANK";
	cout<<"\n\n\t  Virtual Simualtor";
	cout<<"\n\n\t  SYSTEM";
	cout<<"\n\n\n\nCreated by Dev.M association (Press Enter to continue) :";
	cin.get();
}
