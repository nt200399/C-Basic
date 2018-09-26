//File dinh kem: https://github.com/thanhhff/C-Basic/blob/master/week3-3-danhsach.txt
#include <stdio.h>

#define MAX_DS 50
#define MAX_NAME 50
#define MAX_LEN 81

typedef struct
{
  int stt;
  int mssv;
  char name[MAX_NAME];
  char sdt[15];
  double diem;
} SV;

int soluongsv = 0;

void inputDS(FILE *file1, SV sinhvien[]);
void nhapdiem(SV sinhvien[]);
void outputDS(FILE *file2, SV sinhvien[]);
int checkdiem(double n);

int main()
{
  SV sinhvien[MAX_DS];
  FILE *file1, *file2;
  char filename1[] = "danhsach.txt";
  char filename2[] = "bangdiem.txt";

  if ((file1 = fopen(filename1, "r")) == NULL)
    {
      printf("Khong the mo %s\n", filename1);
      return 1;
    }
  else if ((file2 = fopen(filename2, "w")) == NULL)
    {
      printf("Khong the mo %s\n", filename2);
      return 1;
    }
  inputDS(file1, sinhvien);
  nhapdiem(sinhvien);
  outputDS(file2, sinhvien);
  fclose(file1);
  fclose(file2);
  return 0;
}

void inputDS(FILE *file1, SV sinhvien[])
{
  char str[MAX_LEN];
  int i = 0;
  
	//Quet du lieu tu dong thu 2
  while(fgets(str, MAX_LEN, file1) != NULL)
    {
      fscanf(file1, "%d %d %s %s", &sinhvien[i].stt, &sinhvien[i].mssv, sinhvien[i].name, sinhvien[i].sdt);
      i++;
      soluongsv++;
    }
}

void nhapdiem(SV sinhvien[])
{
  printf("%-4s %-10s %-20s %s\n", "STT", "MSSV", "HO TEN", "DIEM");
  for (int i = 0; i < soluongsv - 1; i++)
    {
      printf("%-4d %-10d %-20s ", sinhvien[i].stt, sinhvien[i].mssv, sinhvien[i].name);
      scanf("%lf", &sinhvien[i].diem);
      if (checkdiem(sinhvien[i].diem) == 0)
         {
           printf("\nVui long nhap diem trong khoang 0 - 10! Nhap lai!\n");
           i--;
	 }
    }
}

void outputDS(FILE *file2, SV sinhvien[])
{
  fprintf(file2, "%-4s %-10s %-20s %-15s %s\n", "STT", "MSSV", "HO TEN", "SDT", "DIEM");
  for (int i = 0; i < soluongsv - 1; i++)
    {
      fprintf(file2, "%-4d %-10d %-20s %-15s %.2lf\n", sinhvien[i].stt, sinhvien[i].mssv, sinhvien[i].name, sinhvien[i].sdt, sinhvien[i].diem);
    }
}

int checkdiem(double n)
{
  if (0 <= n && n <= 10)
     return 1;
  return 0;	
}
