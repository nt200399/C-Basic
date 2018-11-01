#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[20];
    char dungluong[8];
    char kichco[15];
    char giatien[15];
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

void insertAtHead(PHONEDB data)
{
  node *p = makeNode(data);
  if (head == NULL)
    head = tail = p;
  else
    {
      p->next = head;
      head = p;
    }
}

PHONEDB *nhapDuLieuTuBanPhim(PHONEDB *data)
{
  printf("Ten dien thoai: ");
  scanf("%s", data->name);
  printf("Dung luong: ");
  scanf("%s", data->dungluong);
  printf("Kich co man hinh: ");
  scanf("%s", data->kichco);
  printf("Gia tien: ");
  scanf("%s", data->giatien);
  return data;
}

void addNewPhone()
{
  int dieukien;
  do
    {    
      printf("******************\n"
	     "1. Them vao dau\n"
	     "2. Them vao cuoi\n"
	     "0. Thoat!\n"
	     "-> Chon: ");
      scanf("%d", &dieukien);

      if (dieukien == 0)
	return;   
      if (dieukien <= 0 || dieukien >= 3)
	printf("Nhap lai!\n");

    } while (dieukien <= 0 || dieukien >= 3);

  PHONEDB *data = (PHONEDB*) malloc(sizeof(PHONEDB));
  nhapDuLieuTuBanPhim(data);

  if (dieukien == 1)
    insertAtHead(*data);  
  else
    insertAfterNode(*data);

  free(data);
}

int length(node *p)
{
  if (p == NULL)
    return 0;
  else
    return length(p->next) + 1;
}

void insertPosition()
{
  if (length(head) <= 0)
    {
      printf("Danh sach trong!\n");
      return;
    }
  
  int dieukien;
  
  do
    {    
      printf("******************\n"
	     "Danh sach co do dai tu 0 -> %d !\n"
	     "-> Chon vi tri: ", length(head) - 1);
      scanf("%d", &dieukien);
      if (dieukien < 0 || dieukien > length(head) - 1)
	printf("Nhap lai!\n");

    } while (dieukien < 0 || dieukien > length(head) - 1);
  
  PHONEDB *data = (PHONEDB*) malloc(sizeof(PHONEDB));
  nhapDuLieuTuBanPhim(data);
  
  int i = 0;
  node *prev = NULL;
  for (node *p = head; p != NULL; p = p->next)
    {
      if (dieukien == 0)
	{
	  insertAtHead(*data);
	  break;
	}
      else if (dieukien == i)
	{
	  node *new = makeNode(*data);
	  prev->next = new;
	  new->next = p;
	  break;
	}
      i++; 
      prev = p;
    }

  free(data);
}

void inputDataFromDat()
{
    FILE *fin;
    char filename[] = "phoneDB.dat";
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
    printf("%-4s %-15s %-13s %-15s %s", "STT", "Model", "Dung Luong",
	   "Kich Co MH", "Gia Tien\n");

    int i = 0;
    for (node *p = head; p != NULL; p = p->next)
    {
        i++;
        printf("%-4d %-15s %-13s %-15s %s\n", i, p->data.name, p->data.dungluong,
	       p->data.kichco, p->data.giatien);
    }
}

void removeNode()
{
  node *p = NULL;
  while(head != NULL)
    {
      p = head;
      head = head->next;
      free(p);
    }
}

void removeNodeHead()
{
  if (head == NULL)
    return;
  node *p = head;
  head = head->next;
  free(p);
  printf("\n-----Thanh Cong-----\n");
}

void removeNodeTail()
{
  if (head == NULL)
    return;
  else if (head == tail)
    removeNodeHead();
  else
      for (node *p = head; p != NULL; p = p->next)
	  if (p->next == tail)
	    {
	      free(tail);
	      p->next = NULL;
	      tail = p;
	    }
  printf("\n-----Thanh Cong-----\n");
}

