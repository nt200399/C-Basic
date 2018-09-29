//Note: Bien dich lai neu thay doi file dsnhaycam.txt
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100
#define MAX_DS 100

char mangdsnhaycam[MAX_DS][MAX_DS];
int sotunhaycam;

void dsnhaycam(char *filename);
void check(char arr[], char kitu[]);

int main(int argv, char *argc[])
{
  FILE *file1;
  char filename1[MAX_LEN];
  char fileds[] = "dsnhaycam.txt";
  
  if (argv != 3)
    {
      printf("Nhap sai tham so dong lenh!\n"
	     "Nhap lai theo mau: ./bai1 <file> <KiTuDacBiet>\n");
      return 1;
    }

  strcpy(filename1, argc[1]);
  
  if ((file1 = fopen(filename1, "r")) == NULL)
    {
      printf("Khong the mo %s\n", filename1);
      return 2;
    }
  
  dsnhaycam(fileds);
  
  char str[MAX_LEN];
  char c;
  while(!feof(file1))
    {
      c = fgetc(file1);
      //c < ki tu !(33) hoac lon hon ki tu z (126)
      if (c < '!' || c > 'z')
	printf("%c", c);
      else
	{
	  fseek(file1, -1, SEEK_CUR);
	  fscanf(file1, "%s", str);
	  check(str, argc[2]);
	} 
    }
  
  fclose(file1);
  return 0;
}

void dsnhaycam(char *filename)
{
  FILE *file;
  if ((file = fopen(filename, "r")) == NULL)
    {
      printf("Khong the mo %s\n", filename);
      exit(0);
    }
  fscanf(file, "%d", &sotunhaycam);
  for (int i = 0; i < sotunhaycam; i++)
    {
      fscanf(file, "%s", mangdsnhaycam[i]);
    }
  fclose(file);
}

void check(char arr[], char kitu[])
{
  int check = 0;
  for (int i = 0; i < sotunhaycam; i++)
    {
      if (strcmp(arr, mangdsnhaycam[i]) == 0)
	{
	  check = 1;
	  int getlen = strlen(arr);
	  for (int j = 0; j < getlen; j++)
	    printf("%s", kitu);
	}
    }
  if (check == 0)
    printf("%s", arr);
}
