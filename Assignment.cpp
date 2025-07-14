#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm> // for sort
#include <time.h>
using namespace std;

// ------------------ COMMON FUNCTIONS ------------------
void generateRandomArray(int arr[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // consistent with 0-999 range
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// ------------------ MERGE SORT ------------------
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[100], R[100];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ------------------ QUICK SORT ------------------
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1, temp;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// ------------------ BINARY SEARCH ------------------
int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

// ------------------ EXPONENTIAL SEARCH ------------------
int exponentialSearch(int arr[], int size, int target) {
    if (size == 0) return -1;
    if (arr[0] == target) return 0;

    int i = 1;
    while (i < size && arr[i] <= target)
        i *= 2;

    // Binary search between i/2 and min(i, size - 1)
    int left = i / 2;
    int right = min(i, size - 1);
    return binarySearch(arr + left, right - left + 1, target) + left;
}

// ------------------ MAIN FUNCTION ------------------
int main() {
    int n, choice;
    cout << "Enter the number of elements: ";
    cin >> n;

    if (n <= 0 || n > 100) {
        cout << "Invalid size (must be 1-100).\n";
        return 1;
    }

    int arr[100];
    generateRandomArray(arr, n);

    cout << "\nOriginal Array:\n";
    printArray(arr, n);

    cout << "\nMain Menu:\n";
    cout << "1. Sorting\n";
    cout << "2. Searching\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int sortChoice;
            cout << "\nChoose Sorting Algorithm:\n";
            cout << "1. Merge Sort\n";
            cout << "2. Quick Sort\n";
            cout << "Enter your choice: ";
            cin >> sortChoice;

            switch (sortChoice) {
                case 1:
                    mergeSort(arr, 0, n - 1);
                    cout << "\nSorted using Merge Sort:\n";
                    printArray(arr, n);
                    break;
                case 2:
                    quickSort(arr, 0, n - 1);
                    cout << "\nSorted using Quick Sort:\n";
                    printArray(arr, n);
                    break;
                default:
                    cout << "Invalid sorting choice.\n";
            }
            break;
        }

        case 2: {
            // Ensure array is sorted before searching
            sort(arr, arr + n);
            cout << "\nSorted Array for Searching:\n";
            printArray(arr, n);

            int target;
            cout << "\nEnter the number to search: ";
            cin >> target;

            int searchChoice;
            cout << "\nChoose Search Algorithm:\n";
            cout << "1. Binary Search\n";
            cout << "2. Exponential Search\n";
            cout << "Enter your choice (1 or 2): ";
            cin >> searchChoice;

            int index = -1;
            if (searchChoice == 1) {
                index = binarySearch(arr, n, target);
            } else if (searchChoice == 2) {
                index = exponentialSearch(arr, n, target);
            } else {
                cout << "Invalid search choice.\n";
                return 1;
            }

            if (index != -1) {
                cout << "Element " << target << " found at index: " << index << endl;
            } else {
                cout << "Element " << target << " not found.\n";
            }
            break;
        }

        default:
            cout << "Invalid main menu choice.\n";
    }

    return 0;
}
