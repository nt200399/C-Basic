//Chuong trinh giai phuong trinh bac 2
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

void giaiptb2(double a, double b, double c);

int main(int argc, char *argv[])
{
  double a, b, c;
  char str[] = "sde";
  if (argc != 5)
    {
      printf("Nhap sai doi so dong lenh!\n"
	     "Nhap lai theo mau: ./bai2 sde <a> <b> <c>\n"
	     "Vi du: ./bai2 sde 1 2 1\n");
      return 1;
    }
 
  for (int i = 0; i < strlen(argv[1]); i++)
    {
      argv[1][i] = tolower(argv[1][i]);
    }
  
  if (strcmp(str, argv[1]) != 0)
    {
      printf("Nhap sai tham so dieu khien! Tham so dung la: sde\n"
	     "Vi du: ./bai2 sde 1 2 1\n");
      return 2;
    }
  
  a = atof(argv[2]);
  b = atof(argv[3]);
  c = atof(argv[4]);

  if (a != 0)
    giaiptb2(a,b,c);
  else if (b == 0)
    printf("Ca <a> va <b> khong the cung bang 0. Nhap lai!\n");
  else
    printf("Phuong trinh co 1 nghiem: %lf\n", (double) -c/b);

  return 0;
}

void giaiptb2(double a, double b, double c)
{
  double denta, x1, x2;
  denta =(double) b*b - 4*a*c;

  if (denta < 0)
    printf("Phuong trinh vo nghiem!\n");
  else if (denta == 0)
    {
      x1 = x2 = - (double) b / 2*a;
      printf("Phuong trinh co nghiem kep!\n"
	     "x1 = x2 = %lf\n", x1);
    }
  else if (denta > 0)
    {
      x1 = (double) (-b + sqrt(denta)) / (2*a);
      x2 = (double) (-b - sqrt(denta)) / (2*a);
      printf("Phuong trinh co 2 nghiem phan biet!\n"
	     "x1 = %lf\n"
	     "x2 = %lf\n",x1, x2);
    }
}
