// Bai toan tinh e^x 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

double tinhE(double somu, double saiso);

int main(int argc, char *argv[])
{
  double somu, saiso;
  if (argc != 3 && argc !=4)
    {
      printf("Nhap sai doi so dong lenh!\n");
      printf("Nhap lai theo mau: ./bai1 e <so mu> (<sai so>)\n"
	     "Vi du: ./bai1 e 2 0.00001\n");
      return 1;
    }
  
  char c = *argv[1];
    if (c != 'e' && c != 'E')
    {
      printf("Chuong trinh tinh e^x vui long nhap lai tham so tinh la: e\n"
	     "Nhap lai theo mau: ./bai1 e <so mu> (<sai so>)\n");
      return 2;
    }
  

  if (argc == 3)
    {
      saiso = 0.00001;
      somu = atof(argv[2]);
    }
  else
    {
      somu = atoi(argv[2]);
      saiso = atof(argv[3]);
      if (saiso <= 0)
	{
	  printf("Vui long nhap gia tri <sai so> lon hon 0\n");
	  return 4;
	}
      if (abs(saiso) > abs(somu))
        {
          printf("Vui long nhap gia tri |<sai so>| nho hon |<so mu>|\n");
          return 5;
        }
    }

  printf("Gia tri cua e^%.3lf la: %.9lf\n", somu, tinhE(somu, saiso));
  
  return 0;
}

double tinhE(double somu, double saiso)
{
  int n = 1;
  double giatri = 1, tuso = somu, mauso = n;
  
  while (fabs(tuso / mauso) >= saiso)
    {
      giatri += (double) tuso / mauso;
      n++;
      tuso *= somu;
      mauso *= n;
    }
  
  return giatri;
}
