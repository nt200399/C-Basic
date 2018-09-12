#include <stdio.h>

int n = 5;

int sosanh(int arr1[], int arr2[]);

int main()
{
  // int arr1[5] = {1,2,3,4,5}, arr2[5] = {1,2,3,4,5};
  int arr1[5] = {5,4,3,2,1}, arr2[5] = {1,2,3,4,5};
  //   int arr1[5] = {1,2,3,4,6}, arr2[5] = {1,2,3,4,5};

  int gttv = sosanh(arr1, arr2);

  if (gttv == 1)
    printf("Hai mang bang nhau !\n");
  else if (gttv == -1)
     printf("Hai mang doi nhau !\n");
  else
    printf("Hai mang khac nhau !\n");
    

  return 0;
}

int sosanh(int arr1[], int arr2[])
{
  int dem1 = 0, dem2 = 0;
  for (int i = 0; i < n; i++)
    {
      if (arr1[i] == arr2[i])
	dem1++;
      if (arr1[i] == arr2[n-i-1])
	dem2++;
    }
  if (dem1 == n)
    return 1;
  else
      if (dem2 == n)
	return -1;
  return 0;
    
}
