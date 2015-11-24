

public class SortingAlgorithms {

   public static void main(String[] args) {
      int[] array = new int[5];
      array[0] = 9;
      array[1] = 2;
      array[2] = 8;
      array[3] = 3;
      array[4] = 0;
      selectionSort(array);
      for (int i = 0; i < array.length; i++) {
         System.out.println(array[i]);
      }
      
   }
   
   // Selection sort O(n^2)
   public static void selectionSort(int[] array) {
      for (int i = 0; i < array.length - 1; i++) {
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