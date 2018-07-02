//written by Chua Wei Zhe(132898) Group F

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


void officer(ifstream&,ofstream&,int[],string[], char[], string[], string[],int[],int&,int[]);
void student(int,int [],int [],int []);
void openFiles(ifstream&,int[],string[], char[], string[], string[],int[],int& );
void displaylist(int[],string[], char[], string[], string[],int[],int&,int [] );
void search_display(ofstream&,int[],string[], char[], string[], string[],int[],int&,int [],double&);
void addStudent(ofstream&, ifstream&, int[],string[], char[], string[], string[],int[],int&,int [],double& );
void qualified(int[],int&,int[],double&);
void countqualified(int[],int&,int[],double&);
int searchmatric(int, int [],int&,int [],int [],double&);
int searchname(string, string [],int&,int[],int [],double&);
int searchcontact(string, string [],int&,int [],int [],double&);
void overwrite(ofstream&,int[],string[], char[], string[], string[],int[],int& );
void byGender(int[],string[], char[], string[], string[],int[],int& );
void byqualified(int[],string[], char[], string[], string[],int[],int&,int []);
void byqualified_course(int[],string[], char[], string[], string[],int[],int&, int [] );
void byscorepoint(int[],string[], char[], string[], string[],int[],int& );
void bycourse(int[],string[], char[], string[], string[],int[],int& );

int main()
{
    system("color F0");
    char choice;
    char gender[100];
    int IDcounter_main=0;
    int counter_main=0;
    int matric[100];
    int scorepoint[100];
    int qualification[100];
    int id_number[100];
    double weightedaverage=0;
    string input;
    string name[100];
    string course[100];
    string contact[100];
    string officername[100];
    bool flag;

    ifstream inData_main; //input file stream variable
    ofstream outData_main; //output file stream variable

    do        //Show the Main screen menu
    {
        flag=false;
        system("cls");//clear the screen

        cout<<"********************************************************************************";
        cout<<"\n\t\t\t1-HOSTEL SYSTEM  \n\n";
        cout<<"********************************************************************************";
        cout<<"\n\t\t\tMAIN SCREEN \n\n";
        cout<<"Welcome, Who are you? "<<endl;
        cout<<"\n1.I am a Hostel managing officer"<<endl;
        cout<<"2.I am a Student"<<endl;
        cout<<"3.Exit program\n"<<endl;
        cout<<"Select your choice:";
        cin>>choice;
        system("cls");

        switch(choice)
        {
        case '1':
            cout <<"Enter the password(Case Sensitive): ";    //prompt password
            cin >>input;

            if(input=="cs2016")
            {
                flag=true;
            }
            if (flag)
            {
                officer(inData_main,outData_main,matric,course,gender,name,contact,scorepoint,counter_main,qualification);
            }
            else
            {
                cout <<"Wrong password! Back to main screen.\n";
                system("PAUSE");
                continue;

            }
            break;
        case '2':
            student(counter_main,matric,scorepoint,qualification);
            break;
        case '3':
            cout <<"Thanks you for using 1-Hostel System!\n";
            break;
        default:
            cout <<"Wrong Input! Please Try again!\n";
            system("PAUSE");
            cout <<"\a";
            break;
        }
    }
    while(choice!='3');
    return 0;
}



