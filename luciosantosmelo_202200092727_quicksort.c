#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *input_file;
FILE *output_file;

typedef struct {
  int *vector;
  int *pos;
} array;

typedef struct {
  char *method;
  int count;
} PartitionMethod;

void printVec(int *vector, int size) {
  for (int i = 0; i < size; i++) {
    if (i + 1 < size) {
      printf("%d, ", vector[i]);
    } else {
      printf("%d\n", vector[i]);
    }
  }
}

int lomuto_default(int *vector, int begin, int end,
                   PartitionMethod *partitionsMethods) {
  int pivot = vector[end];
  int x = begin - 1;
  int swap = 0;

  for (int y = begin; y < end; y++) {
    if (vector[y] <= pivot) {
      partitionsMethods->count++;
      x++;
      swap = vector[x];
      vector[x] = vector[y];
      vector[y] = swap;
    }
  }

  partitionsMethods->count++;
  swap = vector[x + 1];
  vector[x + 1] = vector[end];
  vector[end] = swap;

  return x + 1;
}

void quick_sort_lomuto_default(int *vector, int begin, int end,
                               PartitionMethod *partitionsMethods) {
  partitionsMethods->count++;
  if (begin < end) {
    int pivot = lomuto_default(vector, begin, end, partitionsMethods);
    quick_sort_lomuto_default(vector, begin, pivot - 1, partitionsMethods);
    quick_sort_lomuto_default(vector, pivot + 1, end, partitionsMethods);
  }
}

void lomuto_median(
    int *vector, int begin, int end,
    PartitionMethod
        *partitionsMethods) { // WARN: provavelmente o problema está nesse
                              // malloc Alocando mem sem necessidade
  int n = (end - begin) + 1;
  int idx1 = begin + (n / 4);
  int idx2 = begin + (n / 2);
  int idx3 = begin + (3 * n / 4);
  int medianIdx;
  array arr;
  arr.vector = malloc(3 * sizeof(int));
  arr.pos = malloc(3 * sizeof(int));
  arr.pos[0] = idx1;
  arr.pos[1] = idx2;
  arr.pos[2] = idx3;
  arr.vector[0] = vector[idx1];
  arr.vector[1] = vector[idx2];
  arr.vector[2] = vector[idx3];
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
  partitionsMethods->count++;
  swapVec = vector[end];
  vector[end] = vector[arr.pos[1]];
  vector[arr.pos[1]] = swapVec;

  free(arr.vector);
  free(arr.pos);
}

void quick_sort_lomuto_median(int *vector, int begin, int end,
                              PartitionMethod *partitionsMethods) {
  partitionsMethods->count++;
  if (begin < end) {
    lomuto_median(vector, begin, end, partitionsMethods);
    int pivot = lomuto_default(vector, begin, end, partitionsMethods);
    quick_sort_lomuto_median(vector, begin, pivot - 1, partitionsMethods);
    quick_sort_lomuto_median(vector, pivot + 1, end, partitionsMethods);
  }
}

int lomuto_rand(int *vector, int begin, int end,
                PartitionMethod *partitionsMethods) {
  partitionsMethods->count++;
  int swap = vector[end],
      r_index = begin + abs(vector[begin]) % (end - begin + 1);
  vector[end] = vector[r_index];
  vector[r_index] = swap;
  return lomuto_default(vector, begin, end, partitionsMethods);
}

void quick_sort_lomuto_random(int *vector, int begin, int end,
                              PartitionMethod *partitionsMethods) {
  partitionsMethods->count++;
  if (begin < end) {
    int pivot = lomuto_rand(vector, begin, end, partitionsMethods);
    quick_sort_lomuto_random(vector, begin, pivot - 1, partitionsMethods);
    quick_sort_lomuto_random(vector, pivot + 1, end, partitionsMethods);
  }
}

int hoare_default(int *vector, int begin, int end,
                  PartitionMethod *partitionsMethods) {
  int pivot = vector[begin], x = begin - 1, y = end + 1, swap = 0;
  while (1) {
    while (vector[--y] > pivot) {
    }
    while (vector[++x] < pivot) {
    }
    if (x < y) {
      partitionsMethods->count++;
      swap = vector[x];
      vector[x] = vector[y];
      vector[y] = swap;
    } else {
      return y;
    }
  }
}

int hoare_rand(int *vector, int begin, int end,
               PartitionMethod *partitionsMethods) {
  partitionsMethods->count++;
  int swap = vector[begin],
      r_index = begin + abs(vector[begin]) % (end - begin + 1);
  vector[begin] = vector[r_index];
  vector[r_index] = swap;
  return hoare_default(vector, begin, end, partitionsMethods);
}
void quick_sort_hoare_rand(int *vector, int begin, int end,
                           PartitionMethod *partitionsMethods) {
  partitionsMethods->count++;
  if (begin < end) {
    int pivot = hoare_rand(vector, begin, end, partitionsMethods);
    quick_sort_hoare_rand(vector, begin, pivot, partitionsMethods);
    quick_sort_hoare_rand(vector, pivot + 1, end, partitionsMethods);
  }
}

