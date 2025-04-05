// Template allows this function to work with any data type (int, float, string, etc.)
#include <iostream>
#include <vector>
using namespace std;
template <class T>
void insertionSort(T data[], int n) {
    // Outer loop: Start from the second element (i=1) since the first is already "sorted"
    for (int i = 1, j; i < n; i++) {
        // Store the current element in 'tmp' (it may be overwritten during shifting)
        T tmp = data[i];

        // Inner loop: Compare 'tmp' with elements before it (from i-1 down to 0)
        // Shift elements to the right if they are greater than 'tmp'
        for (j = i; j > 0 && tmp < data[j-1]; j--) {
            data[j] = data[j-1];  // Move the larger element one position ahead
        }

        // Insert 'tmp' into its correct position (where the loop stopped)
        data[j] = tmp;
    }
}

template <class T>
void selectionSort(T data[], int n) {
    for (int i = 0, j, least; i < n-1; i++) {
        // Inner loop: Find the smallest element in unsorted portion
        for (j = i+1, least = i; j < n; j++) {
            if (data[j] < data[least]) {
                least = j;
            }
        }
        // Swap the smallest element into place
        swap(data[least], data[i]);
    }
}
template <class T>
void bubbleSort(T data[], int n) {
    for (int i = 0; i < n - 1; i++) {       // Outer loop: n-1 passes
 ////        bool swapped = false;
        // Early termination flag

        // for (int j = 0; j < n - 1 - i; j++ (enhanced)
        for (int j = n - 1; j > i; --j) {   // Inner loop: bubble up the smallest element
            if (data[j] < data[j - 1]) {    // Compare adjacent elements
                swap(data[j], data[j - 1]); // Swap if out of order
////            // Mark that a swap occurred
            }
        }
////        if (!swapped) break;                // Exit early if no swaps (array is sorted)
    }
}

// Merge two sorted subarrays A[left..mid] and A[mid+1..right]
void Merge(vector<int>& A, int left, int mid, int right) {
    int n1 = mid - left + 1;  // Size of left subarray
    int n2 = right - mid;     // Size of right subarray

    // Create temporary arrays
    vector<int> L(n1), R(n2);

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        L[i] = A[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[mid + 1 + j];

    // Merge the temp arrays back into A[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[] (if any)
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[] (if any)
    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

// Recursive Merge Sort function
void MergeSort(vector<int>& A, int left, int right) {
    if (left >= right) {
        return;  // Base case: subarray has 0 or 1 element
    }

    int mid = left + (right - left) / 2;  // Avoids overflow vs. (left+right)/2

    // Recursively sort the two halves
    MergeSort(A, left, mid);      // Sort left half
    MergeSort(A, mid + 1, right); // Sort right half

    // Merge the sorted halves
    Merge(A, left, mid, right);
}

//Quick sort
// Function to swap two elements by reference
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function
// Picks the first element as the pivot (arr[low])
// Rearranges the array so that all elements smaller than pivot are on the left,
// and all greater elements are on the right.
// Returns the correct position (index) of the pivot element after partitioning.
int partition(int arr[], int low, int high) {
    int pivot = arr[low];  // Choose the first element as pivot
    int i = low;           // i will track the position of the smaller element boundary

    // Traverse the rest of the array
    for (int j = low + 1; j <= high; j++) {
        // If current element is less than or equal to pivot
        if (arr[j] <= pivot) {
            i++;  // Increase the smaller element boundary
            swap(arr[i], arr[j]);  // Bring the smaller element to the front
        }
    }

    // Finally, place the pivot in its correct position
    swap(arr[i], arr[low]);

    return i;  // Return the partition index (final position of the pivot)
}

// Recursive Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array, and get the pivot index
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);  // Left of pivot
        quickSort(arr, pi + 1, high); // Right of pivot
    }
}
