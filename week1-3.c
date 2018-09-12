#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX 5
#define LENGTH 20
#define MaxHamChua 100

int soluongcau = 10;

int main()
{
  char article[MAX][LENGTH] = {"the", "a", "one", "some", "any"};
  char noun[MAX][LENGTH] = {"boy", "girl", "dog", "town", "car"};
  char verb[MAX][LENGTH] = {"drove", "jumped", "ran", "walked", "skipped"};
  char preposition[MAX][LENGTH] = {"to", "from", "over", "under", "on"};
  char HAMCHUA[soluongcau][MaxHamChua];

  srand(time(NULL));
  
  for (int i = 0; i < soluongcau; i++)
    {
      strcpy(HAMCHUA[i], "");
      strcat(HAMCHUA[i], article[rand()%MAX]);
      strcat(HAMCHUA[i], " ");
      strcat(HAMCHUA[i], noun[rand()%MAX]);
      strcat(HAMCHUA[i], " ");
      strcat(HAMCHUA[i], verb[rand()%MAX]);
      strcat(HAMCHUA[i], " ");
      strcat(HAMCHUA[i], preposition[rand()%MAX]);
      strcat(HAMCHUA[i], " ");
      strcat(HAMCHUA[i], article[rand()%MAX]);
      strcat(HAMCHUA[i], " ");
      strcat(HAMCHUA[i], noun[rand()%MAX]);
      
      HAMCHUA[i][0] =  toupper(HAMCHUA[i][0]);
      printf("%d. %s.\n", i+1, HAMCHUA[i]);
      
    }

  return 0;
}
