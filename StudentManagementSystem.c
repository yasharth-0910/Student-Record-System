#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct StudentInfo
{
    char ID[10];
    char Name[20];
    char Email[30];
    char Phone[20];
    int  NumberOfCourse;
};
struct CourseInfo
{
    char StudentID[10];
    char Code[10];
    char Name[20];
};

struct StudentInfo Students[100];
struct CourseInfo Courses[500];

int i,j;
int TotalStudents = 0;
int TotalCourse = 0;
char StudentID[10];

bool IsRunning = true;
void Menu();
void AddNewStudent();
void ShowAllStudents();
int  SearchStudent(char StudentID[10]);
void EditStudent(int StudentFoundIndex);
void DeleteStudent(int StudentIndex);
void DeleteAllStudents();
int  IsAlreadyExists(char GivenLine[30],char InfoType, char StudentID[300]);
void DeleteStudentByIndex(int CourseIndex);
void GoBackOrExit();
void ExitProject();


int main()
{
    while(IsRunning)
    {
        Menu();
        int Option;
        scanf("%d",&Option);
        switch(Option)
        {
        case 0:
            IsRunning = false;
            ExitProject();
            break;
        case 1:
            system("cls");
            printf("\n\t\t **** Add A New Student ****\n\n");
            AddNewStudent();
            GoBackOrExit();
            break;
        case 2:
            system("cls");
            printf("\n\t\t **** All Students ****\n\n");
            ShowAllStudents();
            GoBackOrExit();
            break;
        case 3:
        {
            system("cls");
            printf("\n\t\t **** Search Students ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            int IsFound = SearchStudent(StudentID);
            if(IsFound<0)
            {
                printf(" No Student Found\n\n");
            }
            printf("\n");
            GoBackOrExit();
            break;
        }
        case 4:
            system("cls");
            printf("\n\t\t **** Edit a Student ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            int StudentFoundIndex = SearchStudent(StudentID);

            if(StudentFoundIndex>=0)
            {
                EditStudent(StudentFoundIndex);
            }
            else
            {
                printf(" No Student Found\n\n");
            }
            GoBackOrExit();
            break;
        case 5:
            system("cls");
            printf("\n\t\t **** Delete a Student ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);

            int DeleteStudentFoundIndex = SearchStudent(StudentID);

            if(DeleteStudentFoundIndex>=0)
            {
                char Sure = 'N';
                getchar();
                printf("\n\n");
                printf(" Are you sure want to delete this student? (Y/N): ");
                scanf("%c",&Sure);

                if(Sure == 'Y' || Sure == 'y')
                {
                    DeleteStudent(DeleteStudentFoundIndex);
                }
                else
                {
                    printf(" Your Data is Safe.\n\n");
                    GoBackOrExit();
                }

            }
            else
            {
                printf(" No Student Found\n\n");
                GoBackOrExit();
            }

            break;
        case 6:
        {
            char Sure = 'N';
            getchar();
            system("cls");
            printf("\n\t\t **** Delete ALL Students ****\n\n");

            printf(" Are you sure want to delete all the students? (Y/N): ");
            scanf("%c",&Sure);
            if(Sure == 'Y' || Sure == 'y')
            {
                DeleteAllStudents();
            }
            else if(Sure == 'N' || Sure == 'n')
            {
                printf(" Your Data is Safe.\n\n");
                GoBackOrExit();
            }
            else{
                printf("Looks like you entered something else well please return program now \n");
                return 0;
            }
            break;
        }
        default:
            ExitProject();
            break;
        }
    }

    return 0;
}

void Menu()
{
    printf("\n\n\t***Student Management System Using C***\n\n");
    printf("\t\t\tMAIN MENU\n");
    printf("\t\t----------------------------------\n");
    printf("\t\t 1. Add A New student.\n");
    printf("\t\t 2. Show All students.\n");
    printf("\t\t 3. Search A student.\n");
    printf("\t\t 4. Edit A student.\n");
    printf("\t\t 5. Delete A student.\n");
    printf("\t\t 6. Delete All students.\n");
    printf("\t\t 0. Exit the Program.\n");
    printf("\t\t----------------------------------\n");
    printf("\t\tEnter The Choice: ");
} 

void AddNewStudent()
{
    char StudentID[300];
    char Name[300];
    char Phone[300];
    char Email[300];
    int NumberOfCourses;
    char CourseCode[300];
    char CourseName[300];

    int IsValidID = 0;
    while(!IsValidID)
    {
        printf(" Enter The ID: ");
        scanf("%s",&StudentID);
        if(IsAlreadyExists(StudentID,'i',StudentID) > 0)
        {
            printf(" Error: This ID is already exists.\n\n");
            IsValidID = 0;
        }
        else if(strlen(StudentID) > 10)
        {
            printf(" Error: ID can not be more than 10 characters.\n\n");
            IsValidID = 0;
        }
        else if(strlen(StudentID) <= 0)
        {
            printf(" Error: ID can not be empty.\n\n");
            IsValidID = 0;
        }
        else
        {
            IsValidID = 1;
        }
    }

    int IsValidName = 0;
    while(!IsValidName)
    {
        printf(" Enter The Name: ");
        scanf(" %[^\n]s",&Name);
        if(strlen(Name) > 20)
        {
            printf(" Error: Name can not be more than 20 characters.\n\n");
            IsValidName = 0;
        }
        if(strlen(Name) <= 0)
        {
            printf(" Error: Name can not be empty.\n\n");
            IsValidName = 0;
        }
        else
        {
            IsValidName = 1;
        }
    }

    int IsValidEmail = 0;
    while(!IsValidEmail)
    {
        printf(" Enter The Email: ");
        scanf("%s",&Email);
        if(IsAlreadyExists(Email,'e',StudentID) > 0)
        {
            printf(" This Email is Already Exists.\n");
            IsValidEmail = 0;
        }
        else if(strlen(Email) > 30)
        {
            printf(" Error: Email can not be more than 30 characters.\n\n");
            IsValidEmail = 0;
        }
        else if(strlen(Email) <= 0)
        {
            printf(" Error: Email can not be empty.\n\n");
            IsValidEmail = 0;
        }
        else
        {
            IsValidEmail = 1;
        }
    }

    int IsValidPhone = 0;
    while(!IsValidPhone)
    {
        printf(" Enter The Phone: ");
        scanf("%s",&Phone);
        if(IsAlreadyExists(Phone,'p',StudentID) > 0)
        {
            printf(" This Phone Number is Already Exists\n");
            IsValidPhone = 0;
        }
        else if(strlen(Phone) > 20)
        {
            printf(" Error: Phone can not be more than 20 characters.\n\n");
            IsValidPhone = 0;
        }
        else if(strlen(Phone) <= 0)
        {
            printf(" Error: Phone can not be empty.\n\n");
            IsValidPhone = 0;
        }
        else
        {
            IsValidPhone = 1;
        }
    }

    int IsValidNumberOfCourse = 0;
    while(!IsValidNumberOfCourse)
    {
        printf(" Number of courses: ");
        scanf("%d",&NumberOfCourses);
        if(NumberOfCourses <= 0 || NumberOfCourses > 4)
        {
            printf(" Error: Number of courses can not be more than 4 and lees than 1.\n\n");
            IsValidNumberOfCourse = 0;
        }
        else
        {
            IsValidNumberOfCourse = 1;
        }
    }

    strcpy(Students[TotalStudents].ID,StudentID);
    strcpy(Students[TotalStudents].Name,Name);
    strcpy(Students[TotalStudents].Phone,Phone);
    strcpy(Students[TotalStudents].Email,Email);
    Students[TotalStudents].NumberOfCourse = NumberOfCourses;
    TotalStudents++;

    for(i=0; i<NumberOfCourses; i++)
    {

        printf(" Enter Course %d Code: ",i+1);
        scanf("%s",&CourseCode);

        printf(" Enter Course %d Name: ",i+1);
        scanf(" %[^\n]s",&CourseName);

        strcpy(Courses[TotalCourse].StudentID,StudentID);
        strcpy(Courses[TotalCourse].Code,CourseCode);
        strcpy(Courses[TotalCourse].Name,CourseName);
        TotalCourse++;
    }

    printf("\n Student Added Successfully.\n\n");
}

void ShowAllStudents()
{
    printf("|----------|--------------------|------------------------------|--------------------|-------------|\n");
    printf("|    ID    |        Name        |            Email             |       Phone        |  NO.Course  |\n");
    printf("|----------|--------------------|------------------------------|--------------------|-------------|\n");

    for(i=0; i<TotalStudents; i++)
    {
        printf("|");
        printf("%s",Students[i].ID);
        for(j=0; j < (10-strlen(Students[i].ID)); j++)
        {
            printf(" ");
        }
        printf("|");
        printf("%s",Students[i].Name);
        for(j=0; j < (20-strlen(Students[i].Name)); j++)
        {
            printf(" ");
        }
        printf("|");
        printf("%s",Students[i].Email);
        for(j=0; j < (30-strlen(Students[i].Email)); j++)
        {
            printf(" ");
        }
        printf("|");
        printf("%s",Students[i].Phone);
        for(j=0; j < (20-strlen(Students[i].Phone)); j++)
        {
            printf(" ");
        }
        printf("|");
        printf("%d",Students[i].NumberOfCourse);
        for(j=0; j < 12; j++)
        {
            printf(" ");
        }
        printf("|\n");
        printf("|----------|--------------------|------------------------------|--------------------|-------------|\n");

    }
    printf("\n");
}

int SearchStudent(char StudentID[10])
{
    system("cls");
    int StudentFoundIndex = -1;

    int i;
    for(i=0; i<TotalStudents; i++)
    {
        if(strcmp(StudentID,Students[i].ID) == 0)
        {
            StudentFoundIndex = i;
            printf("\n One Student Found for ID: %s\n\n",StudentID);
            printf(" Student Informations\n");
            printf("-------------------------\n");

            printf(" ID:    %s\n",Students[i].ID);
            printf(" Name:  %s\n",Students[i].Name);
            printf(" Email: %s\n",Students[i].Email);
            printf(" Phone: %s\n",Students[i].Phone);
            printf("\n Total Number of Courses: %d\n",Students[i].NumberOfCourse);
        }
    }
    int CourseCount = 0;
    int j;
    for(j=0; j<TotalCourse; j++)
    {
        if(strcmp(StudentID,Courses[j].StudentID) == 0)
        {
            CourseCount++;
            printf(" Course %d Code: %s\n",CourseCount,Courses[j].Code);
            printf(" Course %d Name: %s\n",CourseCount,Courses[j].Name);
        }
    }

    return StudentFoundIndex;
}

void EditStudent(int StudentFoundIndex)
{
    printf("\n\t\t **** Update The New Student ****\n\n");

    char NewName[300];
    char NewPhone[300];
    char NewEmail[300];
    int NewNumberOfCourses;
    char StudentID[300];
    strcpy(StudentID, Students[StudentFoundIndex].ID);
    int OldTotalNumberOfCourse = Students[StudentFoundIndex].NumberOfCourse;

    int IsValidName = 0;
    while(!IsValidName)
    {
        printf(" Enter The New Name(0 for skip): ");
        scanf(" %[^\n]s",&NewName);
        if(strlen(NewName) > 20)
        {
            printf(" Error: Name can not be more than 20 characters.\n\n");
            IsValidName = 0;
        }
        else if(strlen(NewName) <= 0)
        {
            printf(" Error: Name can not be empty.\n\n");
            IsValidName = 0;
        }
        else
        {
            IsValidName = 1;
        }
    }

    int IsValidEmail = 0;
    while(!IsValidEmail)
    {
        printf(" Enter The New Email(0 for skip): ");
        scanf("%s",&NewEmail);

        if(strlen(NewEmail) > 30)
        {
            printf(" Error: Email can not be more than 30 characters.\n\n");
            IsValidEmail = 0;
        }
        else if(strlen(NewEmail) <= 0)
        {
            printf(" Error: Email can not be empty.\n\n");
            IsValidEmail = 0;
        }
        else if(IsAlreadyExists(NewEmail,'e',StudentID) > 0)
        {
            printf(" Error: This Email Already Exists.\n\n");
            IsValidEmail = 0;
        }
        else
        {
            IsValidEmail = 1;
        }
    }

    int IsValidPhone = 0;
    while(!IsValidPhone)
    {
        printf(" Enter The New Phone(0 for skip): ");
        scanf("%s",&NewPhone);

        if(strlen(NewPhone) > 20)
        {
            printf(" Error: Phone can not be more than 20 characters.\n\n");
            IsValidPhone = 0;
        }
        else if(strlen(NewPhone) <= 0)
        {
            printf(" Error: Phone can not be empty.\n\n");
            IsValidPhone = 0;
        }
        else if(IsAlreadyExists(NewPhone,'p',StudentID) > 0)
        {
            printf(" Error: This Phone Number is Already Exists.\n\n");
            IsValidPhone = 0;
        }
        else
        {
            IsValidPhone = 1;
        }
    }

    int IsValidNumberOfCourse = 0;
    while(!IsValidNumberOfCourse)
    {
        printf(" Number of New courses(0 for skip): ");
        scanf("%d",&NewNumberOfCourses);

        if(NewNumberOfCourses > 4 || NewNumberOfCourses < 0)
        {
            printf(" Error: A Student can have maximum 4 and Minimum 0 number of courses.\n\n");
            IsValidNumberOfCourse = 0;
        }
        else
        {
            IsValidNumberOfCourse = 1;
        }
    }

    if(strcmp(NewName,"0") != 0)
    {
        strcpy(Students[StudentFoundIndex].Name,NewName);
    }

    if(strcmp(NewEmail,"0") != 0)
    {
        strcpy(Students[StudentFoundIndex].Email,NewEmail);
    }

    if(strcmp(NewPhone,"0") != 0)
    {
        strcpy(Students[StudentFoundIndex].Phone,NewPhone);
    }

    if(NewNumberOfCourses != 0)
    {
        int OldTotalCourse = Students[StudentFoundIndex].NumberOfCourse;
        Students[StudentFoundIndex].NumberOfCourse = NewNumberOfCourses;


        int FirstCourseIndex;
        int dc;
        for(dc=0; dc<TotalCourse; dc++)
        {
            if(strcmp(StudentID,Courses[dc].StudentID) == 0)
            {
                FirstCourseIndex = dc;
                break;
            }
        }

        char CourseCode[300];
        char CourseName[300];
        for(i=1; i<=NewNumberOfCourses; i++)
        {
            printf(" Enter New Course %d Code: ",i);
            scanf("%s",&CourseCode);

            printf(" Enter New Course %d Name: ",i);
            scanf(" %[^\n]s",&CourseName);

            strcpy(Courses[TotalCourse].StudentID,StudentID);
            strcpy(Courses[TotalCourse].Code,CourseCode);
            strcpy(Courses[TotalCourse].Name,CourseName);
            TotalCourse++;
        }
    }

    printf(" Student Updated Successfully.\n\n");

}

void DeleteStudent(int StudentIndex)
{
    int d;
    int FirstCourseIndexs;
    struct StudentInfo ThisStudents;
    ThisStudents = Students[StudentIndex];
    for(d=0; d<TotalCourse; d++)
    {
        if(strcmp(ThisStudents.ID,Courses[d].StudentID) == 0)
        {
            FirstCourseIndexs = d;
            break;
        }
    }

    DeleteStudentByIndex(StudentIndex);
    printf(" Student Deleted Successfully.\n\n");
    GoBackOrExit();
}

void DeleteAllStudents()
{
    TotalStudents = 0;
    TotalCourse = 0;
    printf(" All Students Deleted Successfully.\n\n");
    GoBackOrExit();
}

void DeleteStudentByIndex(int CourseIndex)
{
    int s;
    for(s=0; s<TotalStudents-1; s++)
    {
        if(s>=CourseIndex)
        {
            Students[s] = Students[s+1];
        }
    }
    TotalStudents--;
}


int IsAlreadyExists(char GivenLine[300],char InfoType, char StudentID[300])
{
    int EmailExists = 0;
    int PhoneExists = 0;
    int IDExists = 0;
    int ep;

    for(ep=0; ep<TotalStudents; ep++)
    {
        if(strcmp(GivenLine,Students[ep].ID) == 0)
        {
            IDExists++;
        }
        if(strcmp(GivenLine,Students[ep].Email) == 0 && strcmp(StudentID,Students[ep].ID) != 0 )
        {
            EmailExists++;
        }
        if(strcmp(GivenLine,Students[ep].Phone) == 0 && strcmp(StudentID,Students[ep].ID) != 0)
        {
            PhoneExists++;
        }

    }

    if(InfoType == 'i')
    {
        return IDExists;
    }
    else if(InfoType == 'e')
    {
        return EmailExists;
    }
    else if(InfoType == 'p')
    {
        return PhoneExists;
    }
    else
    {
        return 0;
    }
}
void GoBackOrExit()
{
    getchar();
    char Option;
    printf(" Go back(b)? or Exit(0)?: ");
    scanf("%c",&Option);
    if(Option == '0')
    {
        ExitProject();
    }
    else
    {
        system("cls");
    }
}

void ExitProject()
{
    system("cls");

    printf("\n");

    printf("--------------Thank you for trying my program hope to see you soon ---------------------- \n");
    printf("Program made by Yasharth Singh \n");
    exit(0);
}

