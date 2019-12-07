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

void updateRowName(const char* filename, int roll, string name) {

  if (checkExists(filename)) {
    ifstream fin(filename);
    ofstream fout("Temp.csv", ios::app | ios::out);
    createHeaders(fout);

    // variable declarations
    bool flag = false;
    vector<string> row;
    string line, word;
    stringstream ss;
    
    // read header line
    getline(fin, line);

    while (getline(fin, line)) {

      row.clear();
      ss.clear();

      ss << line;

      while(getline(ss, word, ',')) {
        row.push_back(word);
      }

      if (stoi(row[0]) == roll) {
        row[1] = name;
        flag = true;

        for (int i = 0; i < row.size() - 1; ++i) {
          fout << row[i] << ",";
        }
        // add final element - couldn't do this in the loop beause of comma
        fout << row[row.size() - 1] << "\n";

      } else {
        while(getline(ss, word, ',')) {
          row.push_back(word);
        }

        for (int i = 0; i < row.size() - 1; ++i) {
          fout << row[i] << ",";
        }
        // add final element - couldn't do this in the loop beause of comma
        fout << row[row.size() - 1] << "\n";
      }
    }

    if (!flag) {
      cout << "Roll Number: " << roll << " not found in the file!" << endl;
      return;
    }

    fin.close();
    fout.close();

    remove(filename);
    rename("Temp.csv", filename);

  } else {
    cout << "The file " << filename << " does not exist!" << endl;
  }
}

void deleteRecord (const char* filename, int roll) {
  
  if (checkExists((filename))) {
    ifstream fin(filename);
    ofstream fout = createFile("Temp.csv");

    // variable declarations
    bool flag = false;
    stringstream ss;
    string line, word;
    vector<string> row;

    // skip headers 
    getline(fin, line);

    while (getline(fin, line)) {
      
      ss.clear();
      row.clear();
      
      ss << line;

      while (getline(ss, word, ',')) {
        row.push_back(word);
      }

      if (stoi(row[0]) == roll) {
        flag = true;
        cout << "Deleting Record: " << row[0] << endl;
        continue;
      } else {
        for (int i = 0; i < row.size() - 1; ++i) {
          fout << row[i] << ",";
        }
        fout << row[row.size() - 1] << "\n";
      }
    }

    fin.close();
    fout.close();

    remove(filename);
    rename("Temp.csv", filename);

  } else {
    cout << "The file: " << filename << " does not exist." << endl;
    return;
  }

}

int main() {
  // create or open existing file
  ofstream file = createFile("reportCard.csv");

  // create a record
  //createRecord(file);

  // find a record
  //findRecord("reportCard.csv", 20330643);

  //update row name
  //updateRowName("reportCard.csv", 543, "yo");

  // delete a record 
  deleteRecord("reportCard.csv", 543);

  // close file
  file.close();
  cout << "Ending Program..." << endl;
  return 0;
}
