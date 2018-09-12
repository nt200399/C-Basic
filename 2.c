#include <stdio.h>
#include <string.h>
#define MAX 200

typedef struct
{
  char fullname[50];
  char name[10];
} SV;

void nhapmang(SV sinhvien[], int soluong);
void tachten(SV sinhvien[], int soluong);
void daomang(char arr[]);
void sapxepten(SV sinhvien[], int soluong);
void inmang(SV sinhvien[], int soluong);
void sinhvientrungten(SV sinhvien[], int soluong);

int main()
{
  SV sinhvien[MAX];
  int soluong;
  printf("Nhap so luong sinh vien: ");
  scanf("%d%*c", &soluong);

  nhapmang(sinhvien, soluong);
  tachten(sinhvien, soluong);
  sapxepten(sinhvien, soluong);
  inmang(sinhvien, soluong);
  sinhvientrungten(sinhvien, soluong);
  
  return 0;
}

void nhapmang(SV sinhvien[], int soluong)
{
    printf("Nhap ho va ten sinh vien !\n");
  for (int i = 0; i < soluong; i++)
    {
      printf("%d. ", i+1);
      gets(sinhvien[i].fullname);
    }
}

void tachten(SV sinhvien[], int soluong)
{
  for (int i = 0; i < soluong; i++)
    {
      int n = strlen(sinhvien[i].fullname);
      for (int j = 0; j < n; j++)
  	{
	  if (sinhvien[i].fullname[n - j - 1] == ' ')
	    break;
	  sinhvien[i].name[j] = sinhvien[i].fullname[n - j - 1];	  
  	}
      daomang(sinhvien[i].name);
    }
}

void daomang(char arr[])
{
  int n = strlen(arr);
  for (int i = 0; i < n / 2; i++)
    {
      char change;
      change = arr[i];
      arr[i] = arr[n - i - 1];
      arr[n - i - 1] = change;
    }
}

void sapxepten(SV sinhvien[], int soluong)
{
  for (int i = 0; i < soluong - 1; i++)
      for (int j = i + 1; j < soluong; j++)
	  if (strcmp(sinhvien[i].name, sinhvien[j].name) >= 0)
	    {
	      SV change;
	      change = sinhvien[i];
	      sinhvien[i] = sinhvien[j];
	      sinhvien[j] = change;
	    }
}

void inmang(SV sinhvien[], int soluong)
{
  printf("\nDanh sach moi !\n");
  for (int i = 0; i < soluong; i++)
    {
      printf("%d. ", i+1);
      puts(sinhvien[i].fullname);
    }
}

void sinhvientrungten(SV sinhvien[], int soluong)
{
  int demtrungmax = 0;
  char tentrung[MAX];

  for (int i = 0; i < soluong - 1; i++)
    {
      int dem = 1;
      for (int j = i + 1; j < soluong; j++)
	if (strcmp(sinhvien[i].name, sinhvien[j].name) == 0)
	  {
	    dem++;
	  }
      if (dem > demtrungmax)
	{
	demtrungmax = dem;
	strcpy(tentrung,sinhvien[i].name);
	}
    }

  if (demtrungmax > 1)
      printf("\nSinh vien '%s' co %d ten trung nhau!\n", tentrung, demtrungmax);
  else
    printf("\nKhong co sinh vien trung ten!\n");
}
