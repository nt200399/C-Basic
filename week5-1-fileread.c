#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  char name[20];
  char tel[11];
  char mail[50];
} phone;

int main(int argv, char* argc[])
{
  FILE *f1;
  if (argv != 2)
    {
      printf("Nhap sai tham so dong lenh!\n"
	     "Nhap lai theo mau:\n"
	     "./fileread <filename>\n");
      return 0;
    }
  if ((f1 = fopen( argc[1] , "r + b")) == NULL)
    {
      printf("Khong the mo %s\n", argc[1]);
      return 1;
    }

  phone *dt;
  
  // Kiem tra co bao nhieu so dien thoai
  fseek(f1, 0, SEEK_END);
  int skt = ftell(f1) / sizeof(phone);
  rewind(f1);
  //
  
  dt = (phone*) malloc(sizeof(phone)*skt);
  
  // In ra so dien thoai
  fread(dt, sizeof(phone), skt, f1);
  
  for (int j = 0; j < skt; j++)
    {
      printf("%d. %s\t %s\t %s\t\n", j+1, dt[j].name, dt[j].tel, dt[j].mail);
    }

  free(dt);
  fclose(f1);
  return 0;
}