void select_median_of_3_pivot(int *vector, int begin, int end,
                              PartitionMethod *partitionsMethods) {
  int n = (end - begin) + 1;
  int idx1 = begin + (n / 4);
  int idx2 = begin + (n / 2);
  int idx3 = begin + (3 * n / 4);
  int medianIdx;
  array arr;
  arr.vector = malloc(3 * sizeof(int));
  arr.pos = malloc(3 * sizeof(int));
  arr.pos[0] = idx1;
  arr.pos[1] = idx2;
  arr.pos[2] = idx3;
  arr.vector[0] = vector[idx1];
  arr.vector[1] = vector[idx2];
  arr.vector[2] = vector[idx3];
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
  partitionsMethods->count++;
  swapVec = vector[begin];
  vector[begin] = vector[arr.pos[1]];
  vector[arr.pos[1]] = swapVec;

  free(arr.vector);
  free(arr.pos);
}

void quick_sort_hoare_median(int *vector, int begin, int end,
                             PartitionMethod *partitionsMethods) {

  partitionsMethods->count++;
  if (begin < end) {
    select_median_of_3_pivot(vector, begin, end, partitionsMethods);
    int pivot = hoare_default(vector, begin, end, partitionsMethods);
    quick_sort_hoare_median(vector, begin, pivot, partitionsMethods);
    quick_sort_hoare_median(vector, pivot + 1, end, partitionsMethods);
  }
}

void quick_sort_hoare_default(int *vector, int begin, int end,
                              PartitionMethod *partitionsMethods) {
  partitionsMethods->count++;
  if (begin < end) {
    int pivot = hoare_default(vector, begin, end, partitionsMethods);
    quick_sort_hoare_default(vector, begin, pivot, partitionsMethods);
    quick_sort_hoare_default(vector, pivot + 1, end, partitionsMethods);
  }
}

// void quick_sort(int *vector, int begin, int end) {
//   if (begin < end) {
//     // int pivot = hoare_default(vector, begin, end);
//     int pivot = lomuto_median(vector, begin, end, (end - begin) / 2);
//     quick_sort(vector, begin, pivot);
//     quick_sort(vector, pivot + 1, end);
//   }
// }

void initPartitionMethods(PartitionMethod *partitionsMethods) {
  char *methods[6] = {"LP", "LM", "LA", "HP", "HM", "HA"};
  for (int i = 0; i < 6; i++) {
    partitionsMethods[i].method = methods[i];
    partitionsMethods[i].count = 0;
  }
}

int *generateVector(int size) {
  srand(time(NULL));
  int *vector = malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    vector[i] = rand() % 100;
  }
  return vector;
}

void ordenacaomacaca(PartitionMethod *vector) {
  int counter = 0;
  PartitionMethod swap;
  while (counter < 5) {
    counter = 0;
    for (int i = 0; i < 5; i++) {
      if (vector[i].count > vector[i + 1].count) {
        swap = vector[i];
        vector[i] = vector[i + 1];
        vector[i + 1] = swap;

      } else {
        counter++;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  char *file_out_path = argv[2];
  char *file_input_path = argv[1];
  input_file = fopen(file_input_path, "r");
  output_file = fopen(file_out_path, "w+");

  int quantity = 0;
  fscanf(input_file, "%d", &quantity);
  int **vectors = malloc(quantity * sizeof(int *));
  int *sizes = malloc(quantity * sizeof(int));
  for (int i = 0; i < quantity; i++) {
    fscanf(input_file, "%d", &sizes[i]);
    vectors[i] = malloc(sizes[i] * sizeof(int));
    for (int j = 0; j < sizes[i]; j++) {
      fscanf(input_file, "%d", &vectors[i][j]);
    }
  }

  PartitionMethod *partitionsMethods = malloc(6 * sizeof(PartitionMethod));

  for (int i = 0; i < quantity; i++) {
    initPartitionMethods(partitionsMethods);
    int *copy_HP = malloc(sizes[i] * sizeof(int));
    int *copy_HA = malloc(sizes[i] * sizeof(int));
    int *copy_HM = malloc(sizes[i] * sizeof(int));
    int *copy_LP = malloc(sizes[i] * sizeof(int));
    int *copy_LA = malloc(sizes[i] * sizeof(int));
    int *copy_LM = malloc(sizes[i] * sizeof(int));
    for (int j = 0; j < sizes[i]; j++) {
      copy_HP[j] = vectors[i][j];
      copy_HA[j] = vectors[i][j];
      copy_HM[j] = vectors[i][j];
      copy_LP[j] = vectors[i][j];
      copy_LA[j] = vectors[i][j];
      copy_LM[j] = vectors[i][j];
    }
    quick_sort_lomuto_default(copy_LP, 0, sizes[i] - 1, &partitionsMethods[0]);
    quick_sort_lomuto_median(copy_LM, 0, sizes[i] - 1, &partitionsMethods[1]);
    quick_sort_lomuto_random(copy_LA, 0, sizes[i] - 1, &partitionsMethods[2]);
    quick_sort_hoare_default(copy_HP, 0, sizes[i] - 1, &partitionsMethods[3]);
    quick_sort_hoare_median(copy_HM, 0, sizes[i] - 1, &partitionsMethods[4]);
    quick_sort_hoare_rand(copy_HA, 0, sizes[i] - 1, &partitionsMethods[5]);
    ordenacaomacaca(partitionsMethods);
    fprintf(output_file, "[%d]:", sizes[i]);
    for (int z = 0; z < 6; z++) {
      fprintf(output_file, "%s(%d),", partitionsMethods[z].method,
              partitionsMethods[z].count);
    }
    fprintf(output_file, "\n");
  }
  fclose(output_file);
  fclose(input_file);
  return 0;
}
