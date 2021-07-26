/*
 * Problem 1 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ GIRISH MOHAN MADNANI ]
 * Student ID: [934130]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 600000
void maxheapify(int *, int, int);
int* buildmaxheap(int *, int);
void maxheapify2(int *, int, int);
int* buildmaxheap2(int *, int);

/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_1_a();
void problem_1_b();
void print_usage_and_exit(char **argv);

int main(int argc, char **argv) {
  if (argc != 2) {
    print_usage_and_exit(argv);
  }

  /* If the argument provided is "a" then run problem_1_a(),
   * run problem_1_b() for "b", and fail otherwise. */
  if (strcmp(argv[1], "a") == 0) {
    problem_1_a();
  } else if (strcmp(argv[1], "b") == 0) {
    problem_1_b();
  } else {
    print_usage_and_exit(argv);
  }

  return 0;
}

/* Print the usage information and exit the program. */
void print_usage_and_exit(char **argv) {
  fprintf(stderr, "usage: %s [ab]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* --- DO NOT CHANGE THE CODE ABOVE THIS LINE --- */

//building a max heap where it starts from half of the number of elements to 0.
int* buildmaxheap(int a[], int n){
    int heapsize = n;
    int j;
    for (j = n/2; j >= 0; j--) {
        maxheapify(a, j, heapsize);
    }
    return a;
}

//checking if the max heap has a larger number when inserted. In accordance to that positions are changed.
void maxheapify(int a[], int i, int heapsize){
    int temp, largest, left, right;
    left = (2*i+1);
    right = ((2*i)+2);
    if (left >= heapsize)
        return;
    else
    {
        if (left < (heapsize) && a[left] > a[i])
            largest = left;
        else
            largest = i;
        if (right < (heapsize) && a[right] > a[largest])
            largest = right;
        if (largest != i)
        {
            temp = a[i];
            a[i] = a[largest];
            a[largest] = temp;
            maxheapify(a, largest, heapsize);
        }
    }
}

//building a max heap where it starts from 0 to half of the number of elements.
int* buildmaxheap2(int a[], int n){
    int heapsize = n;
    int j;
    for (j = 0; j <= n/2; j++) {
        maxheapify2(a, j, heapsize);
    }
    return a;
}

//checking if the max heap has a larger number when inserted. In accordance to that positions are changed.
void maxheapify2(int a[], int i, int heapsize){
    int temp, left, right;
    left = (2*i+1);
    right = ((2*i)+2);

    if(a[left]>a[right])
    {
        temp=a[right];
        a[right]=a[left];
        a[left]=temp;
        maxheapify(a,left,heapsize);
    }
}


/* TODO: Implement your solution to Problem 1.a. in this function. */
void problem_1_a() {
    int i, t, n;
    int *a = calloc(MAX, sizeof(int)); //allocating memory to a pointer 'a' and initializing its values to 0
    int *m = calloc(MAX, sizeof(int)); //allocating memory to a pointer 'm  and initializing its values to 0
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    m = buildmaxheap(a, n);
    for (t = 0; t < n; t++) {
        printf("%d\n", m[t]);
    }
    return ;
}


/* TODO: Implement your solution to Problem 1.b. in this function. */
void problem_1_b() {
    int i, t, n;
    int *a = calloc(MAX, sizeof(int)); //allocating memory to a pointer and initializing its values to 0
    int *m = calloc(MAX, sizeof(int)); //allocating memory to a pointer and initializing its values to 0
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    m = buildmaxheap(a, n);
    m = buildmaxheap2(m,n);
    for (t = 0; t < n; t++) {
        printf("%d\n", m[t]);
    }
    return ;
}
