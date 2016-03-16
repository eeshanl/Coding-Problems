// List of a few sorting algorithms ive coded

public class SortingAlgorithms {

   public static void main(String[] args) {
      int[] array = new int[10];
      array[0] = 5;
      array[1] = 4;
      array[2] = 1;
      array[3] = 2;
      array[4] = 3;
      array[5] = 2;
      array[6] = 88;
      array[7] = 12;
      array[8] = 33;
      array[9] = 9;

      quickSort(array, 0, array.length - 1);
      for (int i = 0; i < array.length; i++) {
         System.out.println(array[i]);
      }
      
   }
   
   public static void quickSort(int[] array, int lowerIndex, int higherIndex) {
      int i = lowerIndex;
      int j = higherIndex;
      int pivot = array[lowerIndex+(higherIndex-lowerIndex)/2];
      while (i <= j) {
      
         while (array[i] < pivot)
            i++;
         
         while (array[j] > pivot)
            j--;
            
         //swap values at index i and j
         if (i <= j) {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
         }
         
      }
      if (lowerIndex < j) 
         quickSort(array, lowerIndex, j);
      if (higherIndex > i)   
         quickSort(array, i, higherIndex);
   }
   
   // Selection sort O(n^2)
   public static void selectionSort(int[] array) {
      for (int i = 0; i < array.length; i++) {
         int min = i;
         for (int j = i + 1; j < array.length; j++) {
            if (array[j] < array[min]) {
               min = j;
            }
         }
         int temp = array[i];
         array[i] = array[min];
         array[min] = temp;
      }
   }

}