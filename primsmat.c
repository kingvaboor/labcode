#include <stdio.h>
#include <string.h>

// Structure to represent an Employee
struct Employee
{
    char employee_name[50];
    int emp_no;
    double emp_salary;
};

// Function to perform the partition step of the QuickSort algorithm
int quickSort(struct Employee arr[], int low, int high, int *swapCount)
{
    int i = low - 1;
    struct Employee pivot = arr[high];

    // Traverse the array and rearrange elements around the pivot
    for (int j = low; j < high; j++)
    {
        if (arr[j].emp_no <= pivot.emp_no)
        {
            i++;

            // Swap arr[i] and arr[j]
            struct Employee temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            (*swapCount)++;
        }
    }

    // Swap arr[i + 1] and arr[high] (pivot)
    struct Employee temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    (*swapCount)++;

    return i + 1;
}

// Recursive function to perform QuickSort on the array
void quickSortRecursive(struct Employee arr[], int low, int high, int *swapCount)
{
    if (low < high)
    {
        // Get the partition index
        int pivotIndex = quickSort(arr, low, high, swapCount);

        // Recursively sort the subarrays on both sides of the pivot
        quickSortRecursive(arr, low, pivotIndex - 1, swapCount);
        quickSortRecursive(arr, pivotIndex + 1, high, swapCount);
    }
}

// Function to merge two subarrays in the MergeSort algorithm
void merge(struct Employee arr[], int left, int mid, int right, int *swapCount)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays to store the left and right subarrays
    struct Employee L[20], R[30];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge the temporary arrays back into the original array
    while (i < n1 && j < n2)
    {
        if (L[i].emp_no <= R[j].emp_no)
        {
            arr[k++] = L[i++];
        }
        else
        {
            // Merge operation with counting the number of swaps
            arr[k++] = R[j++];
            (*swapCount) += (mid - left + 1) - i;
        }
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

// Recursive function to perform MergeSort on the array
void mergeSortRecursive(struct Employee arr[], int left, int right, int *swapCount)
{
    if (left < right)
    {
        // Calculate mid point of array
        int mid = left + (right - left) / 2;

        // Recursively sort both halves
        mergeSortRecursive(arr, left, mid, swapCount);
        mergeSortRecursive(arr, mid + 1, right, swapCount);

        // Merge the sorted halves
        merge(arr, left, mid, right, swapCount);
    }
}

int main()
{
    int n;

    // Input: Number of employees
    printf("Enter the number of employees: ");
    scanf("%d", &n);

    // Array to store employee information
    struct Employee employees[30];

    // Input: Details for each employee
    for (int i = 0; i < n; i++)
    {
        printf("Enter details for Employee %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", employees[i].employee_name);
        printf("Employee Number: ");
        scanf("%d", &employees[i].emp_no);
        printf("Salary: ");
        scanf("%lf", &employees[i].emp_salary);
    }

    // Variables to store the number of swaps in each sorting algorithm
    int quickSwapCount = 0, mergeSwapCount = 0;

    // Perform QuickSort and display sorted array
    quickSortRecursive(employees, 0, n - 1, &quickSwapCount);
    printf("\nSorted array after Quick Sort:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s %d %.2lf\n", employees[i].employee_name, employees[i].emp_no, employees[i].emp_salary);
    }
    printf("Number of swaps in Quick Sort: %d\n", quickSwapCount);

    // Perform MergeSort and display sorted array
    mergeSortRecursive(employees, 0, n - 1, &mergeSwapCount);
    printf("\nSorted array after Merge Sort:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s %d %.2lf\n", employees[i].employee_name, employees[i].emp_no, employees[i].emp_salary);
    }
    printf("Number of swaps in Merge Sort: %d\n", mergeSwapCount);

    return 0;
}
