// Eeshan Londhe
// Program to find how many Stock Exchange Abbreviations, given in a file stocks.txt, have a unique
// integer value corresponding to numbers on a standard cell phone dial pad.

import java.util.*;
import java.io.*;

public class StockCheck {

   public static void main(String[] args) throws FileNotFoundException {
   	Scanner input = new Scanner(new File("stocks.txt"));
      int count = uniqueCount(input);
      System.out.println("Number of unique Stock abbreviations is: " + count);
   }
   
   public static int uniqueCount(Scanner input) {
      HashSet<String> numOfStr = new HashSet<String>();
      int count = 0;
      while(input.hasNextLine()) {
         total++;
         String line = input.nextLine().toLowerCase();
         String numOfLine = "";
         for (int i = 0; i < line.length(); i++) {
            char character = line.charAt(i);
            if (character == 'a' || character == 'b' || character == 'c') {
   		      numOfLine += "2";
   	      } else if (character == 'd' || character == 'e' || character == 'f') {
   		      numOfLine += "3";
   	      } else if (character == 'g' || character == 'h' || character == 'i') {
   		      numOfLine += "4";
   	      } else if (character == 'j' || character == 'k' || character == 'l') {
   		      numOfLine += "5";
   	      } else if (character == 'm' || character == 'n' || character == 'o') {
   		      numOfLine += "6";
   	      } else if (character == 'p' || character == 'q' || character == 'r' || character == 's') {
   		      numOfLine += "7";
   	      } else if (character == 't' || character == 'u' || character == 'v') {
   	      	numOfLine += "8";
   	      } else {
   		      numOfLine += "9";
   	      }
         }
         if(!numOfStr.contains(numOfLine)) {
            numOfStr.add(numOfLine);
            count++;
         }
      }
      return count;
   }

}