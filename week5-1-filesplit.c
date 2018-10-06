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
  FILE *f1, *f2, *f3;
  if (argv != 5)
    {
      printf("Nhap sai tham so dong lenh!\n"
	     "Nhap lai theo mau:\n"
	     "./filesplit <filename> <number> <filename1> <filename2>\n");
      return 0;
    }
  if ((f1 = fopen( argc[1] , "rb")) == NULL)
    {
      printf("Khong the mo %s\n", argc[1]);
      return 1;
    }

  if ((f2 = fopen( argc[3] , "wb")) == NULL)
    {
      printf("Khong the mo %s\n", argc[3]);
      return 1;
    }

  if ((f3 = fopen( argc[4] , "wb")) == NULL)
    {
      printf("Khong the mo %s\n", argc[4]);
      return 1;
    }

  phone *dt;
  
  int number;
  number = atoi(argc[2]);
  
  // Kiem tra co bao nhieu so dien thoai
  fseek(f1, 0, SEEK_END);
  int skt = ftell(f1) / sizeof(phone);
  rewind(f1);

  //
  if (number < 0 || number > skt)
    {
      printf("So cac lien lac vuot qua so cac lien lac hien hanh!\n"
	     "So cac lien lac hien co la: %d\n", skt);
      return 2;
    }

  // Input vao f1
  dt = (phone *)malloc(sizeof(phone)*number);
  fread(dt, sizeof(phone), number, f1);
  fwrite(dt, sizeof(phone), number, f2);
  free(dt);

  // Input vao f2
  dt = (phone *)malloc(sizeof(phone)*(skt - number));
  fread(dt, sizeof(phone), skt - number, f1);
  fwrite(dt, sizeof(phone), skt - number, f3);
  free(dt);

  fclose(f1);
  fclose(f2);
  fclose(f3);
  printf("Thanh cong!\n");
  return 0;
}
