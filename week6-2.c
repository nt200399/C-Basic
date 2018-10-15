#include <stdio.h>
#include <string.h>

int dem = 0;
int TRY(char str[], int dodai)
{
  if (dem == dodai)
    return dem;

  if ('A' <= str[dem] && str[dem] <= 'Z')
    return dem;
  dem++;
  
  return TRY(str, dodai);
}

int main()
{
  char str[50];
  printf("Nhap xau: ");
  gets(str);
  int dodai = strlen(str);
  int vitri = TRY(str, dodai);

  if (vitri == dodai)
    printf("Khong co chu in hoa xuat hien!\n");
  else
    printf("Vi tri chu in hoa dau tien la: %d\n", vitri);

  return 0;
}
