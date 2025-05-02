#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>


int* a;/// pointer to the array
int len;/// length of the array

/////code of insertion  sort 
void insertionSort(int* arr,int start,int end) {
   
    for (int i=start;i<end;i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    
}

////code for sorting first half
void* SortFirstHalf(void* args){
    insertionSort(a,0,ceil(len/2))
    pthread_exit(NULL);
}

////////code for sorting seconf half
void* SortFirstHalf(void* args){
    insertionSort(a,ceil(len/2),len)
    pthread_exit(NULL);
}

/////code for merging the sub-array
void merge(int* arr) {
    int n1 = ceil(len/2);    
    int n2 = len-ceil(len/2);        


    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);

    pthread_exit(NULL);
}




int main(){

    ///getting  the array (length and the arrays element)
    printf("enter the array length:");
    scanf("%d",&len);
    a=(int*)malloc(len * sizeof(int));   

    printf("enter the array elements :");
    for(int i=0;i<len;i++){
        scanf("%d",(a+i));

    }
    /////////end of taking array

    pthread_t threads[3];

    pthread_create(&threads[0],NULL,SortFirstHalf,NULL);
    pthread_create(&threads[1],NULL,SortSecondHalf,NULL);

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);

    printf("each half is sorted successfully ");

    pthread_create($threads[2],NULL,merge,NULL);

    pthread_join(threads[2],NULL);




    free(a);
}