void officer(ifstream& inData,ofstream& outData,int matric[],string course[], char gender[], string name[], string contact[], int scorepoint[],int& counter,int qualification[])
{
    char choice;
    int i;
    for(i = 0; i < counter; i++)
    {
        qualification[i]=0;
    }
    double weightedaverage=101; //The value of weighted percentage will not be 101,so it is used to check whether the officer had input weighted percentage yet
    do   //show the menu for the officer
    {

        system("cls");
        cout<<"********************************************************************************";
        cout<<"\n\t\t\t1-HOSTEL SYSTEM  \n\n";
        cout<<"********************************************************************************";
        cout<<"\n\t\t\tHostel Managing Officer\n\n";
        cout<<"What would you like to do? "<<endl;
        cout<<"\n1. Read students's information from data.txt\n"<<endl;
        cout<<"2. Display all students' information\n"<<endl;
        cout<<"3. Display the total number of students based on:\n"<<endl;
        cout<<"4. Search,display and update specific student's information\n"<<endl;
        cout<<"5. Add new student's information \n"<<endl;
        cout<<"6. Input the Weighted Percentage\n" <<endl;
        cout<<"7. Return to main screen\n" <<endl;
        cout<<"Select your choice:";
        cin >>choice;
        switch(choice)
        {
        case '1':
            system("cls");
            openFiles(inData, matric,course,gender,name,contact,scorepoint,counter);
            break;
        case '2':
            system("cls");
            if (counter==0)
            {
                cout<<"The officer has not update the data yet.\n\n"; //officer has not read the data from data.txt yet
                system("PAUSE");
                break;
            }
            cout  <<"Matric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
            cout  <<"--------------------------------------------------------------------------------\n";

            for(i = 0; i < counter; i++)
            {

                cout <<setw(8) <<matric[i] <<"   " <<setw(10) <<name[i] <<setw(10) <<gender[i] <<setw(10) <<course[i] <<setw(18) <<contact[i] <<setw(14) <<scorepoint[i] <<"\n";
            }

            cout <<"\nThe number of students : " <<counter <<"\n";

            system("PAUSE");
            break;
        case '3':
            displaylist(matric,course,gender,name,contact,scorepoint,counter,qualification);
            break;
        case '4':
            search_display(outData,matric,course,gender,name,contact,scorepoint,counter,qualification,weightedaverage);
            break;
        case '5':
            addStudent(outData,inData, matric,course,gender,name,contact,scorepoint,counter,qualification,weightedaverage);
            break;
        case '6':
            qualified(scorepoint,counter,qualification,weightedaverage);
            break;
        case '7':
            system("cls");
            cout <<"Thanks you for using 1-Hostel System!\n";
            system("PAUSE");
            return;
        default:
            system("cls");
            cout <<"Wrong Input! Please Try again!\n";
            system("PAUSE");
            cout <<"\a";
            continue;
        }
    }
    while(choice!='7');

}


void openFiles(ifstream& inputF,int matric_function[],string course_function[], char gender_function[], string name_function[], string contact_function[], int scorepoint_function[],int& counter)
{
    counter=0;
    int matric;
    string course;
    string name;
    string contact;
    char gender;
    int scorepoint;

    inputF.open("data.txt");//Open input file

    if(inputF.is_open()) //file opened successfully
    {
        cout << "File opened successfully!\n"
             << "\nData is successfully inputted from 'data.txt' to the system!\n" << endl;
        while(inputF >> matric >> name >> gender >> course >> contact >> scorepoint ) //input the data from data.txt to system
        {
            matric_function[counter]=matric;
            name_function[counter]=name;
            gender_function[counter]=gender;
            course_function[counter]=course;
            contact_function[counter]=contact;
            scorepoint_function[counter]=scorepoint;
            counter++;
        }
        inputF.close();
    }

    else if (!inputF) //file opened fail
    {
        cout <<"FAILED";
        return;
    }
    system("PAUSE");

}

void displaylist(int matric_function[],string course_function[], char gender_function[], string name_function[], string contact_function[], int scorepoint_function[],int& counter,int qualification[])
{
    char choice;

    do //show the menu of which attribute would the user like to display a list
    {
        system("cls");
        cout <<"Based on?\n";
        cout <<"1. Score points\n";
        cout <<"2. Qualified status\n";
        cout <<"3. Qualified status by course code\n";
        cout <<"4. Gender\n";
        cout <<"5. Course code\n";
        cout <<"6. Back\n";
        cout <<"Select your choice:";
        cin >>choice;

        switch(choice)
        {
        case '1':
            byscorepoint(matric_function,course_function,gender_function,name_function,contact_function,scorepoint_function,counter);
            break;
        case '2':
            byqualified(matric_function,course_function,gender_function,name_function,contact_function,scorepoint_function,counter,qualification);
            break;
        case '3':
            byqualified_course(matric_function,course_function,gender_function,name_function,contact_function,scorepoint_function,counter,qualification);
            break;
        case '4':
            byGender(matric_function,course_function,gender_function,name_function,contact_function,scorepoint_function,counter);
            break;
        case '5':
            bycourse(matric_function,course_function,gender_function,name_function,contact_function,scorepoint_function,counter);
            break;
        case '6':
            cout <<"\nBack to officer screen.\n";
            system("PAUSE");
            return;
        }
    }
    while (choice!=6);

}

