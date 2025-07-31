#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <cstring>
#include "Header.h"
using namespace std;

//Function Prototypes
void login(int);
void intro();
int employeecounter();
string getday(int);
int managercounter();
void plantsetter(string);
string plantchecker(string, string);
int planttoindex(string);
//Class Prototypes
class Plant;
class Attendance;
class Employee;
class ManagerManagement;
class ManagerHR;
class ManagerAccountant;
class Administrator;
class Director;
class CEO;


string parser(string);
bool duplicatechecker(string);
void objectremover(Employee*);

//Global Variables
int empcounter = 0;
int mancounter = 0;
int admincounter = 0;

Employee* emps;
ManagerManagement* managerman;
ManagerHR* managerhr;
ManagerAccountant* manageracc;
Plant* plants;
Administrator* admins;




void main() {
	plants = new Plant[4];
	plants[0].setname("Nothern Plant");
	plants[1].setname("Southern Plant");
	plants[2].setname("Eastern Plant");
	plants[3].setname("Western Plant");
	plants[0].datareader();
	plants[1].datareader();
	plants[2].datareader();
	plants[3].datareader();
	admins = new Administrator[4];
	emps = new Employee[employeecounter()];
	managerman = new ManagerManagement[managercounter()];
	managerhr = new ManagerHR[managercounter()];
	manageracc = new ManagerAccountant[managercounter()];
	
	intro();
	system("pause");
}

