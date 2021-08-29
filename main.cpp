#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

// the class that stores data
class student
{
    int rollno;
    char name[50];
    int eng_marks, math_marks, phy_marks, chem_marks, cs_marks;
    double average;
    char grade;
    void calculate();

public:
    void getdata();
    void showdata() const;
    void show_tabular() const;
    int retrollno() const;
};

void student::calculate()
{
    average = (eng_marks + math_marks + phy_marks + chem_marks + cs_marks)/5.0;
    if(average >= 90)
        grade = 'A';
    else if(average >= 75)
        grade = 'B';
    else if(average >= 50)
        grade = 'C';
    else
        grade = 'F';
}

void student::getdata()
{
    cout << "\n\tEnter student's roll number: ";
    cin >> rollno;
    cout << "\tEnter student name: ";
    cin.ignore();
    cin.getline(name,50);
    cout << "\n\t **All marks should be out of 100**";
    cout << "\n\n\tEnter marks in English: ";
    cin >> eng_marks;
    cout << "\tEnter marks in Mathematics:  ";
    cin >> math_marks;
    cout << "\tEnter marks in Physics:  ";
    cin >> phy_marks;
    cout << "\tEnter marks in Chemistry:  ";
    cin >> chem_marks;
    cout << "\tEnter marks in Computer science:  ";
    cin >> cs_marks;
    calculate();
}
void student::showdata() const
{
    cout << "\n\tRoll number of student : " << rollno;
    cout << "\n\tName of student : " << name;
    cout << "\n\tPhysics : " << phy_marks;
    cout << "\n\tChemistry : " << chem_marks;
    cout << "\n\tMaths : " << math_marks;
    cout << "\n\tEnglish : " << eng_marks;
    cout << "\n\tComputer Science : " << cs_marks;
    cout << "\n\tAverage Marks : " << average;
    cout << "\n\tGrade of student is : " << grade;
}
void student::show_tabular() const
{
    cout << "\t" << rollno << "     " << setw(25) << left << name << setw(15) << left << phy_marks << 
        setw(15) << left << chem_marks << setw(15) << left << math_marks << setw(15) << left << eng_marks << 
        setw(15) << left << cs_marks << setw(12) << left << average << setw(10) << left << grade << "\n";

}
int  student::retrollno() const
{
    return rollno;
}
//function declaration
void create_student();
void display_sp(int);//display particular record
void display_all(); // display all records
void delete_student(int);//delete particular record
void change_student(int);//edit particular record


//write student details to file
void create_student()
{
    student stud;
    ofstream oFile;
    oFile.open("student.dat", ios::binary|ios::app);
    stud.getdata();
    oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
    oFile.close();
    cout<<"\n\n\tStudent record Has Been Created ";
    cin.ignore();
    cin.get();
}
// read file records
void display_all()
{
    student stud;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
        cout << "\tFile could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\tDISPLAYING ALL RECORDS\n\n";
    while(inFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
    {
        stud.showdata();
        cout << "\n\n\t====================================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}
//read specific record based on roll number
void display_sp(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("student.dat",ios::binary);
    if(!iFile)
    {
        cout << "\tFile could not be opened... Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
    {
        if(stud.retrollno() == n)
        {
            stud.showdata();
            flag = true;
        }
    }
    iFile.close();
    if(flag == false)
        cout << "\n\n\t record does not exist";
    cin.ignore();
    cin.get();
}
// modify record for specified roll number
void change_student(int n)
{
    bool found = false;
    student stud;
    fstream fl;
    fl.open("student.dat",ios::binary|ios::in|ios::out);
    if(!fl)
    {
        cout << "\tFile could not be opened. Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
     while(!fl.eof() && found == false)
    {
        fl.read(reinterpret_cast<char *> (&stud), sizeof(student));
        if(stud.retrollno() == n)
        {
            stud.showdata();
            cout << "\n\n\tEnter new student details:\n";
            cout << "\t------------------------------\n";
            stud.getdata();
            int pos = (-1)*static_cast<int>(sizeof(stud));
            fl.seekp(pos, ios::cur);
            fl.write(reinterpret_cast<char *> (&stud), sizeof(student));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    fl.close();
    if(found == false)
        cout << "\n\n Record Not Found! ";
    cin.ignore();
    cin.get();
}
//delete record with particular roll number
void delete_student(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("student.dat",ios::binary);
    if(!iFile)
    {
        cout << "File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat",ios::out);
    iFile.seekg(0,ios::beg);
    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
    {
        if(stud.retrollno() != n)
        {
            oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
        }
    }
    oFile.close();
    iFile.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    cout << "\n\n\tRecord Deleted..!";
    cin.ignore();
    cin.get();
}
void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\n\t\tALL STUDENTS RESULT \n\n";
	cout << "\t=============================================================================================================================\n";
	cout << "\tR.No          " << setw(18) << left << "Name" << setw(15) << "Physics" << setw(15) << "Chemistry" << setw(15) << "Mathematics" << setw(13) << "English" << setw(20) << "Comp. Science" << setw(10) << "%age" << setw(12) << "Grade\n";
	cout << "\t=============================================================================================================================\n";


	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}

int main()
{
    char ch;
    int num;
    cout.setf(ios::fixed|ios::showpoint);
    cout << setprecision(2);
    do
    {
        system("cls");
        cout << "\n\n\n\t\t\t MENU";
        cout<<"\n\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n\n\t\t 1.CREATE STUDENT RECORD";
        cout << "\n\n\t\t 2.SEARCH STUDENT RECORD ";
        cout << "\n\n\t\t 3.DISPLAY ALL STUDENTS RECORDS";
        cout << "\n\n\t\t 4.MODIFY STUDENT RECORD";
        cout << "\n\n\t\t 5.DELETE STUDENT RECORD";
        cout << "\n\n\t\t 6. DISPLAY CLASS RESULT";
        cout << "\n\n\t\t 7. EXIT";
        cout << "\n\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n\n\t What is your Choice (1/2/3/4/5/6/7) ";
        cin >> ch;
        system("cls");
        switch(ch)
        {
            case '1':
                create_student();
                break;
            case '2':
                cout << "\n\n\tEnter The roll number ";
                cin >> num;
                display_sp(num);
                break;
            case '3':
                display_all();
                break;
            case '4':
                cout << "\n\n\tEnter The roll number ";
                cin>>num;
                change_student(num);
                break;
            case '5':
                cout << "\n\n\tEnter The roll number: ";
                cin >> num;
                delete_student(num);
                break;
            case '6' :
                class_result();
                break;
            case '7':
                cout << "Exiting, Thank you!";
                exit(0);
        }
    }while(ch != '7');
    return 0;
}
