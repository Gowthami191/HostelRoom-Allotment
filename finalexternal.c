#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct hostel
{
  int rollno;
  char name[30];
  char location[30];
  char gender[10];
  int roomno;
} hostel;
hostel h;
hostel h1;
int getRoomNo();
int lower = 100, upper = 500;
void create()
{
  FILE *fp = fopen("hostel.txt", "a+");
  printf("Enter roll number:");
  scanf("%d", &h.rollno);
  printf("Enter Name:");
  scanf("%s", h.name);
  printf("Enter location:");
  scanf("%s", h.location);
  printf("Enter gender:");
  scanf("%s", h.gender);
  h.roomno = getRoomNo(((rand() % (upper - lower + 1)) + lower));
  if (h.roomno != 0)
    fwrite(&h, sizeof(hostel), 1, fp);
  system("clear");
  printf("Room Allocated Sucessfully!!!\n");
  fclose(fp);
}
int getRoomNo(int roomno)
{
  int allocated = 0;
  FILE *fp = fopen("hostel.txt", "r");
  hostel h1;
  while (fread(&h1, sizeof(hostel), 1, fp))
  {
    if (h1.roomno == roomno)
    {
      allocated = 1;
    }
  }
  if (allocated == 0)
    return roomno;
  else
    return getRoomNo(((rand() % (upper - lower + 1)) + lower));
  fclose(fp);
}
void display()
{
  system("clear");
  FILE *fp = fopen("hostel.txt", "r");
  int k = 0;
  printf("\n----------------------------------------------------------------------\n");
  printf("%-10s%-20s%-15s%-10s%-5s", "RollNo", "Name", "Location", "Gender", "RoomNo");
  printf("\n----------------------------------------------------------------------\n");
  while (fread(&h1, sizeof(hostel), 1, fp) > 0)
  {

    printf("%-10d%-20s%-15s%-10s%-5d\n", h1.rollno, h1.name, h1.location, h1.gender, h1.roomno);
    k = 1;
  }
  if (k == 0)
    printf("\t\t\t*No Records*");
  fclose(fp);
}
void del()
{
  int r_no;
  printf("Enter the roll number to delete:");
  scanf("%d", &r_no);
  FILE *fp1 = fopen("hostel.txt", "r+");
  FILE *fp2 = fopen("txt1.txt", "a+");
  while (fread(&h1, sizeof(hostel), 1, fp1))
  {
    if (h1.rollno != r_no)
    {
      fwrite(&h1, sizeof(hostel), 1, fp2);
    }
  }
  fclose(fp1);
  fclose(fp2);
  remove("hostel.txt");
  rename("txt1.txt", "hostel.txt");
  system("clear");
  printf("Record deleted sucessfully!!!");
}
void search()
{
  int roll,fix=0;
  printf("Enter the roll number:");
  scanf("%d",&roll);
  FILE *fp=fopen("hostel.txt","r");
  while(fread(&h1,sizeof(hostel),1,fp)){
    if(h1.rollno==roll)
    {
      printf("\t\t\tRoom Found\n");
  printf("\n----------------------------------------------------------------------\n");
  printf("%-10s%-20s%-15s%-10s%-5s", "RollNo", "Name", "Location", "Gender", "RoomNo");
  printf("\n----------------------------------------------------------------------\n");
  printf("%-10d%-20s%-15s%-10s%-5d\n", h1.rollno, h1.name, h1.location, h1.gender, h1.roomno);
    fix=1;
    }
  }
  fclose(fp);
  if(fix==0)
   printf("Room not found!!!");
}
int main()
{
  printf("\t\t\tHostel Room Allocation");
  system("clear");
  int ch;
  start:
  do
  {
    printf("\n1-ALLOCATE NEW ROOM");
    printf("\n2-DISPLAY");
    printf("\n3-SEARCH");
    printf("\n4-DELETE");
    printf("\n5-EXIT\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
      create();
      break;
    case 2:
      display();
      break;
    case 4:
      del();
      break;
    case 5:
      system("clear");
      printf("\n\t\t\tProgram Terminated!!!\n");
      break;
      case 3:
      system("clear");
      search();
      break;
    default:
     printf("Enter among the given numbers");
     goto start;
    }
  } while (ch!=5);
  return 0;
}