void byscorepoint(int matric_function[],string course_function[], char gender_function[], string name_function[], string contact_function[], int scorepoint_function[],int& counter)
{
    system("cls");
    char choice;
    int number;
    int i;
    int counter_list=0;
    cout <<"Please enter the score points: ";
    cin >>number;
    cout <<"\nPlease choose the following Relational Operators: \n";
    cout <<"1. More than " <<number <<"\n";
    cout <<"2. More than or equal to " <<number <<"\n";
    cout <<"3. Less than " <<number <<"\n";
    cout <<"4. Less than or equal to " <<number <<"\n";
    cout <<"Select your choice:";
    cin >>choice;
    switch(choice)
    {
    case '1':
        cout  <<"\nMatric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
        cout  <<"--------------------------------------------------------------------------------";

        for(i = 0; i < counter; i++)
        {
            if(scorepoint_function[i]>number)
            {

                cout <<setw(8) <<matric_function[i] <<"   " <<setw(10) <<name_function[i] <<setw(10) <<gender_function[i] <<setw(10) <<course_function[i] <<setw(18) <<contact_function[i] <<setw(14) <<scorepoint_function[i] <<"\n";
                counter_list++;
            }
        }

        cout <<"\nThe number of students : " <<counter_list <<"\n";
        system("PAUSE");

        break;
    case '2':
        cout  <<"\nMatric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
        cout  <<"--------------------------------------------------------------------------------";

        for(i = 0; i < counter; i++)
        {
            if(scorepoint_function[i]>=number)
            {

                cout <<setw(8) <<matric_function[i] <<"   " <<setw(10) <<name_function[i] <<setw(10) <<gender_function[i] <<setw(10) <<course_function[i] <<setw(18) <<contact_function[i] <<setw(14) <<scorepoint_function[i] <<"\n";
                counter_list++;
            }
        }

        cout <<"\nThe number of students : " <<counter_list <<"\n";
        system("PAUSE");

        break;
    case '3':
        cout  <<"\nMatric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
        cout  <<"--------------------------------------------------------------------------------";

        for(i = 0; i < counter; i++)
        {
            if(scorepoint_function[i]<number)
            {

                cout <<setw(8) <<matric_function[i] <<"   " <<setw(10) <<name_function[i] <<setw(10) <<gender_function[i] <<setw(10) <<course_function[i] <<setw(18) <<contact_function[i] <<setw(14) <<scorepoint_function[i] <<"\n";
                counter_list++;
            }
        }

        cout <<"\nThe number of students : " <<counter_list <<"\n";
        system("PAUSE");

        break;
    case '4':
        cout  <<"\nMatric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
        cout  <<"--------------------------------------------------------------------------------";

        for(i = 0; i < counter; i++)
        {
            if(scorepoint_function[i]<=number)
            {

                cout <<setw(8) <<matric_function[i] <<"   " <<setw(10) <<name_function[i] <<setw(10) <<gender_function[i] <<setw(10) <<course_function[i] <<setw(18) <<contact_function[i] <<setw(14) <<scorepoint_function[i] <<"\n";
                counter_list++;
            }
        }

        cout <<"\nThe number of students : " <<counter_list <<"\n";
        system("PAUSE");

        break;
    }
}