void CEO::setdata(string name, string cnic, string id, string password, string dateofjoining) {
	this->Name = name;
	this->cnic = cnic;
	this->id = id;
	this->password = password;
	this->dateofjoining = dateofjoining;
}
void CEO::ceomenu() {
	int choice;
	cout << "\n1)Net Investment\n2)Net Profit\n3)Plants Stats\n4)Logout\n";
	cin >> choice;
	switch (choice) {
	case 1:
		cout << "Net Investment: " << (stoi(plants[0].getinvestment()) + stoi(plants[1].getinvestment()) + stoi(plants[2].getinvestment()) + stoi(plants[3].getinvestment()));
		ceomenu();
		break;
	case 2:
		cout << "Net Profit: " << (stoi(plants[0].getprofit()) + stoi(plants[1].getprofit()) + stoi(plants[2].getprofit()) + stoi(plants[3].getprofit())) << endl;
		ceomenu();
		break;
	case 3:
		plants[0].dispplantinfo();
		plants[1].dispplantinfo();
		plants[2].dispplantinfo();
		plants[3].dispplantinfo();
		ceomenu();
		break;
	case 4:
		intro();

		break;
	}
}
void CEO::DisplayData() {
	cout << "Name:" << Name << endl << "Cnic:" << cnic << endl << "ID:" << id << endl << "Date of Joining:" << dateofjoining << endl;
}
void Administrator::setdata(string name, string cnic, string id, string password, string dateofjoining) {
	this->Name = name;
	this->cnic = cnic;
	this->id = id;
	this->password = password;
	this->dateofjoining = dateofjoining;
	plantsetter(id, "Admin");
}
int Administrator::noofemployees() {
	int counter = 0;
	int counter1 = 0;
	string line;
	string inputid, inputpass;
	string parsedid, parsedpass;
	string fid, rank, fname, fpassword, fdoj, fcnic;
	ifstream myfile("logins\\info.txt");
	while (getline(myfile, line)) {

		myfile >> fid;
		fid = parser(fid);
		myfile >> rank;
		myfile >> fpassword;
		myfile >> fname;
		myfile >> fcnic;
		myfile >> fdoj;
		rank = parser(rank);
		fname = parser(fname);
		fpassword = parser(fpassword);
		fdoj = parser(fdoj);
		fcnic = parser(fcnic);
		if (rank == "Employee") {
			if (counter1 < employeecounter()) {
				emps[counter1].setdata(fname, fcnic, fid, fpassword, fdoj);
				plantsetter(fid, "Employee", counter1);
			}
			cout << "\t" << emps[counter1].getplant() << endl;
			if ((emps[counter1].getplant() == plant))
				counter++;
			counter1++;
		}


	}
	return counter;
}
void Administrator::displayatd() {
	Attendance atd;
	string line;
	string data;
	string fid, temp;
	string status;
	int pos1, pos2;
	int daypos = atd.daychecker();
	ifstream filein("attendance\\attendance.txt");
	cout << endl << "ID\t\t" << getday(daypos) << endl;
	while (getline(filein, line)) {
		pos1 = line.find(":");
		fid = line.substr(0, pos1);

		pos1 = (2 * daypos - 2) + 5;
		pos2 = (2 * daypos - 1) + 5;
		data = line.substr(pos1, pos2);

		if (data == "9") {
			status = "Present";
		}
		else
			status = "Absent";
		if (plantchecker(fid, "Employee") == plant) {
			cout << fid << "\t\t" << status << endl;
		}
	}
}
void Administrator::adminmenu() {
	int choice;
	cout << "\n1)Employee Attendance for Today\n2)No of Employees in Plant\n3)Plant Production\n4)Logout\n";
	cin >> choice;
	int index = planttoindex(plant);
	switch (choice) {
	case 1:
		displayatd();
		adminmenu();
		break;
	case 2:
		cout << "Number of Employees in Plant are: " << noofemployees() << endl;
		adminmenu();
		break;
	case 3:
		plants[index].dispstat();
		adminmenu();
		break;
	case 4:
		admincounter--;
		intro();

		break;
	}
}
void Administrator::DisplayData() {
	cout << "Name:" << Name << endl << "Cnic:" << cnic << endl << "ID:" << id << endl << "Date of Joining:" << dateofjoining << endl;
	cout << "Plant:" << plant;
}
void ManagerAccountant::setdata(string name, string cnic, string id, string password, string dateofjoining) {
	this->Name = name;
	this->cnic = cnic;
	this->id = id;
	this->password = password;
	this->dateofjoining = dateofjoining;
	plantsetter(id, "Account");
}
void ManagerAccountant::Employeelist() {
	string line;
	string data;
	string fid, temp;
	int days[5];
	int pos1, pos2;
	ifstream filein("attendance\\attendance.txt");
	cout << "ID\t\tMonday\t\tTuesday\t\tWednessday\t\tThursday\tFriday\n";
	while (getline(filein, line)) {
		pos1 = line.find(":");
		fid = line.substr(0, pos1);
		for (int i = 1; i <= 5; i++) {
			pos1 = (2 * i - 2) + 5;
			pos2 = (2 * i - 1) + 5;
			days[i - 1] = stoi(line.substr(pos1, pos2));
		}

		if (emps[empcounter].getplant() == plant) {
			cout << fid << "\t\t" << days[0] << "\t\t\t" << days[1] << "\t\t\t" << days[2] << "\t\t" << days[3] << "\t\t" << days[4] << endl;
		}
	}
}
void ManagerAccountant::accmenu() {
	int choice;
	int index = planttoindex(plant);
	cout << "\n1)Sales statistics\n2)Plant Statistics\n3)Employee list\n4)Logout\n";
	cin >> choice;
	switch (choice) {
	case 1:
		plants[index].dispplantinfo();
		accmenu();
		break;
	case 2:
		plants[index].dispplantinfo();
		plants[index].dispstat();
		accmenu();
		break;
	case 3:
		Employeelist();
		accmenu();
		break;
	case 4:
		mancounter--;
		intro();

		break;
	}
}
void ManagerAccountant::DisplayData() {
	cout << "Name:" << Name << endl << "Cnic:" << cnic << endl << "ID:" << id << endl << "Date of Joining:" << dateofjoining << endl;
}
void ManagerManagement::setdata(string name, string cnic, string id, string password, string dateofjoining) {
	this->Name = name;
	this->cnic = cnic;
	this->id = id;
	this->password = password;
	this->dateofjoining = dateofjoining;
	plantsetter(id, "Managment");
}
void ManagerManagement::setday() {
	int daypos;
	string stday;
	cout << "\nEnter the day: ";
	cin >> stday;

	string line;
	string data;
	string fid, temp;
	int pos1;
	ifstream filein("attendance\\day.txt");
	ofstream fileout("attendance\\day_temp.txt");
	while (getline(filein, line)) {
		pos1 = line.find(":");
		fid = line.substr(0, pos1);

		if (fid == id) {
			pos1 = (2 * daypos - 2) + 5;
			line.replace(pos1, 1, "9");

		}
		for (int i = 0; i < 2; i++) {
			if (i == 1) {
				if (stday == "Monday" || stday == "monday") {
					daypos = 1;
				}
				else if (stday == "Tuesday" || stday == "tuesday")
					daypos = 2;
				else if (stday == "Wednessday" || stday == "wednessday")
					daypos = 3;
				else if (stday == "Thursday" || stday == "thursday")
					daypos = 4;
				else if (stday == "Friday" || stday == "friday")
					daypos = 5;
			}
			else {
				line += "\n";
				fileout << line;
			}
		}
		switch (daypos) {
		case 1: {
			line = "1:0:0:0:0";
			break;
		}
		case 2: {
			line = "0:1:0:0:0";
			break;
		}
		case 3: {
			line = "0:0:1:0:0";
			break;
		}
		case 4: {
			line = "0:0:0:1:0";
			break;
		}
		case 5: {
			line = "0:0:0:0:1";
			break;
		}
		}
		line += "\n";
		fileout << line;

	}
	filein.close();
	fileout.close();
	remove("attendance\\day.txt");
	rename("attendance\\day_temp.txt", "attendance\\day.txt");
	cout << "Attendace for " << stday << "is Now Open!";
}
void ManagerManagement::managmentmenu() {
	int choice;
	int index = planttoindex(plant);
	cout << "\n1)Set day\n2)Plant Info\n4)logout\n";
	cin >> choice;
	switch (choice) {
	case 1:
		setday();
		managmentmenu();
		break;

	case 2:
		plants[index].dispplantinfo();
		managmentmenu();
		break;
	case 3:

		intro();
		empcounter--;
		break;
	}
}
void ManagerManagement::DisplayData() {
	cout << "Name:" << Name << endl << "Cnic:" << cnic << endl << "ID:" << id << endl << "Date of Joining:" << dateofjoining << endl;
}
void ManagerHR::setdata(string name, string cnic, string id, string password, string dateofjoining) {
	this->Name = name;
	this->cnic = cnic;
	this->id = id;
	this->password = password;
	this->dateofjoining = dateofjoining;
	plantsetter(id, "HR");
}
void ManagerHR::employeeadder() {
	string fid, rank, fname, fpassword, fdoj, fcnic;
	string line;
	ofstream myfile("logins\\info.txt", ios::app);
	ofstream myfile1("logins\\employeelogininfo.txt", ios::app);
	if (!myfile.is_open())
		cout << "cannot open";
	cout << "Enter ID:";
	cin >> fid;
	rank = "Employee";
	cout << "Enter Name:";
	cin >> fname;
	cout << "Enter Password:";
	cin >> fpassword;
	cout << "Enter Cnic:";
	cin >> fcnic;
	cout << "Enter Date of Joining(dd-mm-yy)";
	cin >> fdoj;
	if (!duplicatechecker(fid)) {
		rank = "rank:" + rank + "\n";
		fname = "Name:" + fname + "\n";
		fpassword = "Password:" + fpassword + "\n";
		fdoj = "DateOfJoining:" + fdoj + "\n";
		fcnic = "Cnic:" + fcnic + "\n";
		fid = "ID:" + fid + "\n";
		myfile << fid << rank << fpassword << fname << fcnic << fdoj;
		myfile1 << "\n";
		myfile1 << fid << fpassword;
		myfile.close();
		myfile1.close();
		cout << "Employee is successfuly added!";
	}
	else {
		cout << "Employee with ID " << fid << " already exists!";
		employeeadder();
	}
}
void ManagerHR::employeesearcher() {
	string fid, rank, fname, fpassword, fdoj, fcnic, chkid;
	string line;
	cout << "Enter ID:";
	cin >> chkid;
	ifstream myfile("logins\\info.txt");
	while (getline(myfile, line)) {

		myfile >> fid;
		fid = parser(fid);
		if (fid == chkid) {
			myfile >> rank;
			myfile >> fpassword;
			myfile >> fname;
			myfile >> fcnic;
			myfile >> fdoj;
			rank = parser(rank);
			fname = parser(fname);
			fpassword = parser(fpassword);
			fdoj = parser(fdoj);
			fcnic = parser(fcnic);

			if (rank == "Employee") {
				cout << "Name:" << fname << endl << "Cnic:" << fcnic << endl << "ID:" << fid << endl << "Date of Joining:" << fdoj << endl;
			}
			else {
				cout << "Employee not found";
				employeesearcher();
			}
		}
	}
}
void ManagerHR::leavemarker() {
	string lvid;
	cout << "Enter ID:";
	cin >> lvid;
	Attendance std(lvid);
	std.attendancemarker();
	cout << "Leave for Employee#" << lvid << " is Marked!";
}
void ManagerHR::hrmenu() {
	int choice;
	cout << "\n1)Add a Employee\n2)Search for a Employee\n3)Mark Leave for an Employee\n4)Logout\n";
	cin >> choice;
	switch (choice) {
	case 1:
		employeeadder();
		hrmenu();
	case 2:
		employeesearcher();
		hrmenu();
	case 3:
		leavemarker();
		hrmenu();
	case 4:
		mancounter--;
		intro();

		break;
	}
}
void ManagerHR::DisplayData() {
	cout << "Name:" << Name << endl << "Cnic:" << cnic << endl << "ID:" << id << endl << "Date of Joining:" << dateofjoining << endl;
}
void Employee::setdata(string name, string cnic, string id, string password, string dateofjoining) {
	atd.setid(id);
	this->Name = name;
	this->cnic = cnic;
	this->id = id;
	this->password = password;
	this->WorkingHours = whcalculator(id);
	this->dateofjoining = dateofjoining;
	plantsetter(id, "Employee");
}
int Employee::whcalculator(string id) {
	string line;
	string data;
	string fid;
	int pos1, pos2;
	int wh = 0;

	ifstream cal("attendance\\attendance.txt");
	while (getline(cal, line)) {
		pos1 = line.find(":");
		fid = line.substr(0, pos1);

		if (fid == id) {

			for (int i = 1; i < 5; i++) {
				pos1 = (2 * i - 2) + 5;
				pos2 = (2 * i - 1) + 5;
				data = line.substr(pos1, pos2);
				wh += stoi(data);
			}
		}
	}
	return wh;
}
int Employee::salarycalculator() {
	return WorkingHours * rateperhour;
}
string Employee::getplant() {
	return plant;
}
void Employee::Empmenu() {
	int choice;
	cout << "\n1)Mark Attendance\n2)Check Attendance\n3)Calculate Salary\n4)Logout\n";
	cin >> choice;
	switch (choice) {
	case 1:
		atd.attendancemarker();
		cout << "Your Attendance is Now marked!";
		Empmenu();
		break;
	case 2:
		atd.attendancechecker();
		Empmenu();
		break;
	case 3:
		cout << "Your Current Salary Equals to: " << salarycalculator();
		Empmenu();
		break;
	case 4:
		empcounter--;
		intro();

		break;
	}
}
void Employee::DisplayData() {
	cout << "Name:" << Name << endl << "Cnic:" << cnic << endl << "ID:" << id << endl << "Working Hours:" << WorkingHours << endl << "Date of Joining:" << dateofjoining;
}
void  Director::setdata(string name, string cnic, string id, string password, string dateofjoining) {
	this->Name = name;
	this->cnic = cnic;
	this->id = id;
	this->password = password;
	this->dateofjoining = dateofjoining;

}
void  Director::noofemployees() {
	int choice;
	cout << "For which plant do you want to see Employee salaries for:\n1)Southern Plant\n2)Nothern Plant\n3)Eastern Plant\n4)Western Plant\n";
	cin >> choice;
	switch (choice) {
	case 1: {
		string line;
		string data;
		string fid;
		int pos1, pos2;
		int wh = 0;
		cout << "ID\t\tSalary" << endl;
		ifstream cal("attendance\\attendance.txt");
		while (getline(cal, line)) {
			pos1 = line.find(":");
			fid = line.substr(0, pos1);

			if (plantchecker(fid, "Employee") == "Southern Plant") {

				for (int i = 1; i < 5; i++) {
					pos1 = (2 * i - 2) + 5;
					pos2 = (2 * i - 1) + 5;
					data = line.substr(pos1, pos2);
					wh += stoi(data);
				}
			}
			cout << fid << "\t\t" << (wh * 208) << endl;

		}
		break;
	}
	case 2: {
		string line;
		string data;
		string fid;
		int pos1, pos2;
		int wh = 0;
		cout << "ID\t\tSalary" << endl;
		ifstream cal("attendance\\attendance.txt");
		while (getline(cal, line)) {
			pos1 = line.find(":");
			fid = line.substr(0, pos1);

			if (plantchecker(fid, "Employee") == "Nothern Plant") {

				for (int i = 1; i < 5; i++) {
					pos1 = (2 * i - 2) + 5;
					pos2 = (2 * i - 1) + 5;
					data = line.substr(pos1, pos2);
					wh += stoi(data);
				}

				cout << fid << "\t\t" << (wh * 208) << "\t\t" << plantchecker(fid, "Employee") << endl;
			}
		}
		break;
	}
	case 3: {
		string line;
		string data;
		string fid;
		int pos1, pos2;
		int wh = 0;
		cout << "ID\t\tSalary" << endl;
		ifstream cal("attendance\\attendance.txt");
		while (getline(cal, line)) {
			pos1 = line.find(":");
			fid = line.substr(0, pos1);

			if (plantchecker(fid, "Employee") == "Eastern Plant") {

				for (int i = 1; i < 5; i++) {
					pos1 = (2 * i - 2) + 5;
					pos2 = (2 * i - 1) + 5;
					data = line.substr(pos1, pos2);
					wh += stoi(data);
				}

				cout << fid << "\t\t" << (wh * 208) << endl;
			}
		}
		break;
	}
	case 4: {
		string line;
		string data;
		string fid;
		int pos1, pos2;
		int wh = 0;
		cout << "ID\t\tSalary" << endl;
		ifstream cal("attendance\\attendance.txt");
		while (getline(cal, line)) {
			pos1 = line.find(":");
			fid = line.substr(0, pos1);

			if (plantchecker(fid, "Employee") == "Western Plant") {

				for (int i = 1; i < 5; i++) {
					pos1 = (2 * i - 2) + 5;
					pos2 = (2 * i - 1) + 5;
					data = line.substr(pos1, pos2);
					wh += stoi(data);
				}

				cout << fid << "\t\t" << (wh * 208) << endl;
			}
		}
		break;
	}

	}

}
void  Director::budgetallocator() {
	string budgets[4];
	cout << "Budget for Southern plant: ";
	cin >> budgets[0];
	cout << "Budget for Nothern plant: ";
	cin >> budgets[1];
	cout << "Budget for Eastern plant: ";
	cin >> budgets[2];
	cout << "Budget for Western plant: ";
	cin >> budgets[3];
	string line;
	string data;
	string fid, temp;
	int pos1;
	int counter = 0;
	ifstream filein("logins\\plantinfo.txt");
	ofstream fileout("logins\\plantinfo_temp.txt");
	while (getline(filein, line)) {
		pos1 = line.find(":");
		fid = line.substr(0, pos1);

		if (fid == "Budget") {
			pos1 = 7;
			if (counter == 0) {
				line.replace(pos1, 6, budgets[0]);
				counter++;
			}
			else if (counter == 1) {
				line.replace(pos1, 6, budgets[1]);
				counter++;
			}
			else if (counter == 2) {
				line.replace(pos1, 6, budgets[2]);
				counter++;
			}
			else if (counter == 3) {
				line.replace(pos1, 6, budgets[3]);
				counter++;
			}
		}
		line += "\n";
		fileout << line;

	}
	filein.close();
	fileout.close();
	remove("logins\\plantinfo.txt");
	rename("logins\\plantinfo_temp.txt", "logins\\plantinfo.txt");
}
void  Director::plantstats() {
	int choice;
	cout << "Which plant you wanna see stats for:\n1)Southern Plant\n2)Nothern Plant\n3)Eastern Plant\n4)Western Plant\n";
	cin >> choice;
	switch (choice) {
	case 1:
		plants[0].dispstat();
		break;
	case 2:
		plants[1].dispstat();
		break;
	case 3:
		plants[2].dispstat();
		break;
	case 4:
		plants[3].dispstat();
		break;
	}
}
void  Director::directormenu() {
	int choice;
	cout << "\n1)Budget Allocation of plants\n2)Employees Salary\n3)Plant Production\n4)Logout\n";
	cin >> choice;
	switch (choice) {
	case 1:
		budgetallocator();
		directormenu();
		break;
	case 2:
		noofemployees();
		directormenu();
		break;
	case 3:
		plantstats();
		directormenu();
		break;
	case 4:
		intro();

		break;
	}
}
void Director::DisplayData() {
	cout << "Name:" << Name << endl << "Cnic:" << cnic << endl << "ID:" << id << endl << "Date of Joining:" << dateofjoining << endl;
}
void Plant::setname(string name) {
	this->name = name;
}
void Plant::datareader() {
	string fname1, fname2, fname;
	string fCrudeOil;
	string fbudget;
	string finvestment;
	string fprofit;
	//Amounts of product produced from one barrel of crude oil 
	string fdeisel, ffueloil, fkerosene, fpetroleum, fgasoline, fpropane;
	//Price per barrel
	string fdeiselprice, ffueloilprice, fkeroseneprice, fpetroleumprice, fgasolineprice, fpropaneprice;
	string line;
	ifstream myfile("logins\\plantinfo.txt");
	while (getline(myfile, line)) {

		myfile >> fname1;
		myfile >> fname2;
		fname = fname1 + " " + fname2;

		if (fname == name) {
			myfile >> fCrudeOil;
			myfile >> fdeisel;
			myfile >> ffueloil;
			myfile >> fkerosene;
			myfile >> fpetroleum;
			myfile >> fgasoline;
			myfile >> fpropane;
			myfile >> fdeiselprice;
			myfile >> ffueloilprice;
			myfile >> fkeroseneprice;
			myfile >> fpetroleumprice;
			myfile >> fgasolineprice;
			myfile >> fpropaneprice;
			myfile >> fbudget;
			myfile >> finvestment;
			myfile >> fprofit;
			CrudeOil = parser(fCrudeOil);
			deisel = parser(fdeisel);
			fueloil = parser(ffueloil);
			kerosene = parser(fkerosene);
			petroleum = parser(fpetroleum);
			gasoline = parser(fgasoline);
			propane = parser(fpropane);
			deiselprice = parser(fdeiselprice);
			fueloilprice = parser(ffueloilprice);
			keroseneprice = parser(fkeroseneprice);
			petroleumprice = parser(fpetroleumprice);
			gasolineprice = parser(fgasolineprice);
			propaneprice = parser(fpropaneprice);
			budget = parser(fbudget);
			investment = parser(finvestment);
			profit = parser(fprofit);
			break;
		}
	}
}
string Plant::getinvestment() {
	return investment;
}
string Plant::getprofit() {
	return profit;
}
string Plant::getbudget() {
	return budget;
}
void Plant::dispplantinfo() {
	cout << "\t" << name << endl;
	cout << "Plant Budget: " << budget << endl;
	cout << "Investment: " << investment << endl;
	cout << "Profit: " << profit << endl;
}
void Plant::dispstat() {
	int ammount, price;
	ammount = stoi(deisel) + stoi(fueloil) + stoi(kerosene) + stoi(petroleum);
	price = stoi(deiselprice) + stoi(fueloilprice) + stoi(keroseneprice) + stoi(petroleumprice);
	cout << "Material\t\tBarrels Used\t\t\tBought For\n";
	cout << "Crude Oil\t\t\t" << CrudeOil << "\t\t\t" << "50000\n\n";
	cout << "Materials\t\tBarrels Produced\t\tSold For\n";
	cout << "Diesel\t\t\t\t" << deisel << "\t\t\t" << deiselprice << "\n";
	cout << "Fuel Oil\t\t\t" << fueloil << "\t\t\t" << fueloilprice << "\n";
	cout << "Kerosene\t\t\t" << kerosene << "\t\t\t" << keroseneprice << "\n";
	cout << "Petroleum\t\t\t" << petroleum << "\t\t\t" << petroleumprice << "\n";
	cout << "Gasoline\t\t\t" << gasoline << "\t\t\t" << gasolineprice << "\n";
	cout << "Propane\t\t\t\t" << propane << "\t\t\t" << propaneprice << "\n\n";
	cout << "Total\t\t\t\t" << ammount << "\t\t\t" << price << "\n";
}
Attendance::Attendance() {
	daypos = daychecker();
	cout << ID;
}
Attendance::Attendance(string id) {
	daypos = daychecker();
	ID = id;
	cout << ID;
}
void Attendance::setid(string id) {
	ID = id;
}
int Attendance::daychecker() {
	int pos = 0;
	int counter = 0;
	string line, line1, line2, parsed;
	ifstream dayfile("attendance\\day.txt");
	getline(dayfile, line);
	line1 = line;
	getline(dayfile, line);
	line2 = line;
	for (int i = 0; i < 10; i += 2) {
		pos = line.find(":");
		parsed = line2.substr(i, pos);
		counter++;
		if (parsed == "1") {
			break;
		}
	}
	return counter;
}
void Attendance::attendancemarker() {
	string line;
	string data;
	string fid, temp;
	int pos1;
	ifstream filein("attendance\\attendance.txt");
	ofstream fileout("attendance\\attendance_temp.txt");
	while (getline(filein, line)) {
		pos1 = line.find(":");
		fid = line.substr(0, pos1);

		if (fid == ID) {
			pos1 = (2 * daypos - 2) + 5;
			line.replace(pos1, 1, "9");

		}
		line += "\n";
		fileout << line;

	}
	filein.close();
	fileout.close();
	remove("attendance\\attendance.txt");
	rename("attendance\\attendance_temp.txt", "attendance\\attendance.txt");

}
void Attendance::attendancechecker() {
	string line;
	string data;
	string fid, temp;
	int pos1, pos2;
	ifstream filein("attendance\\attendance.txt");
	while (getline(filein, line)) {
		pos1 = line.find(":");
		fid = line.substr(0, pos1);

		if (fid == ID) {
			pos1 = (2 * daypos - 2) + 5;
			pos2 = (2 * daypos - 1) + 5;
			data = line.substr(pos1, pos2);

		}
	}
	cout << "Your Attendance for " << getday(daypos) << " is Marked!";
}
void Person::setplant(string pl) {
	plant = pl;
}
int planttoindex(string plant) {
	if (plant == "Southern Plant")
		return 0;
	else if (plant == "Nothern Plant")
		return 1;
	else if (plant == "Eastern Plant")
		return 2;
	else if (plant == "Western Plant")
		return 3;
}
int employeecounter() {
	int counter = 0;
	ifstream emp("logins\\employeelogininfo.txt");
	string line;
	string id;
	int i = 0;
	while (getline(emp, line)) {
		if (i % 2 == 1)
			i++;
		else {
			emp >> id;
			id = id.substr(0, 2);
			if (id == "ID") {
				counter++;
			}
		}
	}
	return counter;
}
int managercounter() {
	int counter = 0;
	ifstream emp("logins\\managerlogininfo.txt");
	string line;
	string id;
	int i = 0;
	while (getline(emp, line)) {
		if (i % 2 == 1)
			i++;
		else {
			emp >> id;
			id = id.substr(0, 2);
			if (id == "ID") {
				counter++;
			}
		}
	}
	return counter;
}
bool duplicatechecker(string id) {
	string line, fid;
	ifstream myfile("logins\\info.txt");
	while (getline(myfile, line)) {

		myfile >> fid;
		fid = parser(fid);
		if (fid == id) {
			return true;
		}
		else
			return false;
	}
}
string getid() {
	string id;
	cout << "ID: ";
	cin >> id;
	return id;
}
string getpass() {
	char pass[32];
	char a;
	cout << "Password: ";
	for (int i = 0;;) {
		a = _getch();
		if ((a >= 'a' &&a <= 'z') || (a >= 'A'&&a <= 'Z') || (a >= '0' && a <= '9')) {
			pass[i] = a;
			++i;
			cout << "*";
		}
		if (a == '\b'&&i >= 1) {
			cout << "\b \b";
			--i;
		}
		if (a == '\r') {
			pass[i] = '\0';
			break;
		}

	}
	return pass;
}
string parser(string str) {
	int pos;
	string parsed;
	pos = str.find(":");
	parsed = str.substr(pos + 1);
	return parsed;
}
void plantsetter(string id,string rank) {
	int ID = stoi(id);
	if ((ID > 5500 && ID < 5526)) {
		emps[empcounter].setplant("Southern Plant");
	}
	else if ((ID > 5525 && ID < 5550)) {
		emps[empcounter].setplant("Nothern Plant");
	}
	else if (ID > 5550 && ID < 5575) {
		emps[empcounter].setplant("Eastern Plant");
	}
	else if (ID > 5575 && ID < 6000) {
		emps[empcounter].setplant("Western Plant");
	}
	else if ((ID > 6619 && ID < 6625)) {
		if (rank == "Managment")
			managerman[mancounter].setplant("Southern Plant");
		else if (rank == "HR")
			managerman[mancounter].setplant("Southern Plant");
		else if (rank == "Account")
			managerman[mancounter].setplant("Southern Plant");
	}
	else if ((ID > 6625 && ID < 6630)) {
		if (rank == "Managment")
			managerman[mancounter].setplant("Nothern Plant");
		else if (rank == "HR")
			managerman[mancounter].setplant("Nothern Plant");
		else if (rank == "Account")
			managerman[mancounter].setplant("Nothern Plant");
	}
	else if ((ID > 6631 && ID < 6635)) {
		if (rank == "Managment")
			managerman[mancounter].setplant("Eastern Plant");
		else if (rank == "HR")
			managerman[mancounter].setplant("Eastern Plant");
		else if (rank == "Account")
			managerman[mancounter].setplant("Eastern Plant");
	}
	else if ((ID > 6635 && ID < 6640)) {
		if (rank == "Managment")
			managerman[mancounter].setplant("Western Plant");
		else if (rank == "HR")
			managerman[mancounter].setplant("Western Plant");
		else if (rank == "Account")
			managerman[mancounter].setplant("Western Plant");
	}
	else if (ID == 7720) {
		admins[admincounter].setplant("Southern Plant");
	}
	else if (ID == 7721) {
		admins[admincounter].setplant("Nothern Plant");
	}
	else if (ID == 7722) {
		admins[admincounter].setplant("Eastern Plant");
	}
	else if (ID == 7723) {
		admins[admincounter].setplant("Western Plant");
	}
}
string plantchecker(string id, string rank) {
	int ID = stoi(id);
	if ((ID > 5500 && ID < 5526)) {
		return "Southern Plant";
	}
	else if ((ID > 5525 && ID < 5550)) {
		return "Nothern Plant";
	}
	else if (ID > 5550 && ID < 5575) {
		return "Eastern Plant";
	}
	else if (ID > 5575 && ID < 6000) {
		return  "Western Plant";
	}
	else if ((ID > 6619 && ID < 6625)) {
		if (rank == "Managment")
			return "Southern Plant";
		else if (rank == "HR")
			return "Southern Plant";
		else if (rank == "Account")
			return "Southern Plant";
	}
	else if ((ID > 6625 && ID < 6630)) {
		if (rank == "Managment")
			return "Nothern Plant";
		else if (rank == "HR")
			return "Nothern Plant";
		else if (rank == "Account")
			return "Nothern Plant";
	}
	else if ((ID > 6631 && ID < 6635)) {
		if (rank == "Managment")
			return "Eastern Plant";
		else if (rank == "HR")
			return "Eastern Plant";
		else if (rank == "Account")
			return "Eastern Plant";
	}
	else if ((ID > 6635 && ID < 6640)) {
		if (rank == "Managment")
			return "Western Plant";
		else if (rank == "HR")
			return "Western Plant";
		else if (rank == "Account")
			return "Western Plant";
	}
	else if (ID == 7720) {
		return "Southern Plant";
	}
	else if (ID == 7721) {
		return "Nothern Plant";
	}
	else if (ID == 7722) {
		return "Eastern Plant";
	}
	else if (ID == 7723) {
		return "Western Plant";
	}
}
void plantsetter(string id, string rank, int counter) {
	int ID = stoi(id);
	if ((ID > 5500 && ID < 5526)) {
		emps[counter].setplant("Southern Plant");
	}
	else if ((ID > 5525 && ID < 5550)) {
		emps[counter].setplant("Nothern Plant");
	}
	else if (ID > 5550 && ID < 5575) {
		emps[counter].setplant("Eastern Plant");
	}
	else if (ID > 5575 && ID < 6000) {
		emps[counter].setplant("Western Plant");
	}
	else if ((ID > 6619 && ID < 6625)) {
		if (rank == "Managment")
			managerman[counter].setplant("Southern Plant");
		else if (rank == "HR")
			managerman[counter].setplant("Southern Plant");
		else if (rank == "Account")
			managerman[counter].setplant("Southern Plant");
	}
	else if ((ID > 6625 && ID < 6630)) {
		if (rank == "Managment")
			managerman[counter].setplant("Nothern Plant");
		else if (rank == "HR")
			managerman[counter].setplant("Nothern Plant");
		else if (rank == "Account")
			managerman[counter].setplant("Nothern Plant");
	}
	else if ((ID > 6631 && ID < 6635)) {
		if (rank == "Managment")
			managerman[counter].setplant("Eastern Plant");
		else if (rank == "HR")
			managerman[counter].setplant("Eastern Plant");
		else if (rank == "Account")
			managerman[counter].setplant("Eastern Plant");
	}
	else if ((ID > 6635 && ID < 6640)) {
		if (rank == "Managment")
			managerman[counter].setplant("Western Plant");
		else if (rank == "HR")
			managerman[counter].setplant("Western Plant");
		else if (rank == "Account")
			managerman[counter].setplant("Western Plant");
	}
	else if (ID == 7720) {
		admins[counter].setplant("Southern Plant");
	}
	else if (ID == 7721) {
		admins[counter].setplant("Nothern Plant");
	}
	else if (ID == 7722) {
		admins[counter].setplant("Eastern Plant");
	}
	else if (ID == 7723) {
		admins[counter].setplant("Western Plant");
	}
}
void objectcreater(string id){
	string fid, rank, fname, fpassword, fdoj, fcnic;
	string line;
	ifstream myfile("logins\\info.txt");
	while (getline(myfile, line)) {
		
		myfile >> fid;
		fid = parser(fid);
		if (fid == id) {
			myfile >> rank;
			myfile >> fpassword;
			myfile >> fname;
			myfile >> fcnic;
			myfile >> fdoj;
			rank = parser(rank);
			fname = parser(fname);
			fpassword = parser(fpassword);
			fdoj = parser(fdoj);
			fcnic = parser(fcnic);
		 if (rank == "Admin") {
			if (empcounter <= employeecounter()) {
				admins[admincounter].setdata(fname, fcnic, fid, fpassword, fdoj);
				
				admins[admincounter].DisplayData();
				admins[admincounter].adminmenu();
				
				admincounter++;
				break;
			}
		}
		  else if (rank == "Employee") {
				if (empcounter <= employeecounter()) {
					emps[empcounter].setdata(fname, fcnic, fid, fpassword, fdoj);
					emps[empcounter].DisplayData();
					plantsetter(fid, rank);
					emps[empcounter].Empmenu();
					empcounter++;
					break;
				}
			}
			else if (rank == "Management") {
				if (mancounter <= managercounter()) {
					
					managerman[mancounter].setdata(fname, fcnic, fid, fpassword, fdoj);
					managerman[mancounter].DisplayData();
					plantsetter(fid, rank);
					managerman[mancounter].managmentmenu();
					
					mancounter++;
					break;
				}
			}
			else if (rank == "HR") {
				if (mancounter <= managercounter()) {
					managerhr[mancounter].setdata(fname, fcnic, fid, fpassword, fdoj);
					managerhr[mancounter].DisplayData();
					plantsetter(fid, rank);
					managerhr[mancounter].hrmenu();
					
					mancounter++;
					break;
				}
			}
			else if (rank == "Account") {
				if (mancounter <= managercounter()) {
					manageracc[mancounter].setdata(fname, fcnic, fid, fpassword, fdoj);
					manageracc[mancounter].DisplayData();
					plantsetter(fid, rank);
					manageracc[mancounter].accmenu();
					
					mancounter++;
					break;
				}
			}
			else if (rank == "Director") {
				
					director.setdata(fname, fcnic, fid, fpassword, fdoj);
					director.DisplayData();
					director.directormenu();
					break;
				
			}
			else if (rank == "CEO") {
				
					ceo.setdata(fname, fcnic, fid, fpassword, fdoj);
					ceo.DisplayData();
					ceo.ceomenu();
					break;
				
			}
		}
	}
}

