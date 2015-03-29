/* Eeshan Londhe
 * Program to check if a given string is a palindrome.
 */

public class Palindrome {
   
   public static void main (String[] args) {
      String pal = "racecar";
      System.out.println("Is palindrome?: " + isPal(pal));
   }
   
   public static boolean isPal(String s) {
      return isPal(s, 0, s.length() -1);
   }
   
   private static boolean isPal(String s, int i, int j) {
      if (i >= j) {
         return true;
      } else {
         if (s.charAt(i) == s.charAt(j)) {
            return true && isPal(s, i+1, j-1);
         } else {
            return false;
         }
      } 
   }
}