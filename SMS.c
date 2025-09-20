#include<stdio.h>
#include<conio.h>

struct student
{
    int Roll_no;
    char Name[50];
    float CGPA;
    int age;
};


void addStudent(){
    FILE *file;
    struct student newStudent;
    file = fopen("Students.dat", "ab");
    
    if(file == NULL){
        printf("There is an error in opening file");
        return;
    }

    printf("Enter Student's Roll No. : ");
    scanf("%d",&newStudent.Roll_no);
    printf("Enter Student's Full Name : ");
    scanf("%s",&newStudent.Name);
    printf("Enter Student's CGPA : ");
    scanf("%f",&newStudent.CGPA);
    printf("Enter Student's Age : ");
    scanf("%d",&newStudent.age);

    fwrite(&newStudent, sizeof(struct student), 1, file);
    fclose(file);
    printf("Student Added Successfully!!\n");
}
void displayStudent(){
    FILE *file;
    struct student s;
    file = fopen("Students.dat", "rb");

    if(!file){
        printf("There is an error in opening file!");
    }

    printf("---Students Record---\n");
    while(fread(&s, sizeof(s), 1, file)){
        printf("Roll no.: %d | Name: %s | CGPA: %f | Age: %d\n",s.Roll_no,s.Name,s.CGPA,s.age);
    }
    fclose(file);
}
void findStudent(){
    FILE *file;
    struct student s;
    file = fopen("Students.dat", "rb");
    int found = 0,roll;

    printf("Enter Student Roll no. to search him/her : ");
    scanf("%d",&roll);

    if(!file){
        printf("There is a problem in opening file!");
        return;
    }

    while(fread(&s, sizeof(s), 1, file)){
        if(s.Roll_no == roll){
            printf("Roll no.: %d | Name: %s | CGPA: %.2f | Age: %d\n",s.Roll_no,s.Name,s.CGPA,s.age);
            found = 1;
            break;
        }
    }
    if(!found){
        printf("No record found with that roll number..!");
    }

    fclose(file);

}
void updateStudent(){
    FILE *file;
    FILE *temp;
    struct student s;
    int found = 0,roll;

    file=fopen("Students.dat","rb");
    if(!file){
        printf("There is an problem in opening file!");
        return;
    }
    temp=fopen("Temp.dat","wb");
    if(!temp){
        printf("There is an error in opening file!");
        return;
    }
    
    printf("Enter Student Roll no. to update his/her details : ");
    scanf("%d",&roll);

    while(fread(&s, sizeof(s), 1, file)){
        if(s.Roll_no == roll){
            found = 1;
            printf("Enter the details for Roll No. %d\n",roll);
            printf("Name: "); scanf("%s",s.Name);
            printf("CGPA: "); scanf("%f",&s.CGPA);
            printf("Age: "); scanf("%d",&s.age);
        }
        fwrite(&s, sizeof(s), 1, temp);
    }
    fclose(file);
    fclose(temp);

    remove("Students.dat");
    rename("Temp.dat","Students.dat");

    if(found){
        printf("Student Detail updated successfully!\n");
    }
    else{
        printf("Student with Roll no. %d not found!!",roll);
    }

}
void deleteStudent(int roll){
    FILE *file;
    FILE *temp;
    struct student s;
    file=fopen("Students.dat","rb");
    temp=fopen("Temp.dat","wb");
    int found = 0;

    if(!file){
        printf("There is an problem in opening file!");
        return;
    }
    if(!temp){
        printf("There is an error in opening file!");
        return;
    }

    while(fread(&s, sizeof(s), 1, file)){
        if(s.Roll_no == roll){
            found = 1;
            printf("Removing details of Roll No. %d ......\n",roll);
            continue;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }
    fclose(file);
    fclose(temp);

    remove("Students.dat");
    rename("Temp.dat","Students.dat");

    if(found){
        printf("Student Detail Deleted successfully!\n");
    }
    else{
        printf("Student with Roll no. %d not found!!",roll);
    }
}

int main(){
    int choice;
    int kw,sc,dr;
    do{
    printf("---Please select your choice---\n");
    printf("---1. Add Student data.\n");
    printf("---2. Display all Student.\n");
    printf("---3. Search Student.\n");
    printf("---4. Update Student data.\n");
    printf("---5. Delete Student data.\n");
    printf("---6. Exit.\n");
    printf("-------------------------------\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        addStudent();
        break;
    case 2:
        displayStudent();
        break;
    case 3:
        findStudent();
        break;
    case 4:
        updateStudent();
        break;
    case 5:
        printf("Enter Student Roll no. to delete his/her details : ");
        scanf("%d",&dr);
        deleteStudent(dr);
        break;
    case 6:
        printf("Exiting the Program...Goodbye!\n");
        break;

    default:
        printf("Please Enter Correct Choice..");
        break;
    }
    } while (choice != 6);
    return 0;
}