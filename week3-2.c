#include <stdio.h>
#include <string.h>

#define ALPLEN 26
#define MAX 50

int main(int argv, char *argc[])
{
  FILE *file1, *file2;
  char filename1[MAX];
  // char filename1[] = "bai1.txt";
  char filename2[] = "kqbai2.txt";
  int count[ALPLEN] = {0};

  if (argv != 2)
    {
      printf("Nhap sai tham so dong lenh!\n"
	     "Nhap lai theo mau: ./bai2 <filename>\n"
	     "Vi du: ./bai2 dulieu.txt\n");
      return 2;
    }

  strcpy(filename1, argc[1]);

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

  int c;
  while ((c = fgetc(file1)) != EOF)
    {
      if ('a' <= c && c <= 'z')
	count[c - 'a']++;
      if ('A' <= c && c <= 'Z')
	count[c - 'A']++;
    }
  fclose(file1);

  fputs("Ket qua la: \n", file2);

  for (int i = 0; i < ALPLEN; i++)
    {
       if (count[i] != 0)
	 fprintf(file2, "%c xuat hien %d lan \n", 'a' + i, count[i]);
    }
  fclose(file2);

  return 0;
}
