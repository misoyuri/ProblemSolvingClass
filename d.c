#include <stdio.h>


void swap(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}


int main(void) {
  for(int i = 0; i < 500; i++){
    printf("1 ");
  }
}