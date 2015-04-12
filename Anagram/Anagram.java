/* Eeshan Londhe
 * Program to check if two strings are anagrams. Ignores case.
 */

import java.util.HashMap;

public class Anagram {

   public static void main(String[] args) {
      String s_1 = "listen";
      String s_2 = "silent";
      boolean isAnagram = anagram(s_1.toLowerCase(), s_2.toLowerCase()); // ignores case
      System.out.println("Are these strings anagrams?: " + isAnagram);
   }
   
   public static boolean anagram(String s_1, String s_2) {
      if (s_1.length() != s_2.length()) return false;
      HashMap<Character, Integer> s_1Counts = new HashMap<Character, Integer>();
      HashMap<Character, Integer> s_2Counts = new HashMap<Character, Integer>();
      for (int i = 0; i < s_1.length(); i++) { // puts all characters and counts for both strings
         char c = s_1.charAt(i);
         char c2 = s_2.charAt(i);
         if (!s_1Counts.containsKey(c)) {
            s_1Counts.put(c, 1);
         }
         if (!s_2Counts.containsKey(c2)) { 
            s_2Counts.put(c2, 1);
         }
         if (s_1Counts.containsKey(c)) {
            s_1Counts.put(c, s_1Counts.get(c) + 1);
         }
         if (s_2Counts.containsKey(c2)) {
            s_2Counts.put(c2, s_2Counts.get(c2) + 1);
         }
      }
      for (char c : s_1Counts.keySet()) {
         if (!s_2Counts.containsKey(c) || s_2Counts.get(c) != s_1Counts.get(c)) {
            return false;
         }
      }
      return true;
   }

}