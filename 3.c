#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define MAX_LEN 81

void copytheokitu(FILE *file1, FILE *file2);
void copytheodong(FILE *file1, FILE *file2);
void copytheoblock(FILE *file1, FILE *file2);

double start_time;
double end_time;

int main()
{
  FILE *file1, *file2;
  char filename1[] = "dulieu.txt";
  char filename2[] = "kqbai3.txt";
  /* char filename1[MAX]; */
  /* char filename2[MAX]; */

  /* printf("Chuong trinh sao chep!\n" */
  /* 	 "Nhap theo mau: <filename1> <filename2>\n"); */
  /* scanf("%s", filename1); */
  /* scanf("%s", filename2); */

  if ((file1 = fopen(filename1, "r")) == NULL)
    {
      printf("Khong the mo %s\n", filename1);
      return 1;
    }

  int giatri = 0;
  do
    {
      printf("\nChuong trinh sao chep!\n"
	     "1. Sao chep theo ki tu\n"
	     "2. Sao chep theo dong\n"
	     "3. Sao chep theo block\n"
	     "0. Thoat !\n"
	     "Chon: ");
      scanf("%d", &giatri);
      if (giatri != 0)
	{
	  if ((file2 = fopen(filename2, "w")) == NULL)
	    {
	  printf("Khong the mo %s\n", filename2);
	  return 1;
	    }
	}
      switch(giatri)
	{
	case 1:
	  copytheokitu(file1, file2);
	  break;
	case 2:
	  copytheodong(file1, file2);
	  break;
	case 3:
	  copytheoblock(file1, file2);
	  break;
	case 0:
	    printf("\nChuong trinh ket thuc!\n\n");
	    break;
	default:
	  printf("Gia tri khong hop le!\n"
		 "Chon lai gia tri!\n");
	}
      fseek(file1, 0, SEEK_SET);
       
    } while (giatri != 0);
  
  fclose(file1);
  fclose(file2);
  return 0;
}

void copytheokitu(FILE *file1, FILE *file2)
{
  start_time = clock();
  char c;
  while((c = fgetc(file1)) != EOF)
    {
      fputc(c, file2);
    }
  fclose(file2);
  end_time = clock();
  printf("Sao chep thanh cong!\n");
  printf("Thoi gian chay: %lf s\n", (double) (end_time - start_time)/CLOCKS_PER_SEC );
}

void copytheodong(FILE *file1, FILE *file2)
{
  char str[MAX_LEN];

  start_time = clock();
  while (fgets(str, MAX_LEN, file1) != NULL)
    {
      fputs(str, file2);
    }
  fclose(file2);
  end_time = clock();
  printf("Sao chep thanh cong!\n");
  printf("Thoi gian chay: %lf s\n", (double) (end_time - start_time)/CLOCKS_PER_SEC );
}

void copytheoblock(FILE *file1, FILE *file2)
{
  int kichthuoc;
  char *str;
  printf("Nhap kich thuoc muon sao chep: ");
  scanf("%d", &kichthuoc);
  str = (char *) malloc((kichthuoc + 1)*sizeof(char));

  int copy;
  
  start_time = clock();
  while (!feof(file1))
    {
      copy = fread(str, sizeof(char), kichthuoc, file1);
      fwrite(str, sizeof(char), copy, file2);
    }
  free(str);
  fclose(file2);
  end_time = clock();
  printf("Sao chep thanh cong!\n");
  printf("Thoi gian chay: %lf s\n", (double) (end_time - start_time)/CLOCKS_PER_SEC );
}