void removeNodePosition()
{
  if (length(head) <= 0)
    {
      printf("Danh sach trong!\n");
      return;
    }

  int dieukien;
  do
    {    
      printf("******************\n"
	     "Danh sach co do dai tu 0 -> %d !\n"
	     "-> Chon vi tri: ", length(head) - 1);
      scanf("%d", &dieukien);
      if (dieukien < 0 || dieukien > length(head) - 1)
	printf("Nhap lai!\n");

    } while (dieukien < 0 || dieukien > length(head) - 1);

  int i = 0;
  node *prev = NULL;
  for (node *p = head; p != NULL; p = p->next)
    {
      if (dieukien == 0)
	{
	  removeNodeHead();
	  return;
	}
      else if (dieukien == length(head) - 1)
	{
	  removeNodeTail();
	  return;
	}
      else if (dieukien == i)
	{
	  prev->next = p->next;
	  free(p);
	  return;
	}
      prev = p;
      i++;
    }
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
      printf("%-4d %-15s %-15s %-15s %s\n", j+1, dt[j].name,
	     dt[j].dungluong, dt[j].kichco, dt[j].giatien);
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

void findAndUpdate()
{
  if (length(head) <= 0)
    {
      printf("Danh sach trong!\n");
      return;
    }

  char fModel[20];
  printf("Nhap Model tim kiem: ");
  scanf("%s", fModel);

  int check = 0, i = 0, checksua = 0;
  for (node *p = head; p != NULL; p = p->next)
    {
      if (strcmp(p->data.name, fModel) == 0)
	{
	  i++;
	  check = 1;
	  checksua = 1;
	  printf("%-4d %-15s %-13s %-15s %s\n", i,
		 p->data.name, p->data.dungluong,
	       p->data.kichco, p->data.giatien);
	}
      if (checksua == 1)
	{
	  printf("\n Ban co muon chinh sua khong!\n"
		 "1 - Chinh sua; 0 - Bo qua\n"
		 "---> Chon: ");
	  int chinhsua;
	  checksua = 0;
	  scanf("%d", &chinhsua);
	  if (chinhsua == 0)  
	      continue;
	  
	  PHONEDB *data = (PHONEDB*) malloc(sizeof(PHONEDB));
	  nhapDuLieuTuBanPhim(data);
	  p->data = *data;
	  free(data);
	}
    }
  if (check == 0)
    printf("\nKhong tim thay!\n");
}

void daoNguocDS()
{
  node *p = NULL;
  node *newHead = NULL, *newTail = NULL;

  while(head != NULL)
    {
      p = head;
      head = head->next;

      if (newHead == NULL)
	{
	  p->next = NULL;
	  newHead = newTail = p;
	}
      else
	{
	  p->next = newHead;
	  newHead = p;
	}
    }

  head = newHead;
  tail = newTail;

}

void saveFileDat()
{
  FILE *f;
  char filename[] = "phoneDB.dat";
  if ((f = fopen(filename, "w +b ")) == NULL)
    {
      printf("Khong the mo %s\n", filename);
      return; 
    }


  for (node *p = head; p != NULL; p = p->next)
    {
      fwrite(p, sizeof(PHONEDB), 1, f);
    }
  
  
  fclose(f);
}

int main()
{
  
    int dieukien;
    do
    {
      printf("\n--------------------------\n"
	     "1. Nhap tu PhoneDB.dat\n"
	     "2. Hien thi\n"
	     "3. Them vao dau - cuoi\n"
	     "4. Them vao vi tri bat ki\n"
	     "5. Xoa vi tri bat ki\n"
	     "6. Xoa dau\n"
	     "7. Xoa cuoi\n"
	     "8. Tim kiem va Cap nhat\n"
	     "9. Tach va luu file\n"
	     "10. Dao nguoc danh sach\n"
	     "11. Luu danh sach\n"
	     "0. Thoat!\n"
	     "-> Chon: ");
      scanf("%d", &dieukien);

      switch(dieukien)
	{
	case 1:
	  removeNode();
	  inputDataFromDat();
	  printf("\n Nhap du lieu thanh cong!\n");
	  break;
	case 2:
	  printList();
	  break;
	case 3:
	  addNewPhone();
	  break;
	case 4:
	  insertPosition();
	  break;
	case 5:
	  removeNodePosition();
	  break;
	case 6:
	  removeNodeHead();
	  break;
	case 7:
	  removeNodeTail();
	  break;
	case 8:
	  findAndUpdate();
	  break;
	case 9:
	  slipFile();
	  break;
	case 10:
	  daoNguocDS();
	  printf("\nDao nguoc thanh cong!\n");
	  break;
	case 11:
	  saveFileDat();
	  printf("Luu thanh cong!\n");
	case 0:
	  break;
	default:
	  printf("Nhap lai gia tri!\n");
	}

    } while (dieukien != 0);

    removeNode();
    return 0;
}