void byqualified(int matric_function[],string course_function[], char gender_function[], string name_function[], string contact_function[], int scorepoint_function[],int& counter,int qualification[])
{
    system("cls");
    char choice;
    int counter_list=0;
    int i;
    bool flag=false;


    if(qualification[0]==1 || qualification[0]==2) //if officer had not input the weighed percentage yet, it will return
    {
        flag=true;
    }
    if(!flag)
    {


        cout <<"Sorry,officer has not input the weightage yet.\n";
        system("PAUSE");
        return;

    }



    cout <<"Please choose the Qualified status: \n";
    cout <<"1. Qualified \n";
    cout <<"2. Not Qualified \n";
    cout <<"Select your choice:";
    cin >>choice;
    switch(choice)
    {
    case '1':

        cout  <<"\nMatric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
        cout  <<"--------------------------------------------------------------------------------";

        for(i = 0; i < counter; i++)
        {
            if(qualification[i]==1)
            {

                cout <<setw(8) <<matric_function[i] <<"   " <<setw(10) <<name_function[i] <<setw(10) <<gender_function[i] <<setw(10) <<course_function[i] <<setw(18) <<contact_function[i] <<setw(14) <<scorepoint_function[i] <<"\n";
                counter_list++;
            }
        }

        cout <<"\nThe number of students : " <<counter_list <<"\n";
        system("PAUSE");

        break;
    case '2':

        cout  <<"\nMatric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
        cout  <<"--------------------------------------------------------------------------------";

        for(i = 0; i < counter; i++)
        {
            if(qualification[i]==2)
            {

                cout <<setw(8) <<matric_function[i] <<"   " <<setw(10) <<name_function[i] <<setw(10) <<gender_function[i] <<setw(10) <<course_function[i] <<setw(18) <<contact_function[i] <<setw(14) <<scorepoint_function[i] <<"\n";
                counter_list++;
            }
        }

        cout <<"\nThe number of students : " <<counter_list <<"\n";
        system("PAUSE");

        break;
    }


}


void byqualified_course(int matric_function[],string course_function[], char gender_function[], string name_function[], string contact_function[], int scorepoint_function[],int& counter,int qualification[])
{
    system("cls");
    char choice;
    string course;
    bool flag=false;
    int i;
    int counter_list=0;

    if(qualification[0]==1 || qualification[0]==2) //if officer had not input the weighed percentage yet, it will return
    {
        flag=true;
    }
    if(!flag)
    {


        cout <<"Sorry,officer has not input the weightage yet.\n";
        system("PAUSE");
        return;

    }
    cout <<"Please choose the Qualified status: \n";
    cout <<"1. Qualified \n";
    cout <<"2. Not Qualified \n";
    cout <<"Select your choice:";
    cin >>choice;
    cout <<"\nPlease enter the course code in Capital Letter: ";
    cin >>course;

    switch(choice)
    {
    case '1':

        cout  <<"\nMatric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
        cout  <<"--------------------------------------------------------------------------------";

        for(i = 0; i < counter; i++)
        {
            if(qualification[i]==1 && course_function[i]==course)
            {

                cout <<setw(8) <<matric_function[i] <<"   " <<setw(10) <<name_function[i] <<setw(10) <<gender_function[i] <<setw(10) <<course_function[i] <<setw(18) <<contact_function[i] <<setw(14) <<scorepoint_function[i] <<"\n";
                counter_list++;
            }
        }

        cout <<"\nThe number of students : " <<counter_list <<"\n";
        system("PAUSE");

        break;
    case '2':

        cout  <<"\nMatric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
        cout  <<"--------------------------------------------------------------------------------";

        for(i = 0; i < counter; i++)
        {
            if(qualification[i]==2 && course_function[i]==course)
            {

                cout <<setw(8) <<matric_function[i] <<"   " <<setw(10) <<name_function[i] <<setw(10) <<gender_function[i] <<setw(10) <<course_function[i] <<setw(18) <<contact_function[i] <<setw(14) <<scorepoint_function[i] <<"\n";
                counter_list++;
            }
        }

        cout <<"\nThe number of students : " <<counter_list <<"\n";
        system("PAUSE");

        break;
    }
}

