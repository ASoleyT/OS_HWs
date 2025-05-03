#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int* a; // pointer to the array
int len; // length of the array

// insertion sort for a subarray
void insertionSort(int* arr, int start, int end) {
    for (int i = start; i < end; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= start && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// sorting first half
void* SortFirstHalf(void* args) {
    insertionSort(a, 0, ceil(len/2));
    pthread_exit(NULL);
}

// sorting second half
void* SortSecondHalf(void* args) {
    insertionSort(a, ceil(len/2), len);
    pthread_exit(NULL);
}

// merging two sorted halves
void* merge(void* args) {
    int l =0;
    int m = ceil(len/2)-1;
    int r = len - 1;

    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k++] = L[i++];
        } else {
            a[k++] = R[j++];
        }
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];

    free(L);
    free(R);
    pthread_exit(NULL);
}

int main() {
    printf("Enter the array length: ");
    scanf("%d", &len);
    a = (int*)malloc(len * sizeof(int));

    printf("Enter the array elements:\n");
    for (int i = 0; i < len; i++) {
        scanf("%d", &a[i]);
    }

    pthread_t threads[3];

    pthread_create(&threads[0], NULL, SortFirstHalf, NULL);
    pthread_create(&threads[1], NULL, SortSecondHalf, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    printf("Each half is sorted successfully.\n");

    pthread_create(&threads[2], NULL, merge, NULL);
    pthread_join(threads[2], NULL);

    printf("Final sorted array:\n");
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    free(a);
    return 0;
}
