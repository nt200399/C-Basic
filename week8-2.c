#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  char name[20];
  char tel[11];
  char mail[50];
} PHONEDB;

typedef struct node 
{
    PHONEDB data;
    struct node *next;
} node;

node *head = NULL;
node *tail = NULL;

node *makeNode(PHONEDB data)
{
    node *p = (node *) malloc(sizeof(node));
    if (p == NULL)
    {
        printf("Can't creat node!\n");
        return NULL;
    }
    p->data = data;
    p->next = NULL;
    return p;
}

void insertAfterNode(PHONEDB data)
{
    node *p = makeNode(data);
    if (head == NULL)
        head = tail = p;
    else
    {
        tail->next = p;
        tail = p;
    }
}

void inputDataFromDat()
{
    FILE *fin;
    char filename[] = "phone.dat";
    if ((fin = fopen(filename, "rb")) == NULL)
    {
        printf("Can't open %s\n", filename);
        exit(0);
    }

    PHONEDB *data = (PHONEDB*) malloc(sizeof(PHONEDB));

    while(1)
    {
        fread(data, sizeof(PHONEDB), 1, fin);
        if (feof(fin))
            break;
        insertAfterNode(*data);
    }

    free(data);
    fclose(fin);
}

void printList()
{
    printf("%-4s %-15s %-13s %s", "STT", "Ho Ten",
	   "SDT", "Mail\n");

    int i = 0;
    for (node *p = head; p != NULL; p = p->next)
    {
        i++;
        printf("%-4d %-15s %-13s %s\n", i, p->data.name, p->data.tel, p->data.mail);
    }
}

int length(node *p)
{
  if (p == NULL)
    return 0;
  else
    return length(p->next) + 1;
}

void saveDat(FILE *f1, FILE *f2, int vitri)
{
  int i = 0;
  for (node *p = head; p != NULL; p = p->next)
    {
      if (i <= vitri)
	fwrite(p, sizeof(PHONEDB), 1, f1);
      else if (i > vitri)
	fwrite(p, sizeof(PHONEDB), 1, f2);
      i++;
    }
  
}

void printDat(FILE *f)
{ 
  fseek(f, 0, SEEK_END);
  int skt = ftell(f) / sizeof(PHONEDB);
  rewind(f);
  
  PHONEDB *dt = (PHONEDB*) malloc(sizeof(PHONEDB)*skt);
  fread(dt, sizeof(PHONEDB), skt, f);
  for (int j = 0; j < skt; j++)
    {
      printf("%-4d %-15s %-15s %s\n", j+1, dt[j].name,
	     dt[j].tel, dt[j].mail);
    }
}

void saveAndPrint(int vitri, int dieukien)
{
  FILE *f1, *f2;
  char filename1[] = "phone1.dat";
  char filename2[] = "phone2.dat";

  if ((f1 = fopen(filename1, "w+b")) == NULL)
    {
      printf("Khong the mo %s\n", filename1);
      return;
    }

  if ((f2 = fopen(filename2, "w+b")) == NULL)
    {
      printf("Khong the mo %s\n", filename2);
      return;
    }
  
  saveDat(f1, f2, vitri);

  if (dieukien == 1)
    printDat(f1);
  else
    printDat(f2);

  fclose(f1);
  fclose(f2);
}

void slipFile()
{
  int len = length(head);
  printf("Nhap vi tri tach trong khoang 0 -> %d\n"
	 "---> Nhap: ", len - 1);
  int vitri;
  scanf("%d", &vitri);
  while (vitri < 0 || vitri >= len)
    {
      printf("Nhap lai gia tri!\n"
	     "---> Nhap: ");
      scanf("%d", &vitri);
    }

  int dieukien;
  do
    {
      printf("\n1. Luu va In file 1\n"
	     "2. Luu va In file 2\n"
	     "0. Thoat!\n"
	     "---> Chon: ");
      scanf("%d", &dieukien);

      switch(dieukien)
	{
	case 1:
	  saveAndPrint(vitri, dieukien);
	  break;
	case 2:
	  saveAndPrint(vitri, dieukien);
	  break;
	case 0:
	  break;
	default:
	  printf("Nhap lai!\n");
	}
    } while (dieukien != 0);
}

void removeNode()
{
  node *p = NULL;
  if (head != NULL)
    {
      p = head;
      head = head->next;
      free(p);
    }
}

int main()
{
  int dieukien;

  do
    {
      printf("\n-----------------------\n"
  	     "1. Nhap du lieu tu file Dat\n"
  	     "2. Hien thi du lieu\n"
  	     "3. Tach du lieu\n"
  	     "0. Thoat!\n"
  	     "---> Chon: ");
      scanf("%d", &dieukien);
      switch(dieukien)
  	{
  	case 1:
  	  inputDataFromDat();
  	  break;
  	case 2:
  	  printList();
  	  break;
  	case 3:
	  slipFile();
	  break;
	case 0:
	  break;
  	default:
  	  printf("Nhap lai!\n");
  	}
	
    } while (dieukien != 0);

  removeNode();
  return 0;
}
