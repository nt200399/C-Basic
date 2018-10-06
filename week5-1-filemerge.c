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
  if (argv != 4)
    {
      printf("Nhap sai tham so dong lenh!\n"
	     "Nhap lai theo mau:\n"
	     "./filesplit <filename1> <filename2> <filename>\n");
      return 0;
    }
  if ((f1 = fopen( argc[1] , "rb")) == NULL)
    {
      printf("Khong the mo %s\n", argc[1]);
      return 1;
    }

  if ((f2 = fopen( argc[2] , "rb")) == NULL)
    {
      printf("Khong the mo %s\n", argc[2]);
      return 1;
    }

  if ((f3 = fopen( argc[3] , "wb")) == NULL)
    {
      printf("Khong the mo %s\n", argc[3]);
      return 1;
    }

  phone *dt;
  
  // Kiem tra co bao nhieu so dien thoai
  fseek(f1, 0, SEEK_END);
  int skt1 = ftell(f1) / sizeof(phone);
  rewind(f1);

  fseek(f2, 0, SEEK_END);
  int skt2 = ftell(f2) / sizeof(phone);
  rewind(f2);

  // Input vao f1 vao f3
  dt = (phone *)malloc(sizeof(phone)*skt1);
  fread(dt, sizeof(phone), skt1, f1);
  fwrite(dt, sizeof(phone), skt1, f3);
  free(dt);

  // Input vao f2 vao f3
  dt = (phone *)malloc(sizeof(phone)*(skt2));
  fread(dt, sizeof(phone), skt2, f2);
  fwrite(dt, sizeof(phone), skt2, f3);
  free(dt);

  fclose(f1);
  fclose(f2);
  fclose(f3);
  printf("Thanh cong!\n");
  return 0;
}
