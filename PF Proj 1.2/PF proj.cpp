#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<cstdlib>
#include<stdio.h>
using namespace std;
struct USER {
	string ID;
	string Password;
};
struct ADMIN {
	string ID;
	string Password;
};
struct CAR {
	string Numplate;
	string color;
	string name;
};
void homepage();
void logmenu();
void customerservice();
void addcar();
void availcars();
void rentcar();
void returncar();
void generatereport();
float rentcalculate(float days,float perhour);
bool authentication(string ID, string password, int input);
int main()
{
	system("color 01");
	int input;
	string ID, password;
	homepage:
	homepage();
	cin >> input;
	switch (input)
	{
		case 1:                                                                           //Case 1 is CUSTOMER Side
		{
			logmenu:
			logmenu();
			cin >> input;
			if(input==3)
				goto homepage;	
			else
			{
				int r = authentication(ID, password, input);
				if (r)
				{
					customer:
					cin.ignore();
					customerservice();
					cin >> input;
					switch (input)
					{
					case 1:
						availcars();
						goto customer;
					case 2:
						rentcar();
						goto customer;
					case 3:
						returncar();
						goto customer;
					case 4:
						generatereport();
						goto customer;
					case 5:
						goto logmenu;
					}
				}
				else if (r == false)
					goto logmenu;
				break;
			}
		}
		case 2:                                                                           //Case 2 is ADMIN side

		case 3:
			exit(0);
	}
	return 0;
}
void homepage()
{
	system("CLS");
	cout << "\t\t\tCAR RENTAL SERVICE\n\n\n";
	cout << "1. USER\n";
	cout << "2. ADMIN\n";
	cout << "3. Exit\n\n";
}
void logmenu()
{
	system("CLS");
	cout << "\t\t\tCAR RENTAL SERVICE\n\n\n";
	cout << "1. LOG IN\n";
	cout << "2. SIGN IN\n";
	cout << "3. BACK\n";
	cout<<"4. Support\n\n";
	cout << "Writing invalid cresidentials will redirect you to this window.\nFor any queries leave a message for support.\n\n";

}
void customerservice()
{
	system("CLS");
	cout << "\t\t\tCAR RENTAL SERVICE\n\n\n";
	cout << "\n\n1. View avalable cars\n";
	cout << "2. Rent a Car\n";
	cout << "3. Return a Car\n";
	cout << "4. Generate rental report\n";
	cout << "5. BACK\n";
}
bool authentication(string ID,string password,int input)
{
	system("CLS");
	string line;
	switch (input)
	{
		case 1:
		{
			cin.ignore();
			cout << "Enter ID: ";
			getline(cin, ID);
			cout << "Enter Password: ";
			getline(cin, password);
			ifstream userID("userID.txt");
			userID.seekg(0);
			for (int i = 0; (getline(userID, line)); i++)
			{
				if (line == password)
				{
					return true;
					break;
				}
			}
			userID.close();
			return false;
		}
		case 2:
		{	
			cin.ignore();
			cout << "Enter new ID: \n";
			getline(cin,ID);
			cout << "Enter Password: \n";
			getline(cin,password);
			ofstream userID("userID.txt",ios::app);
			userID << ID<<"\n";
			userID << password<<"\n";
			userID.close();
			return true;
		}
		default:
			return false;
	}	
	return false;
}
void availcars()
{
	cin.ignore();
	system("CLS");
	string line;
	ifstream readcar("availcars.txt");
	cout << "\n\n\n";
	for (int i = 1; (getline(readcar, line)); i++)
	{
		cout << line;
		cout << endl<<endl;
	}
	readcar.seekg(0);
	readcar.close();
	system("pause");
}
void addcar()
{
	cin.ignore();
	system("CLS");
	CAR newcar;
	ofstream addcar("availcars.txt",ios::app);
	cin.ignore();
	cout << "\nEnter car name: (example: CompanyName CarName)\n";
	getline(cin, newcar.name);
	cout << "Enter numberplate: (example: ABC-0000)\n";
	getline(cin, newcar.Numplate);
	cout << "Enter color: \n";
	getline(cin, newcar.color);
	addcar << newcar.name << " | " << newcar.Numplate << " | " << newcar.color << " | ";
	addcar.seekp(0);
	addcar.close();
	system("pause");
}

void rentcar() 
{
	cin.ignore();
	system("CLS");
	string carwanted;
	cout << "\nWrite the name of the car you want to rent: ";
	cin >> carwanted;
	ifstream fileavail("availcars.txt");
	if (!fileavail) {
		cout << "Error: Unable to open available cars file.\n";
		return;
	}
	ofstream filerent("rentedcar.txt", std::ios::app);
	ofstream filereport("reportgenerated.txt", std::ios::app);
	ofstream filetemp("temporary.txt");
	if (!filerent || !filereport || !filetemp) {
		cout << "Error: Unable to open necessary files.\n";
		return;
	}

	string line;
	while (getline(fileavail, line)) 
	{
		if (!line.find(carwanted)) {
			filerent << line << endl;
			filereport << line << "\t| Rented" << endl;
		}
		else {
			filetemp << line << endl;
		}
	}

	cout << "\nCar successfully rented.\n";

	filerent.seekp(0);
	filereport.seekp(0);
	filetemp.seekp(0);
	fileavail.close();
	filerent.close();
	filereport.close();
	filetemp.close();

	if (remove("availcars.txt") != 0 || rename("temporary.txt", "availcars.txt") != 0)
	{
		cout << "Error: Unable to update available cars file.\n";
	}
	system("pause");
}
void generatereport()
{
	system("CLS");
	string line;
	ifstream file("reportgenerated.txt");
	cout << "\nReport Generated...\n";
	while (getline(file, line))
	{
		cout << line << endl;
	}
	file.seekg(0);
	file.close();
	system("pause");
}
void returncar()
{
	system("CLS");
	cin.ignore();
	string line, cartoreturn;
	ifstream filerent("rentedcar.txt");
	if (!filerent)
	{
		cout << "\nUnable to open rented cars file.\n";
	}
	ofstream fileavail("availcars.txt",ios::app);
	ofstream filereport("reportgenerated.txt", ios::app);
	ofstream filetemp("temporary.txt");
	if (!fileavail || !filereport || !filetemp)
	{
		cout << "\nunable to open file.\n";
	}
	cout << "\nEnter the name of the car you want to return: ";
	getline(cin, cartoreturn);
	while (getline(filerent, line))
	{
		if (line.find(cartoreturn) != std::string::npos)
		{
			fileavail << line << endl;
			filereport << line <<"\t| Returned"<< endl;
		}
		else
			filetemp << line << endl;
	}
	fileavail.seekp(0);
	filereport.seekp(0);
	filetemp.seekp(0);
	filerent.close();
	fileavail.close();
	filereport.close();
	filetemp.close();
	if (remove("rentedcar.txt")!=0 || rename("temporary.txt", "rentedcar.txt")!=0)
	{
		cout << "\nError,unable to update availcars file.\n";
		return;
	}
	system("pause");
}
float rentcalculate(float days,float perhour)
{
	float price = days * perhour;
	return price;
}
