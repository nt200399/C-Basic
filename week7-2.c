#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h> // __fpurge(stdin);
#include <string.h>

int tongsdt = 0;

typedef struct
{
  char name[20];
  char dungluong[8];
  char kichco[15];
  char giatien[15];
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

void inputDataDat()//int dieuKhien)
{
  tongsdt = 0;
  FILE *fin;
  char filename[] = "phoneDB.dat";
  if ((fin = fopen(filename, "rb")) == NULL)
  {
    printf("Khong the mo %s\n", filename);
    exit(0);
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
      chenVaoCuoi(*DB);
    }

  free(DB);
  fclose(fin);
}

void inputDataTxt()
{
  tongsdt = 0;
  FILE *fin;
  char filename[] = "phoneDB.txt";
  if ((fin = fopen(filename, "r")) == NULL)
    {
      printf("Khong the mo %s\n", filename);
      exit(0);
    }
  phone *DB = (phone*) malloc(sizeof(phone));
  while(1)
    {
      fscanf(fin, "%s %s %s %s",
	     DB->name, DB->dungluong, DB->kichco, DB->giatien);
      if (feof(fin))
	break;
      chenVaoDau(*DB);
      tongsdt++;
    }

  free(DB);
  fclose(fin);
  
}

void printList()
{

  printf("%-4s %-15s %-15s %-15s %s\n", "STT", "TEN SP", "DUNG LUONG", "KICH CO", "GIA TIEN");
  int i = 0;  
  for (node *p = head; p != NULL; p = p->next)
    {
      i++;
      printf("%-4d %-15s %-15s %-15s %s\n",
	     i, p->data.name, p->data.dungluong,
	     p->data.kichco, p->data.giatien);
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

void nhapData()
{
  int dieukhien;
  printf("\nNhap vi tri chen:\n"
	 "1. Chen vao dau\n"
	 "2. Chen vao cuoi\n"
	 "3. Chen vao ben trong vi tri bat ki\n"
	 "-> Chon: ");
  scanf("%d", &dieukhien);
  
  phone *DB = (phone*) malloc(sizeof(phone));
  __fpurge(stdin);
  printf("\n-> Nhap ten dien thoai: ");
  gets(DB->name);
  printf("-> Nhap dung luong: ");
  gets(DB->dungluong);
  printf("-> Nhap kich co: ");
  gets(DB->kichco);
  printf("-> Nhap gia tien: ");
  gets(DB->giatien);

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

void findByModel()
{
  printf("Nhap Model tim kiem: ");
  char model[20];
  __fpurge(stdin);
  gets(model);

  int check = 0;
  for(node *p = head; p != NULL; p = p->next)
    {
      if (strcmp(model, p->data.name) == 0)
	{
	  check = 1;
	  printf("%-15s %-15s %-15s %s\n",
	       p->data.name, p->data.dungluong,
	       p->data.kichco, p->data.giatien);
	}
    }
  if (check == 0)
    printf("Khong tim thay!\n");
}

void xuatDuLieu()
{
  FILE *fput;
  char filename[] = "phoneDBnew.dat";
  if ((fput = fopen(filename, "wb")) == NULL)
    {
      printf("Khong the mo %s\n", filename);
      exit(0);
    }

  for (node *p = head; p != NULL; p = p->next)
    {
      fwrite(p, sizeof(phone), 1, fput);
    }
  printf("THANH CONG!\n");
  fclose(fput);
}


int main()
{
int dieuKhien;

  do
    {
      printf("\n------------------------\n"
	     "1. Doc tu file Dat\n"
	     "2. Doc tu fie Txt\n"
	     "3. Hien thi danh sach\n"
	     "4. Tim kiem bang Model\n"
	     "5. Nhap du lieu\n"
	     "7. Xuat du lieu ra file Dat moi\n"
	     "0. Thoat\n"
	     "-> Chon: ");
      scanf("%d", &dieuKhien);
 
      switch (dieuKhien)
	{
	case 1:
	  deleteNode();
	  inputDataDat();
	  printf("THANH CONG!\n");
	  break;
	case 2:
	  deleteNode();
	  inputDataTxt();
	  printf("THANH CONG!\n");
	  break;
	case 3:
	  printList();
	  break;
	case 4:
	  findByModel();
	  break;
	case 5:
	  nhapData();
	  break;
	case 7:
	  xuatDuLieu();
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

  return 0;
}
