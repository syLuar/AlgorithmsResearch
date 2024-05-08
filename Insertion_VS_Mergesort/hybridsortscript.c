#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1000000

void randomizer(int arr[], int n)
{
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        // Swap arr[i] and arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int merge(int arr[], int left[], int right[], int leftSize, int rightSize, long long int *comparisons) {
    int i = 0, j = 0, k = 0;
    
    while (i < leftSize && j < rightSize) {
        (*comparisons)++;
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < leftSize) {
        arr[k++] = left[i++];
    }

    while (j < rightSize) {
        arr[k++] = right[j++];
    }
    
    return k;
}

long long int mergeSort(int arr[], int size) {
    long long int comparisons = 0;
    if (size > 1) {
        int mid = size / 2;
        int *left = (int *)malloc(mid * sizeof(int));
        int *right = (int *)malloc((size - mid) * sizeof(int));

        if (left == NULL || right == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }

        for (int i = 0; i < mid; i++) {
            left[i] = arr[i];
        }
        for (int i = mid; i < size; i++) {
            right[i - mid] = arr[i];
        }

        long long int comparisons_l = mergeSort(left, mid);
        long long int comparisons_r = mergeSort(right, size - mid);
        
        comparisons += comparisons_l + comparisons_r;

        int k = merge(arr, left, right, mid, size - mid, &comparisons);

        free(left);
        free(right);

        return comparisons;
    }
    return 0;
}

long long int insertionSort(int arr[], int size) {
    long long int comparisons = 0;
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && key < arr[j]) {
            comparisons++;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return comparisons;
}

long long int hybridSort(int arr[], int size) {
    long long int comparisons = 0;
    if (size > 45) {
        int mid = size / 2;
        int *left = (int *)malloc(mid * sizeof(int));
        int *right = (int *)malloc((size - mid) * sizeof(int));

        if (left == NULL || right == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }

        for (int i = 0; i < mid; i++) {
            left[i] = arr[i];
        }
        for (int i = mid; i < size; i++) {
            right[i - mid] = arr[i];
        }

        long long int comparisons_l = hybridSort(left, mid);
        long long int comparisons_r = hybridSort(right, size - mid);

        comparisons += comparisons_l + comparisons_r;

        int k = merge(arr, left, right, mid, size - mid, &comparisons);

        free(left);
        free(right);
    } else {
        insertionSort(arr, size);
    }

    return comparisons;
}

int main() {
    int size = 10000; // Adjust the size as needed
    int *arr = (int *)malloc(size * sizeof(int));

    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    char temp[2];
    for (int fileNum=1; fileNum <= 3; fileNum++) {
        sprintf(temp, "%d", fileNum);
        char fileName[100] = "TestCases/10000_case";
        strcat(fileName, temp);
        strcat(fileName, ".txt");
        // printf("\n%s\n", fileName);
        FILE *file = fopen(fileName, "r");
        // Generate the test array
        for (int i = 0; i < size; i++) {
            fscanf(file, "%d", &arr[i]);
        }
        // for (int i=0; i<100; i++)
        //     printf("%d ", arr[i]);

        clock_t start_time, end_time;
        double cpu_time_used;

        start_time = clock();
        long long int comparisons = mergeSort(arr, size);
        end_time = clock();
        cpu_time_used = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000000;

        printf("Number of comparisons for file %d of array size %d: %lld\n", fileNum, size, comparisons);
        printf("Time taken: %lf ms.", cpu_time_used);
    }
    

    // Print the sorted array (if needed)

    free(arr);
    return 0;
}



// hybridsort(arr) 
// {
//    split arr into two evenly sized arrs, leftarr & rightarr
//    hybridsort(leftarr);
//    hybridsort(rightarr);
//    hybridMerge(leftarr, rightarr);
// }
// hybridMerge(leftarr, rightarr)
// {
//    if(arr.length <= S)
//    {
//       InsertionSort(arr)
//    }
//    else
//    {
//       merge(arr, left, right) // from Mergesort
//    }
// }