void byGender(int matric_function[],string course_function[], char gender_function[], string name_function[], string contact_function[], int scorepoint_function[],int& counter)
{
    system("cls");
    char inputgender;
    int i;
    int counter_list=0;
    cout <<"Enter the gender(M for Male, F for female)\n";
    cout <<"Select the gender:";
    cin >>inputgender;

    cout  <<"\nMatric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
    cout  <<"--------------------------------------------------------------------------------";

    for(i = 0; i < counter; i++)
    {
        if(inputgender==gender_function[i])
        {

            cout <<setw(8) <<matric_function[i] <<"   " <<setw(10) <<name_function[i] <<setw(10) <<gender_function[i] <<setw(10) <<course_function[i] <<setw(18) <<contact_function[i] <<setw(14) <<scorepoint_function[i] <<"\n";
            counter_list++;
        }
    }

    cout <<"\nThe number of students : " <<counter_list <<"\n";


    system("PAUSE");


}

void bycourse(int matric_function[],string course_function[], char gender_function[], string name_function[], string contact_function[], int scorepoint_function[],int& counter)
{
    system("cls");
    string inputcourse;
    int i;
    int counter_list=0;
    cout <<"Please enter the Course Code in Capital Letter:";
    cin >>inputcourse;

    cout  <<"\nMatric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
    cout  <<"--------------------------------------------------------------------------------";

    for(i = 0; i < counter; i++)
    {
        if(inputcourse==course_function[i])
        {

            cout <<setw(8) <<matric_function[i] <<"   " <<setw(10) <<name_function[i] <<setw(10) <<gender_function[i] <<setw(10) <<course_function[i] <<setw(18) <<contact_function[i] <<setw(14) <<scorepoint_function[i] <<"\n";
            counter_list++;
        }
    }
    cout <<"\nThe number of students : " <<counter_list <<"\n";
    system("PAUSE");
}





void search_display(ofstream& outputF,int matric_function[],string course_function[], char gender_function[], string name_function[], string contact_function[], int scorepoint_function[],int& counter,int qualification_function[],double& weightedaverage)
{
    char choice;
    int inputmatric;
    string inputstring;
    int result;


    for(;;)
    {
        system("cls");

        cout <<"By using: " <<"\n";
        cout <<"1. Matric.No\n";
        cout <<"2. Name\n";
        cout <<"3. Contact Number\n";
        cout <<"4. Back\n";
        cout <<"\nSelect your choice:";
        cin  >>choice;


        switch(choice)
        {
        case '1':
            cout <<"\nPlease enter the Matric No.: ";
            cin >>inputmatric;
            cin.clear();
            result=searchmatric(inputmatric,matric_function,counter,scorepoint_function,qualification_function,weightedaverage);
            if (result<=100)
            {
                cout  <<"Matric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
                cout  <<"--------------------------------------------------------------------------------";
                cout <<setw(8) <<matric_function[result] <<"   " <<setw(10) <<name_function[result] <<setw(10) <<gender_function[result] <<setw(10) <<course_function[result] <<setw(18) <<contact_function[result] <<setw(14) <<scorepoint_function[result] <<"\n";
                overwrite(outputF,matric_function,course_function,gender_function,name_function,contact_function,scorepoint_function,counter); //overwrite data.txt and update the scorepoint

            }
            system("PAUSE");
            break;
        case '2':
            cout <<"\nPlease enter the Name(Case Sensitive and without spaces): ";
            cin >>inputstring;
            result=searchname(inputstring,name_function,counter,scorepoint_function,qualification_function,weightedaverage);
            if (result<=100)
            {
                cout  <<"Matric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
                cout  <<"--------------------------------------------------------------------------------";
                cout <<setw(8) <<matric_function[result] <<"   " <<setw(10) <<name_function[result] <<setw(10) <<gender_function[result] <<setw(10) <<course_function[result] <<setw(18) <<contact_function[result] <<setw(14) <<scorepoint_function[result] <<"\n";
                overwrite(outputF,matric_function,course_function,gender_function,name_function,contact_function,scorepoint_function,counter);
            }
            system("PAUSE");
            break;
        case '3':
            cout <<"\nPlease enter the Contact Number: ";
            cin >>inputstring;
            result=searchcontact(inputstring,contact_function,counter,scorepoint_function,qualification_function,weightedaverage);
            if (result<=100)
            {
                cout  <<"Matric No.  " <<"    Name" <<"        " <<"Gender" <<"   " <<"Course"<<"\t" <<"Contact Number" <<"\t" <<"Score Point" <<"\n";
                cout  <<"--------------------------------------------------------------------------------";
                cout <<setw(8) <<matric_function[result] <<"   " <<setw(10) <<name_function[result] <<setw(10) <<gender_function[result] <<setw(10) <<course_function[result] <<setw(18) <<contact_function[result] <<setw(14) <<scorepoint_function[result] <<"\n";
                overwrite(outputF,matric_function,course_function,gender_function,name_function,contact_function,scorepoint_function,counter);
            }
            system("PAUSE");
            break;
        case '4':
            return;
        default:
            cout <<"\n";
            cout <<"Wrong Input! Please Try again!\n";
            system("PAUSE");
            cout <<"\a";
            break;
        }
    }
}

