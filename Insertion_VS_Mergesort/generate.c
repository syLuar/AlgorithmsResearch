#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

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

int main(void)
{
    int *array = (int *)malloc(N*sizeof(int));

    for (int i = 0; i < N; i++) { //Fill in with no duplicates
        array[i] = i + 1;
    }

    srand(time(NULL));

    randomizer(array, N);

    FILE *f = fopen("100_case3.txt", "w");
    if(f == NULL) {
        perror("Error opening file");
        return 1;
    }

    for(int i=0; i< N; i++){
        fprintf(f, "%d", array[i]);
        if(i < N - 1){
            fprintf(f, "\n");
        }
    }

    fclose(f);

    return 0;

}