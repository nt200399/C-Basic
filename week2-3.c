#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

void cp(FILE *file1, FILE *file2);

int main(int argc, char *argv[])
{
  FILE *file1, *file2;
  char filename1[MAX], filename2[MAX];
  if (argc != 4)
    {
      printf("Nhap sai tham so dong lenh!\n"
	     "Nhap lai theo mau: ./bai3 mycp <file1> <file2>\n");
      return 1;
    }

  char str[] = "mycp";
  if (strcmp(str, argv[1]) != 0)
    {
      printf("Nhap sai tham so dieu khien! Tham so dung la: mycp\n"
	     "Nhap lai theo mau: ./bai3 mycp <file1> <file2>\n");
      return 3;
    }
  
  strcpy(filename1, argv[2]);
  strcpy(filename2, argv[3]);

  if ((file1 = fopen(filename1,"r")) == NULL)
    {
      printf("Khong the mo %s\n", filename1);
      return 2;
    }
  else if ((file2 = fopen(filename2, "w")) == NULL)
    {
      printf("Khong the mo %s\n", filename2);
      return 2;
    }
  else
    {
      cp(file1, file2);
      fclose(file1);
      fclose(file2);
    }
  
    
  return 0;
}

void cp(FILE *file1, FILE *file2)
{
  char c;
  while ((c = fgetc(file1)) != EOF)
      fputc(c, file2);
  printf("Copy file thanh cong!\n");
}