int searchmatric(int matricsearch,int matric_function[],int& counter,int scorepoint_function[],int qualification_function[],double& weightedaverage)
{
    int i=0;
    bool flag=false;
    int choice;
    int newscorepoint;
    for(i=0; i<counter; i++)
    {
        if(matric_function[i]==matricsearch)
        {
            flag=true;


            cout <<"\nDo you want to update score points?(1:Yes,0:No)\n";
            cin >>choice;
            if(choice==1)
            {
                cout <<"Please enter the new score point:";
                cin >>newscorepoint;
                scorepoint_function[i]=newscorepoint;
                if(weightedaverage!=101) //Check whether the officer had input weighted percentage yet.If yes,it will only recalculate the qualification status
                {
                    countqualified(scorepoint_function,counter,qualification_function,weightedaverage);
                }
                cout <<endl;
                break;

            }
            else if(choice==0)
            {
                cout <<endl;
                break;
            }
            else
            {
                cout <<"Invalid Input!\n";
                i=101;
                return i;

            }

        }
    }
    if(flag)
    {
        return i;
    }
    else
    {
        cout <<"Comments :Sorry, Invalid data." <<"\n\n";
        i=101;
        return i;
    }
    system("PAUSE");
}

int searchname(string namesearch,string name_function[],int& counter,int scorepoint_function[],int qualification_function[],double& weightedaverage)
{
    int i=0;
    bool flag=false;
    int choice;
    int newscorepoint;
    for(i=0; i<counter; i++)
    {
        if(name_function[i]==namesearch)
        {
            flag=true;

            cout <<"\nDo you want to update score points?(1:Yes,0:No)\n";
            cin >>choice;
            if(choice==1)
            {
                cout <<"Please enter the new score point:";
                cin >>newscorepoint;
                scorepoint_function[i]=newscorepoint;
                if(weightedaverage!=101) //Check whether the officer had input weighted percentage yet.If yes,it will only recalculate the qualification status
                {
                    countqualified(scorepoint_function,counter,qualification_function,weightedaverage);
                }
                cout <<endl;
                break;

            }
            else if(choice==0)
            {
                cout <<endl;
                break;
            }
            else
            {
                cout <<"Invalid Input!\n";
                i=101;
                return i;

            }

        }
    }
    if(flag)
    {
        return i;
    }
    else
    {
        cout <<"Comments :Sorry, Invalid data." <<"\n\n";
        i=101;
        return i;
    }
    system("PAUSE");
}

int searchcontact(string contactsearch,string contact_function[],int& counter,int scorepoint_function[],int qualification_function[],double& weightedaverage)
{
    int i=0;
    bool flag=false;
    int choice;
    int newscorepoint;
    for(i=0; i<counter; i++)
    {
        if(contact_function[i]==contactsearch)
        {
            flag=true;

            cout <<"\nDo you want to update score points?(1:Yes,0:No)\n";
            cin >>choice;
            if(choice==1)
            {
                cout <<"Please enter the new score point:";
                cin >>newscorepoint;
                scorepoint_function[i]=newscorepoint;
                if(weightedaverage!=101)  //Check whether the officer had input weighted percentage yet.If yes,it will only recalculate the qualification status
                {
                    countqualified(scorepoint_function,counter,qualification_function,weightedaverage);
                }
                cout <<endl;
                break;

            }
            else if(choice==0)
            {
                cout <<endl;
                break;
            }
            else
            {
                cout <<"Invalid Input!\n";
                i=101;
                return i;

            }

        }
    }
    if(flag)
    {
        return i;
    }
    else
    {
        cout <<"Comments :Sorry, Invalid data." <<"\n\n";
        i=101;
        return i;
    }
    system("PAUSE");
}

