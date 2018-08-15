#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXSIZE 1000

/* create a struct for every thread cycle, containing start line, 
end line and the number of cycle.*/
typedef struct Cycle {
  int start;
  int end;
  int id;
}Cycles;

/* the final result int array that contains the all line numbers that 
consists of the given number*/
int* result; // 
int index = 0;
int* content;
int number = 0;
int num_search;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void print(int* arr, int len) {
  for (int i = 0; i < len; i++) {
    printf("%d\n", arr[i]);
  }
}

//the process of searching the number for every thread. 
void search(void* pointer) {
  Cycles* cycle = (Cycles*) pointer;
  int start = cycle->start;
  int end = cycle->end;
  int* position = malloc(sizeof(int) * (end - start + 1));
  int tmp = 0;
  for(int i = start; i <= end; i++) {
     if (content[i] == num_search) {
      position[tmp++] = i + 1;
     }
  }
 
  if(pthread_mutex_lock(&mutex) != 0) {
    perror("pthread_mutex_lock");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < tmp; i++) {
    result[index++] = position[i];
  }
 
  if(pthread_mutex_unlock(&mutex) != 0) {
    perror("pthread_mutex_unlock");
    exit(EXIT_FAILURE);
  }
  free(position);
} 

//read the file
int read(char* file_name) {
  FILE *file;
  file = fopen(file_name, "r");
  if (file == NULL)
  {
    fprintf(stderr, "Error : Can't open the given file\n");   
    return 1;
  }
  char buffer[MAXSIZE];
  while (fgets(buffer, MAXSIZE, file) != NULL)
  {
    content[number++] = atoi(buffer);
  }
  fclose(file);
}

/* the main method that includes creating the multible threads by given numbers,
let all the threads starting the process of searching numbers, and finish the 
main methods until all the threads end.*/

int main(int argc, char *argv[]) {
  if( argc == 5 ) {
    char* file_name = argv[1];
    num_search = atoi(argv[2]);
    int threads_num = atoi(argv[3]);
    int size = atoi(argv[4]);

    content = (int*) malloc(size * 1024 * 1024);

    result = (int*) malloc(size * 1024 * 1024);
    
    if (read(file_name) == 1) {
      return 1;
    }

    int per_thread = number / threads_num;

    int rest = number % threads_num;
    
    pthread_t* thread = malloc(sizeof(pthread_t)*threads_num);

    int start = 0;
    int end = start + per_thread - 1;
    Cycles* cycle = malloc(sizeof(Cycles)*threads_num);;

    for (int i = 0; i < threads_num; i++) {
        while(rest > 0) {
          end++;
          rest--;
        }
        (cycle + i)->start = start;
        (cycle + i)->end = end;
        (cycle + i)->id = i;
        int ret = pthread_create(&thread[i], NULL, (void *)&search, 
          (void *) (cycle + i));
        if(ret != 0) {
            printf ("Create pthread error!\n");
            exit (1);
        }
        start = end + 1;
        end = start + per_thread - 1;
    }

   
    for (int i = 0; i < threads_num; i++) {
        pthread_join(thread[i], NULL);
    }

    print(result, index);
    free(thread);
    free(content);
    free(cycle);
    free(result);

  }
  else if( argc > 5) {
    printf("Too many arguments supplied.\n");
  }
  else {
    printf("One argument expected.\n");
  }
  return 0;
}



