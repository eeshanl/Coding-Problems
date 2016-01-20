// List of a few sorting algorithms ive coded

public class SortingAlgorithms {

   public static void main(String[] args) {
      /*int[] array = new int[5];
      array[0] = 5;
      array[1] = 4;
      array[2] = 1;
      array[3] = 2;
      array[4] = 3;
      selectionSort(array);
      for (int i = 0; i < array.length; i++) {
         System.out.println(array[i]);
      }*/
      int sum = 1;
      sum = -sum;
      System.out.println(sum);
      String x = "sdf";
      blah(x);
      System.out.println(x);
      
   }
   public static void blah(String x) {
      x = "abc";
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