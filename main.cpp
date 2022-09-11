#include <bits/stdc++.h>

using namespace std;
typedef struct node_for_subjects{
    char subject[10];
    int grade;
    struct node_for_subjects *next;
    struct node_for_subjects *prev;
}Node;


typedef struct student{
    char index[10];
    struct student *next_student;
    Node *subject_list;
}Student;

Student *form_student_list()
{
    Student *newstudent;
    Student *head=NULL;
    Student *current=head;
    int res, choice;
    res=choice=1;
    while (choice)
    {
        res=1;
        newstudent=(Student*)malloc(sizeof(Student));
        printf("Enter the index of a student as NNNN/YYYY, where NNNN is the number of the student's index, and YYYY is a year of enrollment (for example 0123/2021) ");
        scanf("%s",&newstudent->index);
        newstudent->next_student=NULL;
        newstudent->subject_list=NULL;
        if(head==NULL)
        {
            head=newstudent;
        }
        else
        { current=head;

            while(current!=NULL)
            {
                if (strcmp(current->index, newstudent->index)==0)
                {
                    res=0;
                    break;
                }
                current=current->next_student;

            }
            if (res==1)
            {
                newstudent->next_student=head;
                head=newstudent;
            }


        }
        if (res==0)
            printf("This student is already in the system. Enter 1 to add a new student or 0 to go back on the menu: ");
        else
            printf("Enter 1 to add a new student or 0 to go back on the menu: ");
        scanf("%d",&choice);
    }
    return head;
}


void form_subj_list(Student *student)
{
    Node *previous;
    Node *head=student->subject_list;
    Node *newnode;
    Node *current=NULL;
    int choice =1;
    int res=0;
    while(choice)
    {
    current=head;
    newnode=(Node*)malloc(sizeof(Node));
    printf("Enter the code of the course that you want to add: ");
    scanf("%s", &newnode->subject);

    while(1)
    {
        printf("Enter the grade that the student has got for this course ");
        scanf("%d",&newnode->grade);
        if (6<=(newnode->grade) && (newnode->grade)<=10 )
            break;
        else
            printf("The grade of a passed course must be from 6 to 10.\n");
    }

    newnode->next=NULL;
    newnode->prev=NULL;
    if (head==NULL)
    {
        head=newnode;
    }
    else
    {
        while(current!=NULL)
        {
            previous=current;
            if (strcmp(current->subject,newnode->subject)<0)
                current=current->next;
            else if (strcmp(current->subject,newnode->subject)==0)
            {
                printf("This course already exists.\n");
                res=2;// predmet vec postoji u listi
                break;
            }
            else
            {
                if (current!=head)
                {
                current->prev->next=newnode;
                newnode->prev=current->prev;
                newnode->next=current;
                current->prev=newnode;
                res=1;}
                else
                {

                    head=newnode;
                    newnode->next=current;
                    current->prev=newnode;
                    res=1;
                }
                break;

            }

        }

        if (previous->next==NULL && res==0)
        {

            previous->next=newnode;
            newnode->prev=previous;
        }


    }
    if (res!=2)
    {
       printf("Enter 1 to add a new course or 0 to go back on the menu: ");
       scanf("%d",&choice);
    }

    }
    student->subject_list=head;
}
Student *add_index(Student *head)
{
    char indeks[15];
    while(1)
    {
        printf("Enter the index of a student: ");
        scanf("%s", &indeks);
        Student *current=head;
        while(current!=NULL)
       {
           if (strcmp(current->index,indeks)==0)
            {
                return current;
            }
            current=current->next_student;

       }
       printf("This student is not in the system.\n");

}}