void intro() {
	system("cls");
	int choice;
	cout << "                      Welcome to Oil Refinery Company!" << endl;
	cout << "1)Login As CEO" << endl;
	cout << "2)Login As Director" << endl;
	cout << "3)Login As Administrator" << endl;
	cout << "4)Login As Manager" << endl;
	cout << "5)login As Employee" << endl;
	cin >> choice;
	login(choice);
}

void login(int choice) {

	switch (choice) {
	case 1:{
		{
			string id = getid();
			string pass = getpass();
			string name;
			ifstream man("logins\\ceologininfo.txt");
			if (!man.is_open())
				cout << "cannot open";
			string line;

			while (getline(man, line)) {
				string inputid, inputpass;
				string parsedid, parsedpass;
				man >> inputid;
				man >> inputpass;
				parsedid = parser(inputid);
				parsedpass = parser(inputpass);
				cout << endl << parsedid << endl << parsedpass << endl;
				if (parsedid == id && parsedpass == pass) {
					system("cls");
					cout << "WELCOME CEO" << endl;
					objectcreater(id);
					break;
				}
				else if (man.eof()) {
					cout << "Incorrect ID or Pass" << endl;
					login(1);
				}
			}

		}
		break;
	}
	case 2:{
		{
			string id = getid();
			string pass = getpass();
			string name;
			ifstream man("logins\\directorlogininfo.txt");
			if (!man.is_open())
				cout << "cannot open";
			string line;

			while (getline(man, line)) {
				string inputid, inputpass;
				string parsedid, parsedpass;
				man >> inputid;
				man >> inputpass;
				parsedid = parser(inputid);
				parsedpass = parser(inputpass);
				cout << endl << parsedid << endl << parsedpass << endl;
				if (parsedid == id && parsedpass == pass) {
					system("cls");
					cout << "WELCOME Director" << endl;
					objectcreater(id);
					break;
				}
				else if (man.eof()) {
					cout << "Incorrect ID or Pass" << endl;
					login(2);
				}
			}

		}
		break;
	}
	case 3: {
		{
			string id = getid();
			string pass = getpass();
			string name;
			ifstream man("logins\\adminlogininfo.txt");
			if (!man.is_open())
				cout << "cannot open";
			string line;

			while (getline(man, line)) {
				string inputid, inputpass;
				string parsedid, parsedpass;
				man >> inputid;
				man >> inputpass;
				parsedid = parser(inputid);
				parsedpass = parser(inputpass);
				cout << endl << parsedid << endl << parsedpass << endl;
				if (parsedid == id && parsedpass == pass) {
					system("cls");
					cout << "WELCOME Administrator" << endl;
					objectcreater(id);
					break;
				}
				else if (man.eof()) {
					cout << "Incorrect ID or Pass" << endl;
					login(3);
				}
			}

		}
		break;
	}
	case 4:
	{
		string id = getid();
		string pass = getpass();
		string name;
		ifstream man("logins\\managerlogininfo.txt");
		if (!man.is_open())
			cout << "cannot open";
		string line;

		while (getline(man, line)) {
			string inputid, inputpass;
			string parsedid, parsedpass;
			man >> name;
			man >> inputid;
			man >> inputpass;
			parsedid = parser(inputid);
			parsedpass = parser(inputpass);
			if (parsedid == id && parsedpass == pass) {
				system("cls");
				cout << "WELCOME Manager" << name << endl;
				objectcreater(id);
				break;
			}
			else if (man.eof()) {
				cout << "Incorrect ID or Pass" << endl;
				login(4);
			}
		}
		break;

	}
	case 5: {
		string id = getid();
		string pass = getpass();
		ifstream emp("logins\\employeelogininfo.txt");
		if (!emp.is_open())
			cout << "cannot open";
		string line;
		while (getline(emp, line)) {
			string inputid, inputpass;
			string parsedid, parsedpass;
			emp >> inputid;
			emp >> inputpass;
			parsedid = parser(inputid);
			parsedpass = parser(inputpass);
			if (parsedid == id && parsedpass == pass) {
				system("cls");
				cout << "WELCOME EMPLOYEE#" << id << endl;
				objectcreater(id);
				break;
			}
			else if (!emp.eof())
				continue;
			else if(emp.eof()){
				cout << "Incorrect ID or Pass" << endl;
				login(5);
			}
		}
		break;
	}
	}
}

string getday(int daypos) {
	switch (daypos) {
	case 1:
		return "Monday";
	case 2:
		return "Tuesday";
	case 3:
		return "Wednessday";
	case 4:
		return "Thursday";
	case 5:
		return "Friday";
	}
}