void overwrite(ofstream& outputF,int matric_function[],string course_function[], char gender_function[], string name_function[], string contact_function[], int scorepoint_function[],int& counter)
{
    int i;

    outputF.open("data.txt"); //Make data.txt blank
    outputF.close();

    outputF.open("data.txt");
    for(i=0; i<counter; i++) //Output the data to data.txt
    {

        outputF <<matric_function[i] <<" " <<name_function[i] <<" " <<gender_function[i] <<" " <<course_function[i] <<" " <<contact_function[i] <<" " <<scorepoint_function[i] <<endl;

    }
    outputF.close();
}


void addStudent(ofstream& outputF,ifstream& inputF,int matric_function[],string course_function[], char gender_function[], string name_function[], string contact_function[], int scorepoint_function[],int& counter,int qualification_function[],double& weightedaverage)
{
    system("cls");
    int newmatric;
    string newname;
    char newgender;
    string newcourse;
    string newcontact;
    int newscore;

    int matric;
    string name;
    char gender;
    string course;
    string contact;
    int scorepoint;

    char choice;

    for(;;)
    {
        system("cls");
        cout<<"********************************************************************************";
        cout<<"\n\t\t\t Add New Student Information  \n\n";
        cout<<"********************************************************************************";
        counter=0;
        outputF.open("data.txt", ios::app);
        cout <<"\nEnter Matric No: ";
        cin >>newmatric;
        cout <<"Enter the Name(Case Sensitive and without spaces): ";
        cin >>newname;
        for(;;)
        {
            cout <<"Enter the gender(M for Male, F for female): ";
            cin >>newgender;
            if (newgender=='M' || newgender=='F')
            {
                break;
            }
            else
            {
                cout <<"\nInvalid Input!Please try again.\n\n";
            }
        }
        cout <<"Enter the Course Code in CAPITAL LETTER: ";
        cin >>newcourse;
        cout <<"Enter Contact Number: ";
        cin >>newcontact;
        for(;;)
        {
            cout <<"Enter the score point: ";
            cin >>newscore;
            if(newscore<0) //To check user has input invalid scorepoint, if yes , prompt the user to input again.
            {
                cout <<"\nInvalid score point!Please reenter the correct score point.\n";
                continue;
            }
            break;
        }
        outputF <<newmatric <<" " <<newname <<" " <<newgender <<" " <<newcourse <<" " <<newcontact <<" " <<newscore <<endl; //Output new student information to data.txt
        outputF.close();
        inputF.open("data.txt");
        if(inputF.is_open())    //Read again to ensure new student's information is stored in the system
        {
            while(inputF >> matric >> name >> gender >> course >> contact >> scorepoint )
            {
                matric_function[counter]=matric;
                name_function[counter]=name;
                gender_function[counter]=gender;
                course_function[counter]=course;
                contact_function[counter]=contact;
                scorepoint_function[counter]=scorepoint;
                counter++;
            }
            inputF.close();
        }
        do
        {
            cout <<"\nDo you want to continue adding new student's information?(1:Yes,0:No)\n"; //Check whether the user would like to add more new student's information
            cin >>choice;
            if(choice=='1')
            {
                break;
            }
            if(choice=='0')
            {
                if(weightedaverage!=101) //Check whether the officer had input weighted percentage yet.If yes,it will only recalculate the qualification status
                {
                    countqualified(scorepoint_function,counter,qualification_function,weightedaverage);
                }
                cout <<"\nBack to officer screen.\n";
                system("PAUSE");
                return;
            }
            else
            {
                cout <<"Invalid Input.\n";
            }
        }
        while(choice!=1);
        continue;
    }
}

