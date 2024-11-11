#include<stdio.h>
#include<string.h>
#include<stdlib.h>
# define size 100
#define maxteacher 50

struct student
{
    int roll;
    char first_name[50];
    char last_name[50];
    char grade[8];
    char class[10];
    int totalclasses;
    int attendedclasses;
    float gpa;
    int rank;
};
typedef struct
{
    char firstname[50];
    char lastname[50];
    char subject[50];
    char position[50];
} Teacher;

struct student students[size];
Teacher teachers[maxteacher];

int count=0;
int tcount=0;

const char USERNAME[]="abcd";
const char PASSWORD[] ="1234";

char Grade(float gpa)
{
    if (gpa==5.0) return 'A+';
    else if (gpa>=4.0) return 'A';
    else if (gpa>=3.5) return 'B';
    else if (gpa>=3.0) return 'C';
    else if(gpa>=2.5) return 'D';
    else return 'F';
}


void add_student() {
    if (count>=size) {
        printf("Can't add any more student!!! Storage is FULL....\n");
    } else {
        printf("Enter Roll Number: ");
        scanf("%d",&students[count].roll);

        printf("Enter First Name: ");
        scanf("%s",students[count].first_name);
        printf("Enter Last Name: ");
        scanf("%s",students[count].last_name);

        printf("Enter GPA: ");
        scanf("%f",&students[count].gpa);

        students[count].grade[0]=Grade(students[count].gpa);
        students[count].grade[1]='\0';
        printf("Enter Class: ");
        scanf("%s",students[count].class);

        students[count].totalclasses = 0;
        students[count].attendedclasses = 0;
        students[count].rank = 0;

        count++;
        printf("Student added successfully!\n");
    }
}

int attendance_percentage(int roll,char *class)
{
    int found=0;

    for (int i=0;i<count;i++)
    {
        if (students[i].roll==roll&&strcmp(students[i].class,class)==0)
        {
            if (students[i].totalclasses>0)
            {
                float attendance_percentage=(float)students[i].attendedclasses / students[i].totalclasses * 100;
                printf("Attendance percentage for Roll Number %d in Class %s is: %.2f%%\n", roll,class,attendance_percentage);

                if (attendance_percentage>=75)
                {
                    printf("Eligible to take the exam.\n");
                }
                else if (attendance_percentage>=65)
                {
                    printf("Warning: Attendance is below 75%%. Approval may be needed.\n");
                }
                else
                {
                    printf("Not eligible to take the final exam due to low attendance.\n");
                }
                return attendance_percentage;
            }
            else
            {
                printf("Total classes held is zero for Roll Number %d in Class %s. Attendance cannot be calculated.\n", roll, class);
                return -1;
            }
        }
    }
    printf("Student with Roll Number %d and Class %s not found.\n",roll,class);
    return -1;
}



void ranking()
{
    for (int i=0;i<count-1; i++)
    {
        for (int j=i+1;j<count;j++)
        {
            if (students[i].gpa<students[j].gpa)
            {
                struct student temp=students[i];
                students[i]=students[j];
                students[j]=temp;
            }
        }
    }
    for (int i=0;i<count;i++)
    {
        students[i].rank=i + 1;
    }
}

void display_students() {
    if (count == 0) {
        printf("NO STUDENT TO DISPLAY HERE!!!\n");
    } else {
        printf("......\nHERE IS A LIST OF STUDENTS......\n");
        for (int i = 0; i < count; i++) {
            printf("\nRank :%d\nRoll : %d\nName : %s %s\nGrade : %s\nClass : %s\n",
                   students[i].rank,students[i].roll,students[i].first_name,students[i].last_name, students[i].grade, students[i].class);
        }
    }
}

void update_attendance()
{
    char classnum[10];
    int roll;
    printf("Enter the student class number: ");
    scanf("%s",classnum);
    printf("Enter Roll to update attendance: ");
    scanf("%d",&roll);

    int found=0;
    for (int i=0;i<count;i++)
    {
        if (students[i].roll==roll&&strcmp(students[i].class,classnum)== 0)
        {
            int attendance;
            printf("Enter number of classes attended: ");
            scanf("%d",&attendance);

            students[i].attendedclasses += attendance;
            if (students[i].attendedclasses>students[i].totalclasses)
            {
                students[i].attendedclasses=students[i].totalclasses;
            }
            printf("Attendance updated successfully! Total attended: %d\n",students[i].attendedclasses);

            attendance_percentage(students[i].roll,students[i].class);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Student with Roll Number %d not found in Class %s.\n",roll,classnum);
    }
}

void total_classes()
{
    char class[10];
    printf("Please Enter Class number to update total classes: ");
    scanf("%s",class);
    int found = 0;
    int classheld,i;
    printf("Enter the number of classes held: \n");
    scanf("%d",&classheld);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].class, class) == 0)
        {
            students[i].totalclasses = students[i].totalclasses+classheld;
            if (students[i].attendedclasses>students[i].totalclasses)
            {
                students[i].attendedclasses = students[i].totalclasses;
                printf("Attended classes for Roll Number %d in Class %s cannot exceed total classes. Set attended classes to %d.\n",students[i].roll, students[i].class,students[i].attendedclasses);
            }


            found = 1;
        }
    }
    printf("Total classes updated successfully! Total classes held: %d\n",students[i].totalclasses);
    if (!found)
    {
        printf("Class %s not found.\n", class);
    }
}