void intersection (Student *head)
{
    printf("Student 1- ");
    Student *student1=add_index(head);
    printf("Student 2- ");
    Student *student2=add_index(head);
    Student *current=head;

    Node *list1=student1->subject_list; //pokazivac list1 i lista2 pokazuju na liste predmeta tih studenata.
    Node *list2=student2->subject_list;

    while (list1!=NULL && list2!=NULL)
    {
        if (strcmp(list1->subject,list2->subject)<0)
            list1=list1->next;
        else if (strcmp(list1->subject,list2->subject)>0)
            list2=list2->next;
        else
        {
            printf("%s\n",list1->subject);
            list1=list1->next;
            list2=list2->next;
        }
    }
}
void print_course (Node* head){
    for (Node *current=head; current !=NULL; current = current->next){
        printf("%s\n",current->subject);
    }
}
void print_student(Student *head)
{
    for (Student *current=head; current !=NULL; current = current->next_student){
        printf("%s\n",current->index);
    }
}
void add_course(Student *head)
{
    Student *current=head;
    char indeks[15];
    Student *ispravan;
    ispravan=add_index(head);
    form_subj_list(ispravan);
}

void list_of_courses(Student *head)
{
    int ocena;
    Node *pocetak;
    int res=0;
    Student *ispravan;
    ispravan=add_index(head);
    printf("Enter the grade: ");
    scanf("%d",&ocena);
    pocetak=ispravan->subject_list;
    printf("Passed courses with grade %d are:\n",ocena);
    while(pocetak!=NULL)
    {
        if (pocetak->grade==ocena)
            {printf("%s\n",pocetak->subject); res=1;}
        pocetak=pocetak->next;
    }
    if (res==0)
        printf("There are no passed courses with this grade.\n");

}

void delete_one_course(Student *head)
{
    char sifra[15];
    Node *predmeti,*pocetni;
    int res=0;
    Student *ispravan;
    ispravan=add_index(head);
    printf("Enter the code of the course that you want to cancel: ");
    scanf("%s", &sifra);
    predmeti=pocetni=ispravan->subject_list;
    while(predmeti!=NULL)
    {
        if (strcmp(predmeti->subject,sifra)==0)
        {
            res=1;
            if (predmeti->next==NULL)
            {
                predmeti->prev->next=NULL;

            }
            else if (predmeti==pocetni)
            {
                pocetni=predmeti->next;
                predmeti->next->prev=NULL;
            }
            else
            {
            predmeti->prev->next=predmeti->next;
            predmeti->next->prev=predmeti->prev;}
        }
        predmeti=predmeti->next;

    }
    if (res==0)
        printf("Studetn did not pass this course.\n");
}
void list_of_passed(Student *head,int a) //a=1 za broj, a=0 za prikaz svih
{
    int br=0;
    Student *ispravan;
    ispravan=add_index(head);
    Node *lista=ispravan->subject_list;
    Node *temp=lista;
    for(lista;lista!=NULL;lista=lista->next)
        br++;
    if (a==1)
        printf("The number of passed courses is: %d\n",br);
    else
        print_course(temp);

}
void print_students(Student *head)
{


}

int main()
{
    int opcija;
    Student *head=NULL;
    Student *student=NULL;
    Student *current;
    char indeks[10];
    printf("       School of Electrical Engineering- information system       \n\n\n");
    printf("1. Adding new student.\n"
           "2. Adding a course that the student has passed.\n"
           "3. The list of courses with a specific grade.\n"
           "4. Canceling (deleting) the grade from the passed course for a certain student.\n"
           "5. Canceling (deleting) all passed courses for a certain student.\n"
           "6. The number of passed courses of a particular student.\n"
           "7. The list of all passed courses of a particular student.\n"
           "8. List of same subjects passed by two students.\n"
           "9. The list of all students in the system.\n"
           "10. EXIT.\n\n\n");
    printf("Enter the menu option you need: ");
    scanf("%d",&opcija);
    while(opcija!=10)
    {
        switch(opcija)
        {
            case 1: head=form_student_list(); break;
            case 2: add_course(head); break;
            case 3: list_of_courses(head); break;
            case 4: delete_one_course(head); break;
            case 5: break;
            case 6: list_of_passed(head,1); break;
            case 7: list_of_passed(head,0); break;
            case 8: intersection(head); break;
            case 9: print_student(head); break;
        }
        printf("Enter the next option from the menu: ");
        scanf("%d",&opcija);
    }
    printf("Goodbye.");
    return 0;

}
