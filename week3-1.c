#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_ALP 26

void mahoa(FILE *file1, FILE *file2, int dolech);
void giaima(FILE *file1, FILE *file3, int dolech);

int main(int argv, char *argc[])
{
  int dolech;
  FILE *file1, *file2, *file3;

  char filename1[MAX];
  char filename2[] = "kqbai1.txt";
  char filename3[] = "gmbai1.txt";

  if (argv != 4)
    {
      printf("Nhap sai tham so dong lenh\n"
	     "Nhap lai theo mau:\n"
	     "Ma hoa: ./bai1 mahoa <filename> <dolech>\n"
	     "Gia ma: ./bai1 giaima <filename> <dolech>\n");
      return 1;
    }

  strcpy(filename1, argc[2]);
  dolech = atoi(argc[3]);
  dolech %= MAX_ALP;
  
  if ((file1 = fopen(filename1, "r")) == NULL)
    {
      printf("Khong the mo %s\n", filename1);
      return 2;
    }

  if (dolech < 0)
    {
      printf("Vui long nhap do lech >= 0\n");
      return 4;
    }

  // MA HOA FILE
  if (strcmp(argc[1], "mahoa") == 0)
    { 
      if ((file2 = fopen(filename2, "w")) == NULL)
	{
	  printf("Khong the mo %s\n", filename2);
	  return 2;
	}
      mahoa(file1, file2, dolech);
      fclose(file2);
    }
  // GIAI MA FILE
  else if (strcmp(argc[1], "giaima") == 0)
    {
      if ((file3 = fopen(filename3, "w")) == NULL)
	{
	  printf("Khong the mo %s\n", filename3);
	  return 2;
	}
      giaima(file1, file3, dolech);
      fclose(file3);
    }

  else 
    {
      printf("Nhap sai tham so dieu khien\n"
	     "Nhap lai theo mau:\n"
	     "Ma hoa: ./bai1 mahoa <filename> <dolech>\n"
	     "Gia ma: ./bai1 giaima <filename> <dolech>\n");
      return 5;
    }

  fclose(file1);
  
  return 0;
}

void mahoa(FILE *file1, FILE *file2, int dolech)
{
  char c;
  while ((c = fgetc(file1)) != EOF)
    {
      if ('a' <= c && c <= 'z')
	{
	  if ((c + dolech) > 'z')
	    c = c - MAX_ALP + dolech;
	  else
	    c = c + dolech;
	}
      else if ('A' <= c && c <= 'Z')
	{
	  if ((c + dolech) > 'Z')
	    c = c - MAX_ALP + dolech;
	  else
	    c = c + dolech;
	}      
      fputc(c, file2);
    }
}

void giaima(FILE *file1, FILE *file3, int dolech)
{
  char c;
  while ((c = fgetc(file1)) != EOF)
    {
      if ('a' <= c && c <= 'z')
  	{
  	  if ((c - dolech) < 'a')
  	    c = c + MAX_ALP - dolech;
  	  else
  	    c = c - dolech;
  	}
      else if ('A' <= c && c <= 'Z')
  	{
  	  if ((c - dolech) < 'A')
  	    c = c + MAX_ALP - dolech;
  	  else
  	    c = c - dolech;
  	}
      fputc(c, file3);
    }
}
