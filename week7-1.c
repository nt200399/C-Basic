#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h> // __fpurge(stdin);

#define MAX_LEN 80

int tongsdt = 0;

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

void inputData()//int dieuKhien)
{
  FILE *fin;
  char filename[] = "phone.dat";
  if ((fin = fopen(filename, "rb")) == NULL)
  {
    printf("Khong the mo %s\n", filename);
    return;
  }

  phone *DB;
  DB = (phone*) malloc(sizeof(phone));

  while(1)
    {
      fread(DB, sizeof(phone), 1, fin);
      if (feof(fin))
  	break;

      // Dem so dt;
      tongsdt++;
      /* if (dieuKhien == 1 || dieuKhien == 3) */
      /* 	chenVaoDau(*DB); */
      /* else if (dieuKhien == 2 || dieuKhien == 4) */
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
      p = head;
      head = head->next;
      free(p);
    }
}

void chenTrong(phone DB)
{
  printf("Nhap vi tri chen: ");
  int vitri;
  scanf("%d", &vitri);
  while(vitri < 1 || vitri >= tongsdt)
    {
      printf("Nhap lai vi tri trong giua!\n");
      scanf("%d", &vitri);
    }

  int i = 0;
  for (node *p = head; p != NULL; p = p->next)
    {
      i++;
      if (vitri == i)
	{
	  node *new = makeNode(DB);
	  new->next = p->next;
	  p->next = new;
	  tongsdt++;
	}
    }
    
}

void nhapData(int dieukhien)
{
  phone *DB = (phone*) malloc(sizeof(phone));
  __fpurge(stdin);
  printf("\n-> Nhap ho ten: ");
  gets(DB->name);
  printf("-> Nhap so dien thoai: ");
  gets(DB->tel);
  printf("-> Nhap mail: ");
  gets(DB->mail);

  if (dieukhien == 1)
    {
      chenVaoDau(*DB);
      tongsdt++;
    }
  else if (dieukhien == 2)
    {
      chenVaoCuoi(*DB);
      tongsdt++;
    }
  else if (dieukhien == 3)
    chenTrong(*DB);

}

void xoaNodeDau()
{
  node *p = head;
  if (head == NULL)
    return;
  head = head->next;
  free(p);
}

void xoaNodeCuoi()
{
  for (node *p = head; p != NULL; p = p->next)
    {
      if (head == current)
	xoaNodeDau();
      if (p->next == current)
	{
	  free(current);
	  p->next = NULL;
	  current = p;
	}
    }
}

void xoaNodeViTri()
{
  int vitri;
  do
    {
      printf("Nhap vi tri can xoa: ");
      scanf("%d", &vitri);
      if (vitri < 0 || vitri > tongsdt)
	printf("Nhap lai vi tri!\n");
    } while (vitri < 0 || vitri > tongsdt);

  int i = 0;
  node *luutru = (node *) malloc(sizeof(node)); 
  for(node *p = head; p != NULL; p = p->next)
    {
      i++;
      if (vitri == 1)
	{
	  xoaNodeDau();
	  tongsdt--;
	  break;
	}
      if (vitri == tongsdt)
	{
	  xoaNodeCuoi();
	  tongsdt--;
	}
      if (vitri == i)
      	{
      	  luutru->next = p->next;
      	  free(p);
	  tongsdt--;
      	  break;
      	}
      luutru = p;
    }
  
}



int main()
{
  int dieuKhien;

  inputData();
  do
    {
      printf("\n------------------------\n"
	     "Chon kieu doc du lieu:\n"
	     /* "1. Doc tu duoi len\n" */
	     /* "2. Doc tu tren xuong\n" */
	     "1. Chen ben tren\n"
	     "2. Chen ben duoi\n"
	     "3. Chen vao ben trong\n"
	     "4. Xoa node bat ki\n"
	     "5. In ra man hinh\n"
	     "6. Reset Node\n"
	     "0. Thoat\n"
	     "-> Chon: ");
      scanf("%d", &dieuKhien);

 
      switch (dieuKhien)
	{
	/* case 1: */
	/*   inputData(dieuKhien); */
	/*   printList(); */
	/*   deleteNode(); */
	/*   break; */
	/* case 2: */
	/*   inputData(dieuKhien); */
	/*   printList(); */
	/*   deleteNode(); */
	/*   break; */
	case 1:
	  nhapData(dieuKhien);
	  break;
	case 2:
	  nhapData(dieuKhien);
	  break;
	case 3:
	  nhapData(dieuKhien);
	  break;
	case 4:
	  xoaNodeViTri();
	  break;
	case 5:
	  printList();
	  break;
	case 6:
	  deleteNode();
	  tongsdt = 0;
	  inputData();
	  break;
	case 0:
	  printf("\n-------- THOAT ---------\n");
	  break;
	default:
	  printf("Nhap lai gia tri");
	}

  
    } while (dieuKhien != 0);

  deleteNode();
  return 0;
}
