/*
* File:   main.cpp
* Author: Thomas Williams
* Project: Project 1
* Class: Data Structure and Algorithm
* Created on October 30, 2018, 7:17 AM
*/

#include <iostream>
#include <string>
#include "stdafx.h"

using namespace std;

class Student {
public:
char fName[64];
char lName[64];
char courseNum[64];
char section[64];
};

class Students {
public:
static const int MaxSize = 100;
char m_fileName[1024];
int m_nMaxStudents;
Student m_studList[MaxSize];

Students(char *filename) {
m_nMaxStudents = 0;
strcpy(m_fileName, filename);
}

void AddRecord(char *fName, char *lName, char *courseNum, char *section) {
int pos = m_nMaxStudents;
strcpy(m_studList[pos].fName, fName);
strcpy(m_studList[pos].lName, lName);
strcpy(m_studList[pos].courseNum, courseNum);
strcpy(m_studList[pos].section, section);
m_nMaxStudents++;
WriteRecords();
}

void EditRecord(int pos, char *fName, char *lName, char *courseNum, char *section) {

strcpy(m_studList[pos].fName, fName);
strcpy(m_studList[pos].lName, lName);
strcpy(m_studList[pos].courseNum, courseNum);
strcpy(m_studList[pos].section, section);
WriteRecords();
}

void DeleteRecord(int pos) {
m_nMaxStudents--;

for (int i = pos; i < m_nMaxStudents; i++) {
m_studList[i + 1];
}
WriteRecords();
}

int ReadRecords() {
FILE *istream = fopen(m_fileName, "rb");

if (istream == 0) {
return false;
}
char buf[4096];
int nTotalRecordsRead = 0;

for (int i = 0; i < MaxSize; i++) {
if (feof(istream)) {
break;
}
int nBytesRead = fread(buf, 1, sizeof(Student), istream);
if (nBytesRead < sizeof(Student)) {
break;
}
char *p = reinterpret_cast<char*>(&m_studList[i]);
memcpy(p, buf, sizeof(Student));
nTotalRecordsRead++;
}

fclose(istream);
m_nMaxStudents = nTotalRecordsRead;
return nTotalRecordsRead;

}

int WriteRecords() {
FILE *ostream = fopen(m_fileName, "wb");

if (ostream == 0) {
return false;
}

int nTotalRecordsWritten = 0;
char buf[4096];
for (int i = 0; i < m_nMaxStudents; i++) {
fwrite((char*)&m_studList[i], 1, sizeof(Student), ostream);
nTotalRecordsWritten++;
}

fclose(ostream);
return nTotalRecordsWritten;
}
};
Students theStudents("c:\\students.bin");

int DisplayMainMenu() {

cout << "Add    Records" << endl;
cout << "List    Records" << endl;
cout << "Modify    Records" << endl;
cout << "Delete    Records" << endl;
cout << "Exit   Program" << endl;
cout << "Select Your Choice :=> ";
int m = -1;
cin >> m;

return m;
}

void ViewRecords() {
theStudents.ReadRecords();
cout << "--------------------------------------------" << endl;
cout << "First Name | Last Name | Course #  | Section" << endl;
cout << "--------------------------------------------" << endl;

int pos = 8;
for (int i = 0; i < theStudents.m_nMaxStudents; i++) {
cout << i + 1;
cout << theStudents.m_studList[i].fName;
cout << theStudents.m_studList[i].lName;
cout << theStudents.m_studList[i].courseNum;
cout << theStudents.m_studList[i].section;
pos++;
}
cout << "--------------------------------------------" << endl;
pos++;

}

void InputRecords() {
while (1) {
char* fName;
char* lName;
char* courseNum;
char* section;

cout << "First Name: ";
cin >> fName;
cout << endl;
cout << "Last Name: ";
cin >> lName;
cout << endl;
cout << "Course Number: ";
cin >> courseNum;
cout << endl;
cout << "Section: ";
cin >> section;
cout << endl;

theStudents.AddRecord(fName, lName, courseNum, section);
string c;
cout << "Do you want to add another record (Y/N)?";
cin >> c;

if (c == "Y" || c == "y") {
continue;
}
else {
break;
}
}
}

void EditRecords() {
ViewRecords();
cout << "Enter the serial number you want to edit: ";
int a;
cin >> a;

if (a >= 1 && a <= theStudents.m_nMaxStudents) {
char* fName;
char* lName;
char* courseNum;
char* section;
cout << "First Name: ";
cin >> fName;
cout << endl;
cout << "Last Name: ";
cin >> lName;
cout << endl;
cout << "Course Number: ";
cin >> courseNum;
cout << endl;
cout << "Section: ";
cin >> section;
cout << endl;
theStudents.EditRecord(a - 1, fName, lName, courseNum, section);
cout << "Record updated. Press any key to return to Main Menu";
}
else {
cout << "Invalid Entry. Press any key to return to Main Menu";
}
}
void DeleteRecords() {
ViewRecords();
cout << "Enter in the number you want to delete: ";
int n;
cin >> n;

if (n >= 1 && n <= theStudents.m_nMaxStudents) {
theStudents.DeleteRecord(n - 1);
cout << "Record Deleted. Press any Ket to return to Main Menu";
}
else {
cout << "Invalid Entry. Press any key to return to Main Menu";
}
}


int main() {

theStudents.ReadRecords();
while (1) {
int selection = DisplayMainMenu();

switch (selection) {
case 1:
InputRecords();
break;
case 2:
EditRecords();
break;
case 3:
ViewRecords();
cout << "Press any key to return to Main Menu: " << endl;
break;
case 4:
DeleteRecords();
break;
default:
return 0;
};
}
return 0;
}