#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE* input_file;
FILE* output_file;

typedef struct {
  char* method[3];
  int count;
}PartitionMethod;

void printVec(int* vector, int size){
  for(int i = 0; i < size;i++ ){
    if(i+1<size){
      printf("%d, ",vector[i]);
    }else{
      printf("%d\n",vector[i]);
    }
  }
}

int lomuto_default(int* vector, int begin, int end) {
    int pivot = vector[end];
    int x = begin - 1;
    int swap = 0;

    for (int y = begin; y < end; y++) {
        if (vector[y] <= pivot) {
            x++;
            swap = vector[x];
            vector[x] = vector[y];
            vector[y] = swap;
        }
    }

    swap = vector[x + 1];
    vector[x + 1] = vector[end];
    vector[end] = swap;

    return x ;
}

int lomuto_median(int* vector, int begin, int end, int median){
    if (begin == end){
    return begin;
  }else{
    int pivot = lomuto_default(vector, begin, end);
    if(pivot - begin + 1 >= median) {
      return lomuto_median(vector,begin, pivot,median);
    }
    else{
      return lomuto_median(vector, pivot+1, end, median - (pivot - begin + 1));
    }
  }
 
}

int lomuto_rand(int* vector, int begin, int end){
  int swap = vector[end], r_index = begin + rand()%(end - begin +1);
  vector[end] = vector[r_index];
  vector[r_index] = swap;
  return lomuto_default(vector, begin,  end);
}



int hoare_default(int* vector, int begin, int end){
  int pivot = vector[begin], x = begin - 1, y = end + 1, swap = 0;
  while (1) {
    while (vector[--y] > pivot) {
    }
    while (vector[++x] < pivot) {
    }
    if(x<y){
      swap = vector[x];
      vector[x] = vector[y];
      vector[y] = swap;
    }else{
      return y;
    }
  }
}

int hoare_rand(int* vector, int begin, int end){
  int swap = vector[begin], r_index = begin + rand()%(end - begin +1);
  vector[begin] = vector[r_index];
  vector[r_index] = swap;
  return hoare_default(vector,begin, end);
}

int hoare_median(int* vector, int begin, int end, int median){
  if (begin == end){
    return begin;
  }else{
    int pivot = hoare_default(vector, begin, end);
    if(pivot - begin + 1 >= median) {
      return hoare_median(vector,begin, pivot,median);
    }
    else{
      return hoare_median(vector, pivot+1, end, median - (pivot - begin + 1));
    }
  }
}


void quick_sort(int* vector, int begin, int end){
  if(begin < end){
    // int pivot = hoare_default(vector, begin, end);
    int pivot = lomuto_median(vector, begin, end, (end - begin)/2);
    quick_sort(vector,begin,pivot);
    quick_sort(vector,pivot+1,end);
  }
}

int* generateVector(int size){
  srand(time(NULL));
  int* vector = malloc(size*sizeof(int));
  for(int i = 0; i < size; i++){
    vector[i] = rand() % 100;
  }
  return vector;
}


int main(int argc, char *argv[])
{
  char* file_out_path = argv[2];
  printf("%s\n",file_out_path);
  char* file_input_path = argv[1];
  printf("%s\n",file_input_path);
  input_file = fopen(file_input_path, "r");
  output_file = fopen(file_out_path, "w+");

  int quantity = 0;
  int size = 0;
  fscanf(input_file,"%d",&quantity);
  for(int i = 0; i < quantity; i++){
    fscanf(input_file,"%d", &size);
    int* vector = malloc(size*sizeof(int));
    for(int j = 0; j<size;j++){
      fscanf(input_file,"%d", &vector[j]);
    }
    free(vector);
  }
  
  fclose(output_file);
  fclose(input_file);
  return 0;
}
