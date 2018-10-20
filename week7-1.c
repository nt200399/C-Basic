#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 80

typedef struct
{
  char name[20];
  char tel[11];
  char mail[50];
} phone;

typedef struct node
{
  phone data;
  struct node *next;
} node;

node *head = NULL;
node *current = NULL;

node *makeNode(phone DB)
{

  node *p = (node *) malloc(sizeof(node));
  if (p == NULL)
    {
      printf("Can't creat p\n");
      return NULL;
    }
  p->data = DB;
  p->next = NULL;
  return p;
}

void chenVaoDau(phone DB)
{
  node *p = makeNode(DB);
  if (head == NULL)
    head = current = p;
  else
    {
      p->next = head;
      head = p;
    }
}

void chenVaoCuoi(phone DB)
{
  node *p = makeNode(DB);
  if (head == NULL)
    head = current = p;
  else
    {
      current->next = p;
      current = p;
    }
}

void inputData(int kieuhien)
{
  FILE *fin;
  char filename[] = "phone.dat";
  if ((fin = fopen(filename, "rb")) == NULL)
  {
    printf("Khong the mo %s\n", filename);
    return;
  }

  phone *DB;
  DB = (phone*) malloc(sizeof(phone)*22);

  while(1)
    {
      fread(DB, sizeof(phone), 1, fin);
      if (feof(fin))
  	break;
      if (kieuhien == 1)
	chenVaoDau(*DB);
      else if (kieuhien == 2)
	chenVaoCuoi(*DB);
      // printf("%-15s %-15s %s\n", DB->name, DB->tel, DB->mail);
    }

  free(DB);
  fclose(fin);
}

void printList()
{

  printf("%-4s %-15s %-15s %s\n", "STT", "HO TEN", "SDT", "MAIL");
  int i = 0;  
  for (node *p = head; p != NULL; p = p->next)
    {
      i++;
      printf("%-4d %-15s %-15s %s\n",
	     i, p->data.name, p->data.tel, p->data.mail);
    }
}

void deleteNode()
{
  node *p = NULL;
  while(head != NULL)
    {
      head = head->next;
      free(p);
    }
}

int main()
{
  int kieuhien;

  do
    {
      printf("------------------------\n"
	     "Chon kieu doc du lieu:\n"
	     "1. Doc tu duoi len\n"
	     "2. Doc tu tren xuong\n"
	     "0. Thoat\n"
	     "Chon: ");
      scanf("%d", &kieuhien);
      switch (kieuhien)
	{
	case 1:
	  inputData(1);
	  printList();
	  deleteNode();
	  break;
	case 2:
	  inputData(2);
	  printList();
	  deleteNode();
	  break;
	case 0:
	  printf("-------- THOAT ---------\n");
	  break;
	default:
	  printf("Nhap lai gia tri");
	}
    } while (kieuhien != 0);

  
  return 0;
}
