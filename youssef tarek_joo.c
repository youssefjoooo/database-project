#include <stdio.h>
#include <stdlib.h>
#define max 10
#define size 5
typedef int u8;
typedef struct simple_DB node;
typedef enum
{
    false,
    true
}bool;
u8 count =0;
struct simple_DB
{
    u8 student_ID;
    u8 student_year;
    u8 course_ID[size];
    u8 course_grade[size];
    node*next;
};
u8 Position_Node(node*head,u8 id)
{
   u8 position=1;
   while(head)
   {
       if(head->student_ID==id)
        return position;
       else
       {
           position++;
       }
       head=head->next;
   }
   return -1;
}
bool SDB_IsFull(void)
{
  if(count==max)
    return true;
  else
    return false;
}
u8 SDB_GetUsedSize()
{
    return count;
}
bool SDB_AddEntry(u8 id,u8 year,u8*subjects,u8*grades,node**head)
{
    if (SDB_IsFull())
    {
        printf("The data base is already full\n\n");
        return false;
    }
    else
    {
        node*st=(node*)malloc(sizeof(node));
        subjects=st->course_ID;
        grades=st->course_grade;
        printf("Enter student number %d",count+1);
        printf(" id \n");
        jump:
        scanf("%d",&id);
        st->student_ID=id;
        u8 pos=Position_Node(*head,st->student_ID);
        if(pos==-1)
        {
        count++;
        printf("Enter the year \n");
        scanf("%d",&year);
        st->student_year=year;
        for(int i=1;i<4;i++)
        {
            printf("Enter the course %d",i);
            printf(" id\n");
            scanf("%d",&subjects[i-1]);
            subjects++;
        }
        subjects=st->course_ID;
        for(int i=1;i<4;i++)
        {
            printf("Enter the course %d",i);
            printf(" grade\n");
            label:
            scanf("%d",&grades[i-1]);
                if(grades[i-1]>100||grades[i-1]<0)
                {
                    printf("Warning you entered a wrong grade\n");
                    printf("Please enter another grade from 0 to 100\n");
                    goto label;
                }
            grades++;
        }
        grades=st->course_grade;
        if(*head==NULL)
        {
            *head=st;
            (*head)->next=NULL;
        }
        else
        {
            node*ptr=*head;
            while(ptr->next)
            {
                ptr=ptr->next;
            }
            ptr->next=st;
            (st)->next=NULL;
        }
        return true;
        }
        else
        {
            printf("The id is already created\n");
            printf("Enter another id\n");
            goto jump;
        }
    }
}
void SDB_DeleteEntry(node**head,u8 id)
{
    if(count==0)
    {
        printf("The database is empty no items to delete\n\n");
        return;
    }
    u8 p;
    node*p1=*head;
    node*p2=*head;
    printf("Enter your id to delete\n");
    jump1:
    scanf("%d",&id);
    p=Position_Node(*head,id);
    if(p<0)
    {
        printf("You id not exist to deldete\n");
        printf("Please enter another id\n");
        goto jump1;
    }
    else
    {
        if(p==1)
        {
            node*ptr=*head;
            *head=(*head)->next;
            free(ptr);
            count--;
            printf("The entry is successfully deleted\n\n");
        }
       else
       {
            for(int i=0;i<p-2;i++)
            {
                p2=p2->next;
                p1=p1->next;
            }
            p1=p1->next;
            p2->next=p1->next;
            count--;
            printf("The entry is successfully deleted\n\n");
       }
    }
}
bool IsExist(node*head,u8 id)
{
    printf("Enter your id to check\n");
    scanf("%d",&id);
    while(head)
    {
        if(head->student_ID==id)
            return true;
        else
            head=head->next;
    }
          return false;
}
bool SDB_ReadEntry(u8 id,u8*year,u8*subject,u8*grade,node*head)
{
    printf("Enter your id to print\n");
    scanf("%d",&id);
    u8 p=Position_Node(head,id);
    if(p<0)
    {
        printf("The id not exist\n\n");
        return false;
    }
  else
    {
        for(int i=0;i<p-1;i++)
        head=head->next;
        *year=head->student_year;
        *subject=head->course_ID;
        *grade=head->course_grade;
    }
}
void SDB_GetList(node*head)
{
    if(count==0)
    {
        printf("The database is empty\n\n");
        return;
    }
    for(int i=0;i<count;i++)
    {
        printf("The student number %d",i+1);
        printf(" his id is = %d",head->student_ID);
        printf("\n");
        head=head->next;
    }
    printf("\n");
}
int main ()
{
    node*head=NULL;
    u8 st_id,year,grade[3],course_id[3],op,*subjects,*grades;
    jump5:
    printf("......................................\n");
    printf("1-Check if the data base is full\n");
    printf("2-Get the number of entries in database\n");
    printf("3-Add entry in database\n");
    printf("4-Delete entery with entering its id\n");
    printf("5-Print entry data\n");
    printf("6-Get list of id in the database\n");
    printf("7-Check if the id is exist or not\n");
    printf("8-Close the program\n");
    printf("......................................\n");
    printf("Select your operation from 1 to 8\n");
    jump6:
    scanf("%d",&op);
    if(op<1||op>8)
    {
        printf("Enter true operation\n");
        goto jump6;
    }
    switch(op)
    {
  case 1:
        {
           if(SDB_IsFull())
            printf("The database is full\n");
           else
            printf("The data base is not full\n\n");
            goto jump5;
        }
  case 2:
        {
           u8 n=SDB_GetUsedSize();
           printf("The number of entries is %d",n);
           printf("\n\n");
           goto jump5;
        }
  case 3:
        {
           if(SDB_AddEntry(st_id,year,subjects,grades,&head))
           {
               printf("The entry is added successfully\n\n");
           }
           goto jump5;
        }
  case 4:
        {
            SDB_DeleteEntry(&head,st_id);
            goto jump5;
        }
  case 5:
        {
            if(count==0)
            {
                printf("The database is empty\n\n");
                goto jump5;
            }
            if(SDB_ReadEntry(st_id,&year,&subjects,&grades,head))
            {
                printf("The year is %d",year);
                printf("\n");
            for(int i=1;i<4;i++)
              {
                printf("The course %d",i);
                printf(" id %d",subjects[i-1]);
                printf("\n");
                subjects++;
              }
            for(int i=1;i<4;i++)
              {
                printf("The course %d",i);
                printf(" grade %d",grades[i-1]);
                printf("\n");
                grades++;
              }
            }
                goto jump5;
        }
  case 6:
        {
                SDB_GetList(head);
                goto jump5;
        }
  case 7:
        {
                if(IsExist(head,st_id))
                {
                    printf("The id exists in the database\n\n");
                    goto jump5;
                }
                else
                {
                    printf("The id not exist in the database\n\n");
                    goto jump5;
                }
        }
  case 8:
        {
             printf("Thank you\n");
             return 0;
        }
    }
}
