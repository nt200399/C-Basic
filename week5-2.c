#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 81

typedef struct
{
  int stt;
  int mssv;
  char name[20];
  char sdt[15];
  double diem;
} SV;

void text2dat(FILE *fileT, FILE *fileD);
void infiledat(FILE *fileD);
void searchAndupdate(FILE *fileD);
void nhapdiem(SV *sinhvien, int j, FILE *fileD);

char filenameT[] = "grade.txt";
char filenameD[] = "grade.dat";

int main()
{
  FILE *fileT, *fileD;
  int giatri;
  do
    {
      printf("\n------MENU------\n"
	     "1. Text2Dat\n"
	     "2. Xem file Dat\n"
	     "3. Tim va Cap nhat\n"
	     "4. Thoat!\n");
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
	  searchAndupdate(fileD);
	  break;
	case 4:
	  printf("\n THOAT! \n");
	  break;
	default :
	  printf("Gia tri khong hop le\n");
	}
    } while(giatri != 4);

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
  int ssv = 0;
  char str[MAX_LEN];
  while(fgets(str, MAX_LEN, fileT) != NULL)
      ssv++;
  //Bo dong dau!
  ssv = ssv - 1;
  
  rewind(fileT);

  // Quet so dien thoai vao struct dt
  SV *sinhvien;
  sinhvien = (SV*) malloc(sizeof(SV)*ssv);
  int i = 0;

  //Bo qua dong dau tien
  fgets(str, MAX_LEN, fileT);
  while(!feof(fileT))
    {
      fscanf(fileT, "%d %d %s %s %lf", &sinhvien[i].stt, &sinhvien[i].mssv, sinhvien[i].name, sinhvien[i].sdt, &sinhvien[i].diem);
  	i++;
    }

  /* for (int j = 0; j < i - 1; j++) */
  /*   { */
  /*     printf("%d %d %s %s %.2lf\n", sinhvien[j].stt, sinhvien[j].mssv, sinhvien[j].name, sinhvien[j].sdt, sinhvien[j].diem); */
  /*   } */

  //in sinh vien vao file dat;
  fwrite(sinhvien, sizeof(SV), ssv, fileD);

  free(sinhvien);
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

  SV *sinhvien;
  
  // Kiem tra co bao nhieu sinh vien
  fseek(fileD, 0, SEEK_END);
  int skt = ftell(fileD) / sizeof(SV);
  rewind(fileD);
  //
  sinhvien = (SV*) malloc(sizeof(SV)*skt);
  
  // In ra sinh vien
  fread(sinhvien, sizeof(SV), skt, fileD);
  printf("%-4s %-10s %-20s %-15s %s\n", "STT", "MSSV", "HO TEN", "SDT", "DIEM");
  for (int j = 0; j < skt; j++)
    {
      printf("%-4d %-10d %-20s %-15s %.2lf\n", sinhvien[j].stt, sinhvien[j].mssv, sinhvien[j].name, sinhvien[j].sdt, sinhvien[j].diem); 
    }

  free(sinhvien);
  fclose(fileD);
}

void searchAndupdate(FILE *fileD)
{
  if ((fileD = fopen(filenameD , "r + b")) == NULL)
    {
      printf("Khong the mo %s\n", filenameD);
      exit(0);
    }

  SV *sinhvien;
  
  // Kiem tra co bao nhieu sinh vien
  fseek(fileD, 0, SEEK_END);
  int skt = ftell(fileD) / sizeof(SV);
  rewind(fileD);
  //
  sinhvien = (SV*) malloc(sizeof(SV)*skt);
  
  // Doc sinh vien
  fread(sinhvien, sizeof(SV), skt, fileD);

  // Tim kiem sinh vien theo ma so!

  int check;
  do
    {
      int mssv;
      printf("Nhap MSSV: ");
      scanf("%d", &mssv);
      int j = 0;
      check = 0;
      for ( ; j < skt; j++)
	{
	  if (mssv == sinhvien[j].mssv)
	    {
	      check = 1;
	      printf("%-10d %-20s %-15s %.2lf\n\n", sinhvien[j].mssv, sinhvien[j].name, sinhvien[j].sdt, sinhvien[j].diem);

	      nhapdiem(sinhvien, j, fileD);
	      printf("Sau khi doi diem!\n");
	      printf("%-10d %-20s %-15s %.2lf\n\n", sinhvien[j].mssv, sinhvien[j].name, sinhvien[j].sdt, sinhvien[j].diem);
	      
	      break;
	    }
	}
      if (check == 0)
	{
	  printf("Khong co sinh vien mang mssv la: %d\n"
		 "Vui long nhap lai!\n\n",mssv);
	  // infiledat(fileD);
	}
    } while (check == 0);

  free(sinhvien);
  fclose(fileD);  
}

void nhapdiem(SV *sinhvien, int j, FILE *fileD)
{
  do
    {
      printf("Nhap diem moi: ");
      scanf("%lf", &sinhvien[j].diem);
      if (sinhvien[j].diem > 10 || sinhvien[j].diem < 0)
	printf("Nhap lai diem trong khoang 0 den 10!\n");
    } while (sinhvien[j].diem > 10 || sinhvien[j].diem < 0);

  SV *change;
  change = &sinhvien[j]; 
  
  fseek(fileD, sizeof(SV)*j, SEEK_SET);
  fwrite(change, sizeof(SV), 1, fileD);
  
}
