#include <stdio.h>
#include <stdlib.h>

int n;
int *checkNgangDoc;
int *checkCheo1;
int *checkCheo2;
int *banco;
int dem = 0;

void inViTri()
{
  dem++;
  printf("\nCach xep %d\n", dem);
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
	{
	  if (j == banco[i])
	    printf("1\t");
	  else
	    printf("-\t");
	}
      printf("\n");
    }
  // exit(0);
}

int check(int i, int quanHau)
{
  if (checkNgangDoc[i] != 0)
    return 0;
  if (checkCheo1[quanHau + i] != 0)
    return 0;
  if (checkCheo2[quanHau - i + n] != 0)
    return 0;
  return 1;
}

void TRY(int quanHau)
{
  //quanHau ban dau = 0;
  if (quanHau == n)
    inViTri();
  for (int i = 0; i < n; i++)
    {
      if (check(i, quanHau) == 1)
	{
	  banco[quanHau] = i;
	  checkNgangDoc[i] = 1;
	  checkCheo1[quanHau + i] = 1;
	  checkCheo2[quanHau - i + n] = 1;

	  TRY(quanHau + 1);

	  checkNgangDoc[i] = 0;
	  checkCheo1[quanHau + i] = 0;
	  checkCheo2[quanHau - i + n] = 0;
	}
    }
}

int main()
{
  printf("Nhap kich thuoc ban co (n x n): ");
  scanf("%d", &n);

  checkNgangDoc = (int *)malloc(sizeof(int)*(n-1));
  checkCheo1 = (int *)malloc(sizeof(int)*(2*n));
  checkCheo2 = (int *) malloc (sizeof(int)*(2*n));
  banco = (int *) malloc(sizeof(int)*(n-1));
  
  TRY(0);
  if (dem == 0)
    printf("Khong co cach xep!\n");
  
  free(checkNgangDoc);
  free(checkCheo1);
  free(checkCheo2);
  free(banco);

  return 0;
}
