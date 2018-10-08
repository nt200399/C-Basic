#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_LEN 81

typedef struct
{
  char name[20];
  char dungluong[8];
  char kichco[15];
  char giatien[15];
} PHONE;

void text2dat(FILE *fileT, FILE *fileD);
void infiledat(FILE *fileD);
void in(PHONE *dt, int skt);
void doctheotrang(FILE *fileD);
void timkiemdt(FILE *fileD);

char filenameT[] = "phoneDB.txt";
char filenameD[] = "phoneDB.dat";

int main()
{
  FILE *fileT, *fileD;
  int giatri;
  do
    {
      printf("\n------MENU------\n"
	     "1. Text2Dat\n"
	     "2. Doc file theo cac che do\n"
	     "3. Doc file theo trang\n"
	     "4. Tim kiem\n"
	     "5. Thoat!\n");
      printf("Chon: ");
      scanf("%d", &giatri);

      switch (giatri)
	{
	case 1:
	  text2dat(fileT, fileD);
	  break;
	case 2:
	  infiledat(fileD);
	  break;
	case 3:
	  doctheotrang(fileD);
	  break;
	case 4:
	  timkiemdt(fileD);
	  break;
	case 5:
	  printf("\n THOAT! \n");
	  break;
	default :
	  printf("Gia tri khong hop le\n");
	}
    } while(giatri != 5);

  return 0;
}

void text2dat(FILE *fileT, FILE *fileD)
{
  if ((fileT = fopen(filenameT, "r")) == NULL)
    {
      printf("Khong the mo %s\n", filenameT);
      exit(0);
    }

  if ((fileD = fopen(filenameD , "wb")) == NULL)
    {
      printf("Khong the mo %s\n", filenameD);
      exit(0);
    }
  
  //Dem so sinh vien trong list
  int smd = 0;
  char str[MAX_LEN];
  while(fgets(str, MAX_LEN, fileT) != NULL)
      smd++;
  //Bo dong dau!
  smd = smd - 1;
  
  rewind(fileT);

  // Quet so dien thoai vao struct dt
  PHONE *dt;
  dt = (PHONE*) malloc(sizeof(PHONE)*smd);
  int i = 0;

  //Bo qua dong dau tien
  fgets(str, MAX_LEN, fileT);
  while(!feof(fileT))
    {
      fscanf(fileT, "%s %s %s %s", dt[i].name, dt[i].dungluong, dt[i].kichco, dt[i].giatien);
  	i++;
    }

  //in sinh vien vao file dat;
  fwrite(dt, sizeof(PHONE), smd, fileD);
  free(dt);
  fclose(fileT);
  fclose(fileD);
  printf("Chuyen file Txt sang Dat thanh cong!\n");
}

void infiledat(FILE *fileD)
{
  if ((fileD = fopen(filenameD , "rb")) == NULL)
    {
      printf("Khong the mo %s\n", filenameD);
      exit(0);
    }

  PHONE *dt;
  
  // Kiem tra co bao nhieu sinh vien
  fseek(fileD, 0, SEEK_END);
  int skt = ftell(fileD) / sizeof(PHONE);
  rewind(fileD);

  ///////////////////////////////////////
  int chon;
  printf("\n----------------------\n"
	 "1. Doc toan phan tu dau\n"
	 "2. Doc toan phan tu duoi\n"
	 "3. Doc 1 phan tu tren voi so phan tu\n"
	 "4. Doc 1 phan tu duoi voi so phan tu\n"
	 "Chon: ");
  scanf("%d", &chon);
  //
  int sophantu = 0;
  if (chon == 3 || chon == 4)
    {
      printf("Nhap so phan tu: ");
      scanf("%d", &sophantu);
    }
  else
    sophantu = skt;
  
  switch (chon)
    {
    case 1:
    case 3:
      rewind(fileD);
      dt = (PHONE*) malloc(sizeof(PHONE)*sophantu);
      fread(dt, sizeof(PHONE), sophantu, fileD);
      in(dt, sophantu);
      free(dt);
      break;
    case 2:
    case 4:
      rewind(fileD);
      dt = (PHONE*) malloc(sizeof(PHONE)*sophantu);
      int i = 0;
      printf("\n%-4s %-15s %-10s %-20s %s\n", "STT", "Model", "DLBN", "Kich Thuoc MH", "Gia Tien");
      while(i != sophantu)
	{
	  fseek(fileD, -sizeof(PHONE)*(i+1), SEEK_END);
	  fread(dt, sizeof(PHONE), 1, fileD);
	  printf("%-4d %-15s %-10s %-20s %s\n",i+1, dt[0].name, dt[0].dungluong, dt[0].kichco, dt[0].giatien);
	  i++;
	}
      free(dt);
      break;
    default:
      printf("Gia tri khong thoa man!\n");
    }

  fclose(fileD);
}

