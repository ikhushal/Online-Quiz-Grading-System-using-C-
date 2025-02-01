//ONLINE QUIZ AND GRADING SYSTEM
#include<iostream>
#include <fstream>
#include <vector>
#include<sstream>
#include <string>
//#include <bits/stdc++.h>  // this headerfile does not work in my macbook so i used <sstream>

using namespace std;

void create()
{
    // file pointer
    fstream fout;
  
    // opens an existing csv file or creates a new file.
    fout.open("quizgrading.csv", ios::out|ios::app);

  
    int i, roll;
	string quiz1, quiz2, quiz3, quiz4;
    string name;
  
    // Read the input
    for (i = 0; i < 2; i++) {
        cout<<"------- ONlINE QUIZ AND GRADING -------"<<endl;
  		cout<<"Enter the following data(of one student and then another but first) " << endl;
  		cout << "Enter your reg number and name and then the marks obtained in 4 quizzes of MT-103 "
         << " (reg number, name,  quiz1 quiz2 quiz3 quiz4) of student : "<<i << endl;
        cin >> roll
            >> name
            >> quiz3
            >> quiz1
            >> quiz2
            >> quiz4;
  
        // Insert the data to file
        fout << roll << ","
             << name << ","
             << quiz3 << ","
             << quiz1 << ","
             << quiz2 << ","
             << quiz4 << endl;
    }
}

void read_record()
{
    // File pointer
    fstream fin;
  
    // Open an existing file
    fin.open("quizgrading.csv", ios::in);
  
    // Get the roll number
    // of which the data is required
    int rollnum, roll2, count = 0;
    cout << "Enter the roll number of the student to display details: ";
    cin >> rollnum;
  
    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word;
  
    while (!fin.eof()) {
  
        row.clear();
  
        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);
  
        // used for breaking words
        stringstream s(line);
  
        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',')) {
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }
      
  
        // convert string to integer for comparision
        roll2 = stoi(row[0]);
        if (roll2 == rollnum) {
  
            cout<<"Print the found data";
            count = 1;
            cout << " Roll: " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
            cout << "Quiz 1: " << row[2] << endl;
            cout << "Quiz 2: " << row[3] << endl;
            cout << "Quiz 3: " << row[4] << endl;
            cout << "Quiz 4: " << row[5] << endl;
            cout << endl;
            break;
        }
    }
    if (count == 0)
        cout << "Record not found!\n";
}

void update_record()
{
  
    // File pointer
    fstream fin, fout;
  
    // Open an existing record
    fin.open("quizgrading.csv", ios::in);
  
    // Create a new file to store updated data
    fout.open("quizgradingnew.csv", ios::out);
  
    int  pid2, marks, found = 0, i;
    int pid;
    char data;
    int index, new_id,roll1;
    string line, word;
    vector<string> row;
    int new_data;
  
    // Get the registration number from the user
    cout << "Enter the roll number "
         << "of the student to be updated: ";
    cin >> pid;
  
    // Get the data to be updated
    // here 1 means quiz 1, 2 means quiz 2 and so on..
    cout << "Enter the data "
         << "to be updated(1/2/3/4): \n"<<"1--> Quiz 1 \n"<< "2--> Quiz 2 \n"<< "3--> Quiz 3 \n"<<"4--> Quiz 4 \n" ;
    cin >> data;
  
    // Determine the index of the subject
    // where quiz1 has index 2,
    // quiz2 has index 3, and so on
    if (data == '1' )
        index = 2;
    else if (data == '2' )
        index = 3;
    else if (data == '3' )
        index = 4;
    else if (data == '4' )
        index = 5;
    else {
        cout << "Wrong choice. Enter again\n";
        update_record();
    }
  
    // Get the new marks
    cout << "Enter new data: ";
    cin >> new_data;
  
    // Traverse the file
    while (!fin.eof()) {
  
        row.clear();
  
        getline(fin, line);
        stringstream s(line);
  
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
  
        roll1 = stoi(row[0]);
        int row_size = row.size();

        if (roll1 == pid) {
            found = 1;
            stringstream convert;
  
         //  sending a number as a stream into output string
           convert << new_data;
  
            // the str() converts number into string
            row[index] = convert.str();
  
            if (!fin.eof()) {
                for (i = 0; i < row_size - 1; i++) {
  
                    // write the updated data
                    // into a new file 'resultnew.csv'
                    // using fout
                    fout << row[i] << ",";
                }
  
                fout << row[row_size - 1] << endl;
            }
        }
        else {
            if (!fin.eof()) {
                for (i = 0; i < row_size - 1; i++) {
  
                    // writing other existing records
                    // into the new file using fout.
                    fout << row[i] << ",";
                }
  
                
                fout << row[row_size - 1] << endl;
            }
        }
        if (fin.eof())
            break;
    }
    if (found == 0)
        cout << "Record not found!" << endl;
  
    fin.close();
    fout.close();
  
    // removing the existing file
    remove("quizgrading.csv");
    // renaming the updated file with the existing file name
    rename("quizgradingnew.csv", "quizgrading.csv");
}

