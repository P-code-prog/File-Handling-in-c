/* File Handling Program to get, add, displayLinklist, free employee details from the .txt file*/ 
/* format of data stored into the file */
/* employeeName employeeID employeeCity employeePin */
/* employeeName should be under square bracket.
   employeeID should contain a alphabet, a number and '_'.
   employeeCity:- Pune
   employeePin- employeePin should be a 6 digit number  
   example:- [Snehal Joshi] abc_12 pune 123445 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>



/*defining the structure*/
typedef struct employee
{
  char employeeName[50];
  char employeeID[8];
  char employeeCity[10];
  char employeePin[10];
  struct employee *next;
} SLL;


/*declaring all function prototype*/
SLL *getDetailsFromFile (SLL * start, FILE * fp);
SLL *addEmployeeDetailsToFile (SLL * start, FILE *fp);
void displayLinklist (SLL * start);
void freeLinklist(SLL *start);

/*main function*/
int main()
{
	SLL *start = NULL;
	FILE *fp;
	int choice=0;
	bool bo = true;

	fp = fopen ("Employee.txt", "r+");
	if(fp == NULL)
	  fp=fopen("Employee.txt","w+");

	do
	  {
	    printf ("\n***********");
	    printf ("\n FILE HANDLING");
	    printf ("\n****************");
	    printf ("\n1.Get employee details from the file ");
	    printf ("\n2. Add employee details to the file");
	    printf ("\n3. displayLinklist employee details");
            printf ("\n4. free linklist and close the file");
	     printf("\n6. exit");
	    printf ("\n***********");
	    printf ("\n Enter the choice");
	    scanf ("%d", &choice);


	    switch (choice)
	      {
	      case 1:
		start = getDetailsFromFile (start, fp);                         /* reading data from file and storing it in linklist*/
		break;
	      case 2:
		start = addEmployeeDetailsToFile (start,fp);                          /*adding more data into the linklist*/
		break;
	      case 3:
		displayLinklist (start);                                       /* storing data in the file and displayLinklisting the data */
		break;
	      case 4:freeLinklist(start);
		         fclose (fp);
		         bo = false;
	      }
	  }
	while (bo == true);
	return 0;
}


 /* reading data from file and storing it in linklist*/

SLL* getDetailsFromFile(SLL*start,FILE *fp)
{
    long int n;
	if (fp == NULL)
	  printf ("\n NO DATA FOUND");
	else
	  {
	    SLL *nw = NULL, *last = NULL, *nws = NULL;
	    nw = (SLL *) malloc (sizeof (SLL));
	    nw->next = NULL;
        while(fscanf(fp,"%[^' '] %[^' '] %[^' '] %[^'\n']\n",nw->employeeName,nw->employeeID,nw->employeeCity,nw->employeePin)!=EOF)
	      {
	                printf("%s %s %s %s\n",nw->employeeName,nw->employeeID,nw->employeeCity,nw->employeePin);
	               
			nws = (SLL *) malloc (sizeof (SLL));
			nw->next = NULL;
			strcpy(nws->employeeName,nw->employeeName);
			strcpy (nws->employeeID, nw->employeeID);
			strcpy (nws->employeeCity, nw->employeeCity);
			strcpy (nws->employeePin, nw->employeePin);

			nws->next = NULL;
			if (start == NULL)
			  start = nws;
			else
			  last->next = nws;
			last = nws;
			last->next = NULL;

	      }
  }

return start;

}


/*adding more data into the File*/

SLL* addEmployeeDetailsToFile(SLL*start,FILE *fp)
{

SLL *nw, *check = start;
int flag = 0,found=0,employeeNameSize=0;
char cus_employeeID[8];
SLL *last;
char ans;

 do
 {
	check = start;
	flag = 0;
	printf ("\n check if the data you want to enter is already present or not");
	printf ("\nEnter the employee_employeeID ");
	scanf ("%s",cus_employeeID);
	for (; check != NULL; check = check->next)
	  { last=check;
	    if (strcmp(check->employeeID,cus_employeeID)==0)
	      {
		printf ("\n sorry this student data is already present:\n");
		flag = 1;
		break;
	      }
	  }
	  for(int i=0;cus_employeeID[i]!='\0';i++)
      {
          if((cus_employeeID[i]>=65 && cus_employeeID[i]<=90) || (cus_employeeID[i]>=97 && cus_employeeID[i]<=122))
           found++;
           if(cus_employeeID[i]>=48 && cus_employeeID[i]<=57)
           found++;
          if(cus_employeeID[i]=='_')
           found++;
      }
      printf("%d ",found);
       if(found<3)
      {
          printf("Invalid employee id\n");
          break;
      }

	if (flag == 1)
	  break;
	nw = (SLL *) malloc (sizeof (SLL));
	strcpy(nw->employeeID,cus_employeeID);
	printf ("\n enter the Name of the employee ");
	getchar();
	 scanf ("%[^\n]s", nw->employeeName);
	printf("\n Enter the City of the Employee");
	scanf("%s",nw->employeeCity);
	printf ("\n Enter the Pin of employee");
	scanf ("%s", nw->employeePin);

	nw->next = NULL;

	if (start == NULL)
	  start = nw;
	else
	  last->next = nw;
	last = nw;
        last->next=NULL;

	printf ("\n ***more records****y/n");
	getchar ();
	scanf ("%c", &ans);

 }while (ans != 'n');

          rewind (fp);
	  SLL *p=NULL;
	  p = start;
	  for (; p != NULL; p = p->next)
	    {

		       fprintf(fp,"%s %s %s %s\n",p->employeeName,p->employeeID,p->employeeCity,p->employeePin);
		       printf("%-16s %-16s %-16s %-16s\n",p->employeeName,p->employeeID,p->employeeCity,p->employeePin);
            }



return start;

}




/* displaying Linklist Employee details */

void
displayLinklist (SLL * start)
{
	  SLL *p=NULL;
	  p = start;
	  for (; p != NULL; p = p->next)
	    {
		       printf("%-16s %-16s %-16s %-16s\n",p->employeeName,p->employeeID,p->employeeCity,p->employeePin);

            }

}


void 
freeLinklist(SLL *start)
{

    SLL *p;
    p=start;
    for(;p!=NULL;p=start)
    {
        start=start->next;
        free(start);
    }
    start=NULL;
}


