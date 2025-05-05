//Assume we have two input and two output tapes to perform the sorting. The
//internal memory can hold and sort m records at a time. Write a program in java
//for external sorting. Find out time complexity.

// This program demonstrates Merge Sort, which is useful in external sorting.
// External sorting is used when data is too large to fit in memory (handled in chunks).

import java.io.*;
import java.util.*;

public class MergeSort {

    // Recursive function to divide the array and sort the subarrays
    public static void mergeSort(int[] array, int left, int right) {
        if (left < right) {
            // Find the middle point to divide the array into two halves
            int mid = left + (right - left) / 2;

            // Recursively sort the left half
            mergeSort(array, left, mid);

            // Recursively sort the right half
            mergeSort(array, mid + 1, right);

            // Merge the sorted halves
            merge(array, left, mid, right);
        }
    }

    // Function to merge two sorted subarrays into one sorted array
    public static void merge(int[] array, int left, int mid, int right) {
        // Sizes of the subarrays
        int n1 = mid - left + 1;
        int n2 = right - mid;

        // Temporary arrays for left and right subarrays
        int[] leftArray = new int[n1];
        int[] rightArray = new int[n2];

        // Copy data into temporary arrays
        for (int i = 0; i < n1; i++)
            leftArray[i] = array[left + i];
        for (int j = 0; j < n2; j++)
            rightArray[j] = array[mid + 1 + j];

        // Initial indexes for left, right, and merged subarrays
        int i = 0, j = 0, k = left;

        // Merge the temp arrays back into the original array
        while (i < n1 && j < n2) {
            if (leftArray[i] <= rightArray[j]) {
                array[k] = leftArray[i];
                i++;
            } else {
                array[k] = rightArray[j];
                j++;
            }
            k++;
        }

        // Copy remaining elements of leftArray (if any)
        while (i < n1) {
            array[k] = leftArray[i];
            i++;
            k++;
        }

        // Copy remaining elements of rightArray (if any)
        while (j < n2) {
            array[k] = rightArray[j];
            j++;
            k++;
        }
    }

    // Main method for input and output
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Read number of elements
        System.out.print("Enter the number of elements: ");
        int n = scanner.nextInt();

        // Read elements into the array
        int[] array = new int[n];
        System.out.println("Enter the elements of the array:");
        for (int i = 0; i < n; i++) {
            array[i] = scanner.nextInt();
        }

        // Display original array
        System.out.println("Original Array:");
        for (int num : array) {
            System.out.print(num + " ");
        }
        System.out.println();

        // Sort the array using Merge Sort
        mergeSort(array, 0, array.length - 1);

        // Display sorted array
        System.out.println("Sorted Array:");
        for (int num : array) {
            System.out.print(num + " ");
        }
        System.out.println();

        scanner.close(); // Close the scanner
    }
}
//time complexity:O(n logn)