void class_num() {
    char classname[10];
    printf("....Enter a class to search....\n");
    scanf("%s", classname);

    int found = 0;
    struct student class_students[size];
    int classcount = 0;

    for (int i=0;i<count;i++) {
        if (strcmp(students[i].class,classname) == 0) {
            class_students[classcount++]=students[i];
            found = 1;
        }
    }

    if (!found) {
        printf("No students found in Class %s.\n", classname);
        return;
    }

    for (int i = 0;i<classcount-1; i++) {
        for (int j =i+1;j<classcount;j++) {
            if (class_students[i].gpa<class_students[j].gpa) {
                struct student temp=class_students[i];
                class_students[i]=class_students[j];
                class_students[j]=temp;
            }
        }
    }

    printf("....Students in Class %s:....\n", classname);
    for (int i = 0; i<classcount; i++) {
        printf("\nRank: %d\nRoll: %d\nFirst Name: %s\nLast Name: %s\nGrade: %s\nGPA: %.2f\n",
               i + 1, class_students[i].roll, class_students[i].first_name,
               class_students[i].last_name, class_students[i].grade, class_students[i].gpa);
        attendance_percentage(class_students[i].roll, class_students[i].class);
    }
}

void student_id_class() {
    int roll;
    char class[10];
    printf("Enter the class number\n");
    scanf("%s",class);
    printf("Enter a roll to search: \n");
    scanf("%d",&roll);
    int found = 0;

    for (int i=0;i<count;i++) {
        if (students[i].roll==roll&&strcmp(students[i].class,class)==0) {
            printf("FOUND IT!!!\n");
            printf("Roll Number: %d\n",students[i].roll);
            printf("Name: %s %s\n",students[i].first_name, students[i].last_name);
            printf("Grade: %s\n",students[i].grade);
            printf("GPA: %.2f\n",students[i].gpa);
            printf("Class: %s\n",students[i].class);
            float attendancePercentage = attendance_percentage(students[i].roll,students[i].class);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with roll %d not found in Class %s.\n",roll,class);
    }
}
void delete_name() {
    int roll;
    char class_name[50];
    int found = 0;

    printf("Enter the roll number of the student to delete: ");
    scanf("%d",&roll);
    printf("Enter the class of the student to delete: ");
    scanf("%s",class_name);

    for (int i=0; i<count;i++) {
        if (students[i].roll==roll&&strcmp(students[i].class,class_name)== 0) {
            for (int j=i;j<count-1;j++) {
                students[j]=students[j + 1];
            }
            count--;
            printf("Student with Roll Number %d from Class %s deleted successfully.\n", roll, class_name);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d from Class %s not found.\n", roll, class_name);
    }
}



void modify_student() {
    int roll;
    char class[10];
    int found = 0;

    printf("Enter class: ");
    scanf("%s", class);
    printf("Enter roll number to modify: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll && strcmp(students[i].class, class) == 0) {
            printf("Enter new details:\n");

            printf("Enter new first name: ");
            scanf("%s", students[i].first_name);

            printf("Enter new last name: ");
            scanf("%s", students[i].last_name);

            printf("Enter new roll number: ");
            scanf("%d", &students[i].roll);

            printf("Enter grade: ");
            scanf("%s", students[i].grade);

            printf("Enter GPA: ");
            scanf("%f", &students[i].gpa);

            printf("Enter rank: ");
            scanf("%d", &students[i].rank);

            printf("\nStudent details modified successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d and Class %s not found.\n", roll, class);
    }
}

void modify_teacher()
{
    char firstname[50];
    char lastname[50];
    int found = 0;

    printf("Enter teacher's first name to modify: ");
    scanf("%s", firstname);
    printf("Enter teacher's last name to modify: ");
    scanf("%s", lastname);

    for (int i = 0; i < tcount; i++)
    {
        if (strcmp(teachers[i].firstname, firstname) == 0 && strcmp(teachers[i].lastname, lastname) == 0)
        {
            printf("Enter new details for the teacher:\n");

            printf("Enter new first name: ");
            scanf("%s", teachers[i].firstname);

            printf("Enter new last name: ");
            scanf("%s", teachers[i].lastname);

            printf("Enter new subject: ");
            scanf("%s", teachers[i].subject);

            printf("Enter new position: ");
            scanf("%s", teachers[i].position);

            printf("\nTeacher details modified successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Teacher with name %s %s not found.\n", firstname, lastname);
    }
}


void login_user()
{
    char username[50];
    char password[50];
    const char USERNAME[] = "abcd";
    const char PASSWORD[] = "1234";

    printf("\n|*********************************************|\n");
    printf("|                LOGIN SYSTEM                 |\n");
    printf("|*********************************************|\n");


    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);
    if (strcmp(username,USERNAME)==0&&strcmp(password, PASSWORD)==0)
    {
        printf("Login successful!\n");
    }
    else
    {
        printf("Invalid username or password. Exiting program...\n");
        exit(0);
    }
}

void addteacher()
{
    if (tcount < maxteacher)
    {
        getchar();

        printf("Enter First Name: ");
        fgets(teachers[tcount].firstname, 50, stdin);
        teachers[tcount].firstname[strcspn(teachers[tcount].firstname, "\n")] = '\0';

        printf("Enter Last Name: ");
        fgets(teachers[tcount].lastname, 50, stdin);
        teachers[tcount].lastname[strcspn(teachers[tcount].lastname, "\n")] = '\0';

        printf("Enter Subject: ");
        fgets(teachers[tcount].subject, 50, stdin);
        teachers[tcount].subject[strcspn(teachers[tcount].subject, "\n")] = '\0';

        printf("Enter Position: ");
        fgets(teachers[tcount].position, 50, stdin);
        teachers[tcount].position[strcspn(teachers[tcount].position, "\n")] = '\0';

        tcount++;
        printf("Teacher added successfully!\n");
    }
    else
    {
        printf("Teacher list is full.\n");
    }
}
void searchTeacher()
{
    char search_firstname[50];
    char search_lastname[50];
    int found = 0;

    printf("Enter teacher's first name to search: ");
    scanf("%s", search_firstname);
    printf("Enter teacher's last name to search: ");
    scanf("%s", search_lastname);

    for (int i = 0; i < tcount; i++)
    {
        if (strcmp(teachers[i].firstname, search_firstname) == 0 && strcmp(teachers[i].lastname, search_lastname) == 0)
        {
            printf("Teacher Found:\n");
            printf("Name: %s %s, Subject: %s, Position: %s\n",
                   teachers[i].firstname, teachers[i].lastname, teachers[i].subject, teachers[i].position);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Teacher not found.\n");
    }
}
void displayteachers()
{
    printf("List of Teachers:\n");
    for (int i = 0; i < tcount; i++)
    {
        printf("Name: %s %s, Subject: %s, Position: %s\n",
               teachers[i].firstname, teachers[i].lastname, teachers[i].subject, teachers[i].position);
    }
}

void deleteteacher()
{
    char firstname[50];
    char lastname[50];
    int found = 0;
    getchar();

    printf("Enter Teacher's First Name to delete: ");
    fgets(firstname, 50, stdin);
    firstname[strcspn(firstname, "\n")] = '\0';

    printf("Enter Teacher's Last Name to delete: ");
    fgets(lastname, 50, stdin);
    lastname[strcspn(lastname, "\n")] = '\0';

    for (int i = 0; i < tcount; i++)
    {
        if (strcmp(teachers[i].firstname, firstname) == 0 && strcmp(teachers[i].lastname, lastname) == 0)
        {
            for (int j = i; j < tcount - 1; j++)
            {
                teachers[j] = teachers[j + 1];
            }
            tcount--;
            printf("Teacher with name \"%s %s\" deleted successfully!\n", firstname, lastname);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Teacher not found.\n");
    }
}




int main()
{
    login_user();
    int choice;
    while(1)
    {
        printf("\n|*********************************************|\n");
        printf("|          SCHOOL MANAGEMENT SYSTEM           |\n");
        printf("|*********************************************|\n");
        printf("| 1. Add Student                              |\n");
        printf("| 2. Add Teacher                              |\n");
        printf("| 3. Update Total classes held                |\n");
        printf("| 4. Update Attendance                        |\n");
        printf("| 5. Find a student in Class                  |\n");
        printf("| 6. Find all students in a Class             |\n");
        printf("| 7. Search Teacher                           |\n");
        printf("| 8. Display All Students                     |\n");
        printf("| 9. Display All Teachers                     |\n");
        printf("| 10.Remove Student Name                      |\n");
        printf("| 11.Remove Teacher Name                      |\n");
        printf("| 12.Modify Student Information               |\n");
        printf("| 13.Modify Teacher Information               |\n");
        printf("| 14.Exit                                     |\n");
        printf("|*********************************************|\n");
        printf("Enter Your Choice: ");
        scanf("%d",&choice);

        if(choice == 1)
        {
            add_student();
        }
        else if(choice == 2)
        {
            addteacher();
        }
        else if(choice == 3)
        {
            total_classes();
        }
        else if(choice == 4)
        {
            update_attendance();
        }
        else if(choice == 5)
        {
            student_id_class();
        }
        else if(choice == 6)
        {
            class_num();
        }
        else if(choice == 7)
        {
            searchTeacher();
        }
        else if(choice==8)
        {
            display_students();
        }
        else if(choice==9)
        {
            displayteachers();
        }
        else if(choice==10)
        {
            delete_name();
        }
        else if(choice==11)
        {
            deleteteacher();
        }
        else if(choice==12)
        {
            modify_student();
        }
        else if(choice==13)
        {
            modify_teacher();
        }
        else if(choice == 14)
        {
            printf(".....EXITING PROGRAM.....\n");
            exit(0);
        }
        else
        {
            printf("Invalid choice! Please choose another option.\n");
        }
    }
}

