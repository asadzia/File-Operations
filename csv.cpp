#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

bool checkExists (const char* fileName) {
  ifstream file(fileName);
  return (bool)file;
}

void createHeaders (ofstream &file) {
  file  <<  "Roll Number"  <<  ","
        <<  "Name"  << ","
        <<  "Maths" << ","  
        <<  "Physics" << ","
        <<  "Chemistry" << ","
        << "Biology"  << "\n"; 
}

ofstream createFile (const char* fileName) {
  ofstream file;
  
  // open file and append headers accordingly
  if (checkExists(fileName)) {
    file.open(fileName, ios::out | ios::app);
    return file;
  } else {
    // this either creates or opens an existing file
    file.open(fileName, ios::out | ios::app);
    createHeaders(file);
    return file;
  }   
}

void createRecord (ofstream &file) {

  cout << "Enter the details of the report card:" << endl;

  int roll, maths, phy, chem, bio;
  string name;

  cin >> roll
      >> name
      >> maths
      >> phy
      >> chem
      >> bio;

  file  << roll << ","
        << name << ","
        << maths << ","
        << phy << ","
        << chem << ","
        << bio << "\n";

  cout << "Thanks" << endl;
}

void findRecord (const char* fileName, int rollNumber) {
  
  if (checkExists(fileName)) {
    ifstream file(fileName, ios::in);
    
    // variable declarations
    vector<string> row;
    string line, word;
    stringstream ss;
    int count = 0;

    // Skip headers
    getline(file, line);

    while (getline(file, line)) {
      
      // empty vector and stringstream
      row.clear();
      ss.clear();

      ss << line;

      while (getline(ss, word, ',')) {
        row.push_back(word);
        // roll - name - math - phy - chem - bio
      }

      if (stoi(row[0]) == rollNumber) {
        count = 1;
        cout << "Record found! Details as follows: " << endl;
        cout << "Roll Number: " << row[0] << endl;
        cout << "Name: " << row[1] << endl;
        cout << "Maths " << row[2] << endl;
        cout << "Physics: " << row[3] << endl;
        cout << "Chemistry: " << row[4] << endl;
        cout << "Biology: " << row[5] << endl;
        break;
      }
    }

    if (count == 0) {
      cout << "Roll number: " << rollNumber << " not found!" << endl;
    }

    file.close();

  } else {
    cout << "The file " << fileName << " does not exist!" << endl;
  }
}

int main() {
  // create or open existing file
  ofstream file = createFile("reportCard.csv");

  // create a record
  //createRecord(file);

  // find a record
  findRecord("reportCard.csv", 20330643);

  // close file
  file.close();
  cout << "Ending Program..." << endl;
  return 0;
}
