/* Eeshan Londhe
 * Checks to see if a given string has all unique characters.
 * Used HashSet to make it O(n) time. Without use of data structure, time complexity would be O(n^2)
 */

import java.util.*;

public class IsUnique {
      
   public static void main(String[] args) {
      String str = "blah"; // Edit this string
      boolean unique = isUnique(str);
      System.out.println("Is this string unique?: " + unique);
   }
   
   
   public static boolean isUnique(String str) {
      HashSet<Character> uniqueSet = new HashSet<Character>();
      for (int i = 0; i < str.length(); i++) {
         if (!uniqueSet.contains(str.charAt(i))) {
            uniqueSet.add(str.charAt(i));
         } else {
            return false;   
         }
      }
      return true;
   }
   
}
