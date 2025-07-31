#pragma once
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;



class Person {
public:
	string Name;
	string cnic;
	string id;
	string password;
	string dateofjoining;
	string plant;
	void setplant(string pl);

};
class Attendance {
	int daypos;
	string ID;
public:
	Attendance(); // Constructor
	Attendance(string id);
	void setid(string id); // Sets ID 
	int daychecker(); //Gets day which Manager has Opened for Attendance
	void attendancemarker(); // Marks Attendance for Employees
	void attendancechecker(); // Checks Attendance for Employees
};
class Plant {
	string name;
	string CrudeOil;
	string budget;
	string investment;
	string profit;
	//Amounts of product produced from one barrel of crude oil 
	string deisel, fueloil, kerosene, petroleum, gasoline, propane;
	//Price per barrel
	string deiselprice, fueloilprice, keroseneprice, petroleumprice, gasolineprice, propaneprice;
public:
	void setname(string name); // Sets Plant Name
	void datareader(); // Reads Data from txt file
	string getinvestment(); // Returns Investment
	string getprofit(); // Returns Profit
	string getbudget(); // Returns Budget
	void dispplantinfo(); // Displays Budget, Investment and profit of Plant
	void dispstat(); // Displays Production of All Materials
};
class Director : public Person {
public:
	void setdata(string name, string cnic, string id, string password, string dateofjoining); // Sets Data
	void noofemployees(); // Counts Number of Employees In a Plant
	void budgetallocator(); // Allocates Budget to Each Plant
	void plantstats(); // Displays all Information of Plant
	void directormenu(); // Runtime Options of Director
	void DisplayData(); // Displays Data of Director
};
class Employee : public Person {
	int rateperhour = 208;
	Attendance atd;
	int WorkingHours;
	int salary;

public:
	friend void plantsetter(string, string, int); // Assigns a Employee to Certain Plant According to Their ID
	friend void plantsetter(string, string);
	void setdata(string name, string cnic, string id, string password, string dateofjoining); // Assigns Data
	int whcalculator(string id); // Reads Attendance from txt File and Calculates Working Hours of Employee
	int salarycalculator(); // Calculates Salary
	string getplant(); // Returns Plant Name
	void Empmenu(); // Employee Menu
	void DisplayData(); // Displays Employee Data
};

class ManagerHR : public Person {
public:
	friend void plantsetter(string, string, int); // Assigns Manager to Plant According to their ID
	friend void plantsetter(string, string);
	void setdata(string name, string cnic, string id, string password, string dateofjoining); // Assigns Data
	void employeeadder(); // Adds a New Employee 
	void employeesearcher(); // Searches an Employee by their ID
	void leavemarker(); //Marks Leave for Employee
	void hrmenu(); // Managers Menu
	void DisplayData(); //Displays Data
};
class ManagerManagement : public Person {
public:
	friend void plantsetter(string, string, int); // Assigns Manager to Plant According to their ID
	friend void plantsetter(string, string);
	void setdata(string name, string cnic, string id, string password, string dateofjoining); // Assigns Data
	void setday(); // Opens Day for Employees if Employee marks their attendance their Attendance will be marked to that day
	void managmentmenu(); // Managers Menu
	void DisplayData(); // Displays Data
};
class ManagerAccountant : public Person {
public:
	friend void plantsetter(string, string, int); //Assisgns Plant
	friend void plantsetter(string, string);
	void setdata(string name, string cnic, string id, string password, string dateofjoining); //Assigns Data
	void Employeelist(); //List of Employees in plant
	void accmenu(); // Managers Menu
	void DisplayData(); // Displays Data
};
class Administrator : public Person {
public:
	friend void plantsetter(string, string); //Assigns Plant
	friend void plantsetter(string, string, int);
	void setdata(string name, string cnic, string id, string password, string dateofjoining); // Assigns Data
	int noofemployees(); // Number of Employees in Plant which Admin belongs
	void displayatd(); // Attendance of Employees of that plant
	void adminmenu(); // Admins Menu
	void DisplayData(); // Displays Data
};
class CEO : protected Person {
public:
	void setdata(string name, string cnic, string id, string password, string dateofjoining); // Assigns Data
	void ceomenu(); // CEO Menu
	void DisplayData(); // Displays Data
};
Director director;
CEO ceo;