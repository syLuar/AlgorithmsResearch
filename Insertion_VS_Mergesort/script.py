import random
import copy
# Section 1: Testcase Generation Functions 

###### Section 1.1: Testcase Generator function
# Arguments: n -> int; 
# Returns: list of 1 to n (inclusive)
# Outputs: N/A
def testCaseGenerator(n):
    available_indices = list(range(n))
    res = [0] * n
    for i in range(n):
        insertIndex = random.choice(available_indices)
        available_indices.remove(insertIndex)
        res[insertIndex] = i + 1
    return res

###### Section 1.2: Testcase Generator unit-tester
# Arguments: arr -> list[int]; 
# Returns: True if duplicate found, False otherwise
# Output: Input array, if no duplicates found
def containsDuplicate(arr):
    dupe = set()
    for x in arr:
        if x in dupe:
            return True
        dupe.add(x)
    print(arr)
    return False

# Section 2: Sorting Functions
###### Both sort functions will modify the array IN-PLACE.

###### Section 2.1: Insertion Sort function
# Arguments: arr -> list[int]; 
# Returns: number of comparisons took to sort arr
# Outputs: N/A
def insertionSort(arr):
    comparisons = 0
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0:
            comparisons += 1 
            if key < arr[j]:
                arr[j + 1] = arr[j]
                j -= 1
            else:
                break
        arr[j + 1] = key
    return comparisons, arr

###### Section 2.1: Merge Sort function
# Arguments: arr -> list[int]; 
# Returns: number of comparisons took to sort arr
# Outputs: N/A
def mergeSort(arr):
    if len(arr) > 1:
        mid = len(arr)//2
        L = arr[:mid]
        R = arr[mid:]
        comparisons_l = mergeSort(L)
        comparisons_r = mergeSort(R)
        i = j = k = 0
        comparisons = comparisons_l + comparisons_r
        while i < len(L) and j < len(R):
            comparisons += 1
            if L[i] <= R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1
        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1   
        return comparisons
    return 0

def hybridSort(arr):
    comparisons = 0
    if len(arr) > 30:
        mid = len(arr)//2
        L = arr[:mid]
        R = arr[mid:]
        comparisons_l, L = hybridSort(L)
        comparisons_r, R = hybridSort(R)
        i = j = k = 0
        comparisons = comparisons_l + comparisons_r
        while i < len(L) and j < len(R):
            comparisons += 1
            if L[i] <= R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1
        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1   
        return comparisons, arr
    else:
        comparisons, arr = insertionSort(arr)
        
        return comparisons, arr


def main():
    ########################################
    ############ Test Phase 1: #############
    # Determining which power of 10 where
    # Insertion is better than Merge sort at

    # Generate the test arrays, in varying sizes up to 10^7

    #test_10_3_IS = testCaseGenerator(1000)
    #test_10_4_IS = testCaseGenerator(10000)
    #test_10_5_IS = testCaseGenerator(100000)
    test_10_6_IS = testCaseGenerator(1000000)
    # test_10_7_IS = testCaseGenerator(10000000)
    #comparisons, sortedArr = hybridSort(test_10_3_IS)
    #comparisons, sortedArr = hybridSort(test_10_6_IS)
    #print(comparisons)
    #print(sortedArr)

    
    file_object = open("1000000_case1.txt", "a")
    for i in test_10_6_IS:
        file_object.write(str(i)+ "\n")
    
    file_object.close()

    '''
    TestCaseArray = []
    with open('1000_case.txt') as f:
        TestCaseArray = f.read().splitlines()

    TestCaseArray = [int(i) for i in TestCaseArray]
    print(TestCaseArray)
    '''

    # We will use Deep-copy versions of these for the Merge sorts,
    # in order to ensure both sorts are judged by the same arrays
    # test_10_3_MS = copy.deepcopy(test_10_3_IS)
    # test_10_4_MS = copy.deepcopy(test_10_4_IS)
    # test_10_5_MS = copy.deepcopy(test_10_5_IS)
    # test_10_6_MS = copy.deepcopy(test_10_6_IS)
    # test_10_7_MS = copy.deepcopy(test_10_7_IS)

    # print("IS Comparisons")
    # print(insertionSort(test_10_3_IS))
    # print(insertionSort(test_10_4_IS))
    # print(insertionSort(test_10_5_IS))
    # print(insertionSort(test_10_6_IS))
    # print(insertionSort(test_10_7_IS))
    # print("MS Comparisons")
    # print(mergeSort(test_10_3_MS))
    # print(mergeSort(test_10_4_MS))
    # print(mergeSort(test_10_5_MS))
    # print(mergeSort(test_10_6_MS))
    # print(mergeSort(test_10_7_MS))
    print("test")

main()