void in(PHONE *dt, int skt)
{
  printf("\n%-4s %-15s %-10s %-20s %s\n", "STT", "Model", "DLBN", "Kich Thuoc MH", "Gia Tien");
  for (int j = 0; j < skt; j++)
    {
      printf("%-4d %-15s %-10s %-20s %s\n",j+1, dt[j].name, dt[j].dungluong, dt[j].kichco, dt[j].giatien); 
    }
}

////////////////////////////////////////////////////////////
void doctheotrang(FILE *fileD)
{
  if ((fileD = fopen(filenameD , "rb")) == NULL)
    {
      printf("Khong the mo %s\n", filenameD);
      exit(0);
    }

  PHONE *dt;

  // Kiem tra co bao nhieu sinh vien
  fseek(fileD, 0, SEEK_END);
  int skt = ftell(fileD) / sizeof(PHONE);
  rewind(fileD);

  dt = (PHONE*) malloc(sizeof(PHONE)*skt);
  
  int dem = 0, i = 0;
  float val = (float) skt / 24;
  int trang = 1;
  printf("\n%-4s %-15s %-10s %-20s %s\n", "STT", "Model", "DLBN", "Kich Thuoc MH", "Gia Tien");
  
  while(1)
    {
      fread(dt, sizeof(PHONE), 1, fileD);
      if (feof(fileD))
	break;
      dem ++;
      printf("%-4d %-15s %-10s %-20s %s\n",i+1, dt[0].name, dt[0].dungluong, dt[0].kichco, dt[0].giatien);
      i++;
      if (dem == 24)
	{
	  printf("\nTrang %d/%.0lf\n"
		 "Bam phim Enter de doc tiep - bam phim khac de ket thuc!\n", trang, ceil(val));
	  dem = 0;
	  trang++;
	  char enter;
	  scanf("%c%*c", &enter);
	  if (enter == '\n')
	    continue;
	  else
	    {
	      printf("Ket thuc!\n");
	      break;
	    }
	   /* while (getchar() != '\n' && getchar() != EOF) */
	   /*   { */
	   /*   } */
	}
    }

  free(dt);
  fclose(fileD);
}

void timkiemdt(FILE *fileD)
{
  if ((fileD = fopen(filenameD , "rb")) == NULL)
    {
      printf("Khong the mo %s\n", filenameD);
      exit(0);
    }

  PHONE *dt;

  // Kiem tra co bao nhieu sinh vien
  fseek(fileD, 0, SEEK_END);
  int skt = ftell(fileD) / sizeof(PHONE);
  rewind(fileD);

  dt = (PHONE*) malloc(sizeof(PHONE)*skt);
  fread(dt, sizeof(PHONE), skt, fileD);
  printf("\nNhap model tim kiem: \n");

  char model[MAX_LEN];
  scanf("%s", model);
  //fgets(model, MAX_LEN, stdin);
  int check = 0, check2 = 0;
  // printf("\n");
  for (int i = 0; i < skt; i++)
    {
      if(strcmp(model, dt[i].name) == 0)
	{
	  check = 1;
	  if ((check + check2) == 1)
	    {
	      printf("\n%-15s %-10s %-20s %s\n", "Model", "DLBN", "Kich Thuoc MH", "Gia Tien");
	      check2 = 1;
	    }
	  printf("%-15s %-10s %-20s %s\n", dt[i].name, dt[i].dungluong, dt[i].kichco, dt[i].giatien);
	}
    }

  if (check == 0)
    {
      printf("\nKhong tim thay model: %s !\n", model);
    }


  free(dt);
  fclose(fileD);
  
}
