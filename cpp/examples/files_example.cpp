#include <fstream>
#include <iostream>
using namespace std;

int main() {
  char first_name[30], last_name[30]; int age;
  string fileName;
  // Collect the data.
  cout << "Enter First Name: "; cin >> first_name;
  cout << "Enter Last Name: "; cin >> last_name;
  cout << "Enter Age: "; cin >> age;
  cout << endl << "Enter the name of the file: "; cin >> fileName;

  // Create an ofstream called People, open the stream for output.
  ofstream People(fileName, ios::out);
  // Write the output to the stream.
  People << first_name << endl << last_name << endl << age << endl; 
  return 0;
} 