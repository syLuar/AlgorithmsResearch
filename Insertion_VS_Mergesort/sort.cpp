#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

#define S 5000

// # Section 1: Testcase Generation Functions 

// ###### Section 1.1: Testcase Generator function
// # Arguments: n -> int; 
// # Returns: array of 1 to n (inclusive)
// # Outputs: N/A

int* testCaseGenerator(int n) {
    int* test = new int[n];
    for (int i = 0; i < n; ++i) {
        test[i] = i + 1;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(test[i], test[j]);
    }

    return test;
}

// ###### Section 1.2: Testcase Generator unit-tester
// # Arguments: arr -> array of int; 
// # Returns: True if duplicate found, False otherwise
// # Output: Input array, if no duplicates found

bool containsDuplicate(const int* arr, int n) {
    std::unordered_set<int> dupe;

    for (int i = 0; i < n; ++i) {
        int x = arr[i];
        if (dupe.find(x) != dupe.end()) {
            return true;
        }
        dupe.insert(x);
    }

    return false;
}

// # Section 2: Sorting Functions
// ###### Both sort functions will modify the array IN-PLACE.

// ###### Section 2.1: Insertion Sort function
// # Arguments: arr -> array of int; 
// # Returns: number of comparisons took to sort arr
// # Outputs: N/A

long long insertionSort(int* arr, int n) {
    long long comparisons = 0;
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Initial comparison of last element of Sorted List
        // vs Key
        comparisons++;
        while (j >= 0 && key < arr[j]) {
            comparisons++;
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }

    return comparisons;
}

// ###### Section 2.2: Merge Sort function
// # Arguments: arr -> array of int; 
// # Returns: number of comparisons took to sort arr
// # Outputs: N/A

long long merge(int* arr, int left, int mid, int right) {
    long long comparisons = 0;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    comparisons++;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;

    return comparisons;
}

long long mergeSort(int* arr, int left, int right) {
    long long comparisons = 1;
    if (left < right) {
        int mid = left + (right - left) / 2;

        long long comparisons_l = mergeSort(arr, left, mid);
        long long comparisons_r = mergeSort(arr, mid + 1, right);

        comparisons += merge(arr, left, mid, right);

        comparisons += comparisons_l + comparisons_r;
    }
    return comparisons;
}

// # Section 3: Hybrid Sort
// This sort resorts to Insertion Sort below or equal S, and Merge Sort above S.

long long hybridSort(int *arr, int n) {
    if (n <= S) 
        return insertionSort(arr, n);
    return mergeSort(arr, 0, n-1);
}

int main() {
    int n = 25; // Change this to the desired array size (e.g., 1000, 10000, 100000, 1000000, 10000000)
    int* test_IS = testCaseGenerator(n);
    // for (int i = 0; i < n; i++) {
    //     std::cout << test_IS[i] << " ";
    // }
    // std::cout << containsDuplicate(test_IS, n);
   
    int *test_MS = new int[n];
    for (int i=0; i<n; i++) 
        test_MS[i] = test_IS[i];

    // // Insertion Sort
    long long insertion_comparisons = insertionSort(test_IS, n);

    // // Merge Sort
    int merge_comparisons = mergeSort(test_MS, 0, n - 1);

    std::cout << "Array Size: " << n << std::endl;
    std::cout << "Insertion Sort Comparisons: " << insertion_comparisons << std::endl;
    std::cout << "Merge Sort Comparisons: " << merge_comparisons << std::endl;

    delete[] test_IS;
    delete[] test_MS;

    return 0;
}
