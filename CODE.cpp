#include <bits/stdc++.h>
using namespace std;
class student
{
int rollno;
char name[50];
int phy, che, math, eng, cse;
int total;
double per;
char grade;
void calculate();//function to calculate grade
public:
void getdata(); //function to accept data from user
void showdata() const; //function to show data on screen
void show_tabular() const;
int retrollno() const;
int rettotal() const;
}; 
void student::calculate()
{
total=phy+che+math+eng+cse;
per=(total)/5.0;
if(per>=90)
grade='A';
else if(per>=80 && per<90)
grade='B';
else if(per>=70 && per<80)
grade='C';
else if(per>=60 && per<70)
grade='D';
else if(per>=50 && per<60)
 grade='E';
else
 grade='F';
}
void student::getdata()
{
cout<<"\nEnter The roll number of student ";
cin>>rollno;
cout<<"\n\nEnter The Name of student ";
cin.ignore();
cin.getline(name,50);
cout<<"\nEnter The marks in python out of 100 : ";
cin>>phy;
cout<<"\nEnter The marks in cpp out of 100 : ";
cin>>che;
cout<<"\nEnter The marks in maths out of 100 : ";
cin>>math;
cout<<"\nEnter The marks in economics out of 100 : ";
cin>>eng;
cout<<"\nEnter The marks in DAA out of 100 : ";
cin>>cse;
calculate();
}
void student::showdata() const
{
cout<<"\nRoll number of student : "<<rollno;
cout<<"\nName of student : "<<name;
cout<<"\nMarks in Python : "<<phy;
cout<<"\nMarks in Cpp : "<<che;
cout<<"\nMarks in Maths : "<<math;
cout<<"\nMarks in Economics : "<<eng;
cout<<"\nMarks in DAA :"<<cse;
cout<<"\nPercentage of the student is :"<<per;
cout<<"\nGrade of student is :"<<grade;
}
void student::show_tabular() const
{
cout<<rollno<<setw(6)<<" 
"<<name<<setw(10)<<phy<<setw(4)<<che<<setw(4)<<math<<setw(4)
<<eng<<setw(4)<<cse<<setw(4)<<total<<setw(8)<<per<<setw(6)<<grade<<endl;
}
int student::retrollno() const
{
return rollno;
}
int student::rettotal() const
{
return total;
}
void write_student(); //write the record in binary file
void display_all(); //read all records from binary file
void display_sp(int); //accept rollno and read record from binary file
void modify_student(int); //accept rollno and update record of binary file
void delete_student(int); //accept rollno and delete selected records from binary file
void display_top3(); //displays top 3 students
void class_result(); //display all records in tabular format from binary file
void result(); //display result menu
void entry_menu(); //display entry menu on screen
int main()
{
char ch;
do
{
cout<<"\n\n\n\tSRM STUDENT REPORT MANAGEMENT SYSTEM";
cout<<"\n\n\n\tMAIN MENU";
cout<<"\n\n\t01. RESULT MENU";
cout<<"\n\n\t02. ENTRY/EDIT MENU";
cout<<"\n\n\t03. EXIT";
cout<<"\n\n\tPlease Select Your Option (1-3) ";
cin>>ch;
switch(ch)
{
case '1': result();
break;
case '2': entry_menu();
break;
case '3':
break;
default :cout<<"\a";
}
 }while(ch!='3');
return 0;
}
void write_student()
{
student st;
ofstream outFile;
outFile.open("student.dat",ios::binary|ios::app);
st.getdata();
outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
outFile.close();
 cout<<"\n\nStudent record Has Been Created ";
cin.ignore();
cin.get();
}
void display_all()
{
student st;
ifstream inFile;
inFile.open("student.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
{
st.showdata();
cout<<"\n\n====================================\n";
}
inFile.close();
cin.ignore();
cin.get();
}
void display_sp(int n)
{
student st;
ifstream inFile;
inFile.open("student.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
{
if(st.retrollno()==n)
{
 st.showdata();
flag=true;
}
}
inFile.close();
if(flag==false)
cout<<"\n\nrecord not exist";
cin.ignore();
cin.get();
}
void modify_student(int n)
{
bool found=false;
student st;
fstream File;
File.open("student.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
 while(!File.eof() && found==false)
{
File.read(reinterpret_cast<char *> (&st), sizeof(student));
if(st.retrollno()==n)
{
st.showdata();
cout<<"\n\nPlease Enter The New Details of student"<<endl;
st.getdata();
 int pos=(-1)*static_cast<int>(sizeof(st));
 File.seekp(pos,ios::cur);
 File.write(reinterpret_cast<char *> (&st), sizeof(student));
 cout<<"\n\n\t Record Updated";
 found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}
void delete_student(int n)
{
student st;
ifstream inFile;
inFile.open("student.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
ofstream outFile;
outFile.open("Temp.dat",ios::out);
inFile.seekg(0,ios::beg);
while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
{
if(st.retrollno()!=n)
{
outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
}
}
outFile.close();
inFile.close();
remove("student.dat");
rename("Temp.dat","student.dat");
cout<<"\n\n\tRecord Deleted ..";
cin.ignore();
cin.get();
}
void display_top3()
{
student st;
ifstream inFile;
inFile.open("student.dat",ios::binary);
if(!inFile){
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
int index=0,i,j,temp,a[50];
while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student))){
a[index]=st.rettotal();
index++;
}
for(i=0;i<index;i++){
for(j=0;j<index;j++){
if(a[j]>a[i]){
temp=a[i];
a[i]=a[j];
a[j]=temp;
}
}
}
int k=index;
cout<<"\n\tTOP 3 MARKS ARE";
while(k-- &&k>index-4){
cout<<"\n\t"<<a[k];
}
}
void class_result()
{
student st;
ifstream inFile;
inFile.open("student.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
cout<<"===================================================
=======\n";
cout<<"R.No Name P C M E DAA %age Grade"<<endl;
cout<<"===================================================
=======\n";
while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
{
st.show_tabular();
}
cin.ignore();
cin.get();
inFile.close();
}
void result()
{
char ch;
int rno;
cout<<"\n\n\n\tRESULT MENU";
cout<<"\n\n\n\t1. Class Result";
cout<<"\n\n\t2. Student Report Card";
cout<<"\n\n\t3. Back to Main Menu";
cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
cin>>ch;
switch(ch)
{
case '1' :class_result(); break;
case '2' :cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
display_sp(rno); break;
case '3' :break;
default: cout<<"\a";
}
}
void entry_menu()
{
char ch;
int num;
cout<<"\n\n\n\tENTRY MENU";
cout<<"\n\n\t1.CREATE STUDENT RECORD";
cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
cout<<"\n\n\t4.MODIFY STUDENT RECORD";
cout<<"\n\n\t5.DELETE STUDENT RECORD";
cout<<"\n\n\t6.DISPLAY TOP 3 MARKS";
cout<<"\n\n\t7.BACK TO MAIN MENU";
cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
cin>>ch;
switch(ch)
{
case '1':write_student();break;
case '2':display_all();break;
case '3': cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
display_sp(num); break;
case '4': cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
modify_student(num);break;
case '5': cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
delete_student(num);break;
case '6':display_top3();break;
case '7': break;
default: cout<<"\a"; entry_menu();
}
}