void qualified(int scorepoint[],int& counter,int qualification[],double&  weightedaverage)
{

    double sum;
    double average;
    double mustscore;
    int i;
    system("cls");
    if (counter==0)    //Check whether the officer had read students information from data.txt or not
    {
        cout <<"The officer has not update the data yet.\n";
        system("PAUSE");
        return;
    }
    for(i=0; i<counter; i++)
    {
        sum+=scorepoint[i];
    }
    average=(sum)/counter;

    for(;;)
    {
        system("cls");
        cout<<"********************************************************************************";
        cout<<"\n\t\t\t Weighted Percentage  \n\n";
        cout<<"********************************************************************************";
        cout <<"\nPlease enter the weighted percentage in %(1-100).\n";
        cout <<"Weighted Percentage: ";
        cin >> weightedaverage;
        if( weightedaverage<1||weightedaverage>100)
        {
            cout <<"Please only input the weighted percentage in %(1-100).\n";
            system("PAUSE");
        }
        else
        {
            break;
        }
    }
    mustscore=(average+(( weightedaverage/100)*average));
    for(i=0; i<counter; i++)
    {
        if(scorepoint[i]>=mustscore) //1 is qualified to apply for hostel, 2 is not
        {
            qualification[i]=1;
        }
        else
        {
            qualification[i]=2;
        }
    }     /*let officer know the lowest scorepoint to apply for hostel*/
    cout <<"\nStudent must score at least " <<(static_cast<int>(mustscore))+1 <<" or above to apply for hostel.";
    cout <<"\n\nReminder:Weighted Percentage and qualification status will reset on every \n         officer login!\n";
    cout <<"\nNow back to officer screen\n";
    system("PAUSE");
}


void countqualified(int scorepoint[],int& counter,int qualification[],double& weightedaverage)
{
    double sum;
    double average;
    double mustscore;
    int i;

    for(i=0; i<counter; i++)
    {
        sum+=scorepoint[i];
    }
    average=(sum)/counter;

    mustscore=(average+(( weightedaverage/100)*average));
    for(i=0; i<counter; i++)
    {
        if(scorepoint[i]>=mustscore) //1 is qualified to apply for hostel, 2 is not
        {
            qualification[i]=1;
        }
        else
        {
            qualification[i]=2;
        }
    }
    system("cls");
    cout <<"\nStudent must score at least " <<(static_cast<int>(mustscore))+1 <<" or above to apply for hostel.\n\n";
}


void student(int counter,int matric[],int scorepoint[],int qualification[])
{
    if (counter==0)
    {
        cout<<"The officer has not update the data yet.\n\n"; //officer has not read the data from data.txt yet
        system("PAUSE");
        return;
    }
    int matricInput;
    int i;
    bool flag;
    do
    {
        system("cls");
        flag=false;
        cout<<"********************************************************************************";
        cout<<"\n\t\t\t1-HOSTEL SYSTEM  \n\n";
        cout<<"********************************************************************************";
        cout<<"\n\t\t\tStudent \n\n";
        cout<<"You can only check your collected points and your qualification status."<<endl;
        cout<<"Enter 0 to return to main screen. " <<endl;
        cout<<"\nMatric Number:";
        cin >>matricInput;
        for(i=0; i<counter; i++)
        {
            if(matric[i]==matricInput)
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            cout <<"Your collected points : " <<scorepoint[i] <<"\n\n";
            if(qualification[i]==1)
            {
                cout <<"Congratulation, you are qualified to apply for hostel.\n";
            }
            else if (qualification[i]==2)
            {
                cout <<"Sorry, you are not qualified to apply for hostel.\n";
            }
            else
            {
                cout <<"Sorry, officer has not input the weightage yet.\n";
            }


        }
        else if(matricInput==0)
        {
            cout<<"Thank You!Back to Main Screen!\n\n";
        }
        else
        {
            cout <<"Sorry, Invalid data." <<"\n\n";
        }
        system("PAUSE");
    }
    while(matricInput!=0);
    return;
}


