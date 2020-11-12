//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<fstream.h>
#include<iomanip.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>


//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class student
{
	int rollno;
	char name[50];
	int p_marks, c_marks, m_marks, e_marks, cs_marks;
	float per;
	char grade;
	void calculate();	//function to calculate grade
public:
	void getdata();		//function to accept data from user
	void showdata();	//function to show data on screen
	void show_tabular();
	int retrollno();
}; //class ends here


void student::calculate()
{
	per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
	if(per>=60)
		grade='A';
	else if(per>=50)
		grade='B';
	else if(per>=33)
		grade='C';
	else
		grade='F';
}

void student::getdata()
{
	cout<<"\nStudent Roll Number        :-";
	cin>>rollno;
	cout<<"\nName of student            :-";
	gets(name);
	cout<<"\nMarks in Physics (100)     :-";
	cin>>p_marks;
	cout<<"\nMarks in Chemistry (100)   :-";
	cin>>c_marks;
	cout<<"\nMarks in Mathematics (100) :-";
	cin>>m_marks;
	cout<<"\nMarks in English (100)     :-";
	cin>>e_marks;
	cout<<"\nMarks in Comp.Science (100):-";
	cin>>cs_marks;
	calculate();
}

void student::showdata()
{
	cout<<"\nRoll number of student    :- "<<rollno;
	cout<<"\nName of student           :- "<<name;
	cout<<"\nMarks in Physics          :- "<<p_marks;
	cout<<"\nMarks in Chemistry        :- "<<c_marks;
	cout<<"\nMarks in Maths            :- "<<m_marks;
	cout<<"\nMarks in English          :- "<<e_marks;
	cout<<"\nMarks in Computer Science :- "<<cs_marks;
	cout<<"\nPercentage of student is  :- "<<per;
	cout<<"\nGrade of student is       :- "<<grade;
}

void student::show_tabular()
{
	cout<<rollno<<" "<<setw(14)<<name<<setw(8)<<p_marks<<setw(8)<<c_marks<<setw(8)<<m_marks<<setw(8)<<e_marks<<setw(8)<<cs_marks<<setw(10)<<per<<setw(8)<<" "<<grade<<endl;
}

int  student::retrollno()
{
	return rollno;
}


//***************************************************************
//    	FUNTION DECLARATION
//****************************************************************

void write_student();		//write the record in binary file
void display_all();		//read all records from binary file
void display_sp(int);		//accept rollno and read record from binary file
void modify_student(int);	//accept rollno and update record of binary file
void delete_student(int);	//accept rollno and delete selected records from binary file
void class_result();		//display all records in tabular format from binary file
void result();			//display result menu
void intro();			//display welcome screen
void entry_menu();		//display entry menu on screen


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


void main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); // program outputs decimal number to two decimal places
	clrscr();
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU\n\n";
		cout<<"\n\n\t01. RESULT MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
			case '1': result();
				break;
			case '2':
				int c;
				char pass[9];
				char r[9]="teacher01";
				again:
				strcpy(pass,"         ");
				c=0;
				clrscr();
				cout<<"\n\n\n\tPassword: ";
				for(int i=0;i<9;i++)
				{
					pass[i] = getch();
					cout<<"*";
				}
				for(int j=0;j<9;j++)
				{
					if(pass[j]==r[j])
					{
						c+=1;
					}
				}
				clrscr();
				if(c==9)
				{
					cout<<"Correct Password"<<endl<<endl;
					entry_menu();
				}
				else
				{
					cout<<"Invalid Password\n\n Try Again\t\t\n";
					goto again;
				}

					break;
			case '3':
				break;
			default :cout<<"\a";
		}
	 }while(ch!='3');
	 getch();
}

//***************************************************************
//    	FUCTION TO WRITE IN FILE
//****************************************************************

void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write((char *) &st, sizeof(student));
	outFile.close();
	cout<<"\n\n--> RECORD CREATED!! ";
	cin.ignore();
	getch();
}

//***************************************************************
//    	FUNCTION TO READ SPECIFIC RECORD FROM FILE
//****************************************************************

void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";

		getch();
		return;
	}
	int flag=0;
	while(inFile.read((char *) &st, sizeof(student)))
	{
		if(st.retrollno()==n)
		{
			 st.showdata();
			 flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\n-->RECORD DOES NOT EXISTS!!";


	getch();
}

//***************************************************************
//    	FUNCTION TO MODIFY RECORD OF FILE
//****************************************************************

void modify_student(int n)
{
	int found=0;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";

		getch();
		return;
	}

	while(File.read((char *) &st, sizeof(student)) && found==0)
	{
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    int pos=(-1)*sizeof(st);
		    File.seekp(pos,ios::cur);
		    File.write((char *) &st, sizeof(student));
		    cout<<"\n\n--> RECORD UPDATED!!";
		    found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n-->RECORD NOT FOUND!! ";
	getch();
}

//***************************************************************
//    	FUNCTION TO DELETE RECORD OF FILE
//****************************************************************

void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		getch();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &st, sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write((char *) &st, sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\t-->RECORD DELETED!!";

	getch();
}

//***************************************************************
//    	FUNCTION TO DISPLAY ALL STUDENTS GRADE REPORT
//****************************************************************

void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";

		getch();
		return;
	}
	cout<<"\n\n\t\t\t\tALL STUDENTS RESULT \n\n";
	cout<<"================================================================================\n";
	cout<<"R.No"<<setw(14)<<"Name"<<setw(8)<<"P"<<setw(8)<<"C"<<setw(8)<<"M"<<setw(8)<<"E"<<setw(8)<<"CS"<<setw(10)<<"%age"<<setw(8)<<"Grade"<<endl;
	cout<<"================================================================================\n";
	while(inFile.read((char *) &st, sizeof(student)))
	{
		st.show_tabular();
	}

	getch();
	inFile.close();
}

//***************************************************************
//    	FUNCTION TO DISPLAY RESULT MENU
//****************************************************************

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
	clrscr();
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_sp(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	cout<<"\n\n\n\n\n\n\n\t\t\t\t  STUDENT";
	cout<<"\n\n\t\t\t\tREPORT CARD";
	cout<<"\n\n\t\t\t\t  PROJECT";
	cout<<"\n\n\n\n\n\n\nMade By:-Hrutik Champaneri,Praharsh Vanjara,Saurav Desai";
	cout<<"\n\nSchool:-SHREE VALLABH ASHRAM SCHOOL";
	getch();
}

//***************************************************************
//    	ENTRY / EDIT MENU FUNCTION
//****************************************************************

void entry_menu()
{
	char ch;
	int num;
	clrscr();
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t3.MODIFY STUDENT RECORD";
	cout<<"\n\n\t4.DELETE STUDENT RECORD";
	cout<<"\n\n\t5.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-5) ";
	cin>>ch;
	clrscr();
	switch(ch)
	{
	case '1':
			write_student();
			break;
	case '2':	cout<<"\n\nEnter the Roll Number:- "; cin>>num;
				display_sp(num); break;
	case '3':	cout<<"\n\nEnter the Roll Number:- "; cin>>num;
				modify_student(num);break;
	case '4':	cout<<"\n\nEnter the Roll Number:- "; cin>>num;
				delete_student(num);break;
	case '5':	break;
	default:	cout<<"\a"; entry_menu();
	}
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
