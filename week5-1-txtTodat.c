#include <stdio.h>

#define MAX_LEN 81

typedef struct
{
  char name[20];
  char tel[11];
  char mail[50];
} phone;

int main()
{
  FILE *file1, *file2;
  if ((file1 = fopen("dulieu.txt", "r")) == NULL)
    {
      printf("Khong the mo %s\n", "dulieu.txt");
      return 1;
    }
  if ((file2 = fopen("phone.dat", "wb")) == NULL)
    {
      printf("Khong the mo %s\n", "phone.dat");
      return 1;
    }

  //Dem so dien thoai trong list
  int sdt = 0;
  char str[MAX_LEN];
  while(fgets(str, MAX_LEN, file1) != NULL)
    {
      sdt++;
    }
  //
  
  rewind(file1);

  // Quet so dien thoai vao struct dt
  phone dt[sdt];
  int i = 0;
  while(!feof(file1))
    {
      fscanf(file1, "%s %s %s", dt[i].name, dt[i].tel, dt[i].mail);
  	i++;
    }

  /* for (int j = 0; j < i - 1; j++) */
  /*   { */
  /*     printf("%d. %s\t %s\t %s\t\n", j + 1, dt[j].name, dt[j].tel, dt[j].mail); */
  /*   } */

  // in sdt vao file2;
  fwrite(dt, sizeof(phone), sdt, file2);

  fclose(file1);
  fclose(file2);
  printf("Thanh cong!\n");
  return 0;
}
