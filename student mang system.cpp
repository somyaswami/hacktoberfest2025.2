#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Student {
private:
    int rollNo;
    string name;
    int marks[3];
    float average;
    char grade;

    void calculateAverageAndGrade() {
        int sum = 0;
        for (int m : marks) sum += m;
        average = sum / 3.0;

        if (average >= 90) grade = 'A';
        else if (average >= 75) grade = 'B';
        else if (average >= 50) grade = 'C';
        else grade = 'F';
    }

public:
    void input() {
        cout << "Enter roll number: ";
        cin >> rollNo;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter marks for 3 subjects: ";
        for (int i = 0; i < 3; i++)
            cin >> marks[i];
        calculateAverageAndGrade();
    }

    void display() const {
        cout << left << setw(10) << rollNo
             << setw(20) << name
             << setw(10) << average
             << setw(5) << grade << endl;
    }

    void saveToFile(ofstream &out) const {
        out << rollNo << '\n' << name << '\n';
        for (int i = 0; i < 3; i++)
            out << marks[i] << ' ';
        out << '\n';
    }

    void readFromFile(ifstream &in) {
        in >> rollNo;
        in.ignore();
        getline(in, name);
        for (int i = 0; i < 3; i++)
            in >> marks[i];
        calculateAverageAndGrade();
    }
};

int main() {
    vector<Student> students;
    int n;
    cout << "How many students? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for student " << i + 1 << ":\n";
        Student s;
        s.input();
        students.push_back(s);
    }

    // Save to file
    ofstream fout("students.txt");
    fout << n << '\n';
    for (const Student &s : students) {
        s.saveToFile(fout);
    }
    fout.close();

    // Read from file
    vector<Student> loadedStudents;
    ifstream fin("students.txt");
    int total;
    fin >> total;
    for (int i = 0; i < total; i++) {
        Student s;
        s.readFromFile(fin);
        loadedStudents.push_back(s);
    }
    fin.close();

    // Display loaded students
    cout << "\n--- Student Records ---\n";
    cout << left << setw(10) << "Roll No"
         << setw(20) << "Name"
         << setw(10) << "Average"
         << setw(5) << "Grade" << endl;

    for (const Student &s : loadedStudents) {
        s.display();
    }

    return 0;
}