void delete_record()
{
  
    // Open FIle pointers
    fstream fin, fout;
  
    // it opens the current file
    fin.open("quizgrading.csv", ios::in);
  
    // Create a new file to store the non-deleted data
    fout.open("quizgradingnew.csv", ios::out);
  
    int rollnum, roll1, marks, count = 0, i;
    char sub;
    int index, new_marks;
    string line, word;
    vector<string> row;
  
    // Get the registration number
    // to decide the data to be deleted
    cout << "Enter the Registration number: ";
    cin >> rollnum;
    cout << endl;
  
    // Check if this record exists
    // If exists, leave it and
    // add all other data to the new file
    while (!fin.eof()) {
  
        row.clear();
        getline(fin, line);
        stringstream s(line);
  
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
  
        int row_size = row.size();
        roll1 = stoi(row[0]);
  
        // writing all records,
        // except the record to be deleted,
        // into the new file 'resultnew.csv'
        // using fout pointer
        if (roll1 != rollnum) {
            if (!fin.eof()) {
                for (i = 0; i < row_size - 1; i++) {
                    fout << row[i] << ",";
                }
                fout << row[row_size - 1] << endl;
            }
        }
        else {
            count = 1;
        }
        if (fin.eof())
            break;
    }
    if (count == 1)
        cout << "Record deleted!" << endl;
    else
        cout << "Record not found!" << endl;
  
    // Close the pointers
    fin.close();
    fout.close();
  
    // removing the existing file
    remove("quizgrading.csv");
  
    // renaming the new file with the existing file name
    rename("quizgradingnew.csv", "quizgrading.csv");
}

int main()
{
	//while
	create();
	//update
    bool cont;
    char c;
    cout<<"Do you want to update the quiz marks ? If yes enter Y " << endl; // I used if statement for the user to select if he wants to continue or not
    cin>>c;
    if(c =='y' || c == 'Y'){
    bool cont= true;

	update_record();
    }
    else{
        cout<<"File has ended!"<<endl;
        exit(0);
    }
	//read
    bool cont1;
    char d;
    cout<<"Do you want to read the record ? If yes enter Y " << endl;
    cin>>d;
    if(d =='y' || d == 'Y'){
    bool cont1= true;
    read_record();
	
    }
    else{
        cout<<"File has ended!"<<endl;
        exit(0);
    }
	//delete
    bool cont2;
    char e;
    cout<<"Do you want to delete the record ? If yes enter Y " << endl;
    cin>>e;
    if(e =='y' || e == 'Y'){
    bool cont2= true;
    delete_record();
	
    }
    else{
        cout<<"File has ended!"<<endl;
        exit(0);
    }
	return 0;
}