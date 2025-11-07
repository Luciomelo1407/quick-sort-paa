#include <stdio.h>
#include <stdlib.h>
typedef struct {
  int *vector;
  int *pos;
} array;

int main(int argc, char *argv[]) {
  array arr;
  arr.vector = malloc(3 * sizeof(int));
  arr.pos = malloc(3 * sizeof(int));
  arr.pos[0] = 0;
  arr.pos[1] = 1;
  arr.pos[2] = 2;
  arr.vector[0] = 9;
  arr.vector[1] = 8;
  arr.vector[2] = 5;
  int swapPos;
  int swapVec;
  int ordenado = 0;
  while (ordenado < 2) {
    for (int i = 0; i < 2; i++) {
      if (arr.vector[i] > arr.vector[i + 1]) {
        swapVec = arr.vector[i];
        swapPos = arr.pos[i];
        arr.vector[i] = arr.vector[i + 1];
        arr.vector[i + 1] = swapVec;
        arr.pos[i] = arr.pos[i + 1];
        arr.pos[i + 1] = swapPos;
      } else {
        ordenado++;
      }
    }
  }
  printf("ordenado: %d, %d, %d", arr.vector[0], arr.vector[1], arr.vector[2]);
  printf("ordenado: %d, %d, %d", arr.pos[0], arr.pos[1], arr.pos[2]);

  free(arr.vector);
  free(arr.pos);

  return 0;
}
