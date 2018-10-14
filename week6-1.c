#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void TRY(int n)
{
  if (n != 1)
    TRY(n / 2);
  printf("%d", n % 2);
}

int main()
{
  int n;
  printf("Chuyen doi tu he co so 10 sang co so 2!\n"
	 "Nhap gia tri: ");
  scanf("%d", &n);
  while (n <= 0)
    {
      printf("Nhap lai gia tri duong!\n");
      printf("Gia tri: ");
      scanf("%d", &n);
    }
  printf("Sau khi chuyen: ");
  TRY(n);
  printf("\n");
  return 0;
}
