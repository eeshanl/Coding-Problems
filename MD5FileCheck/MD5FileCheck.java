// Eeshan Londhe
// Counts how many unique files there are by checking if both MD5 Hash code
// and file size is the same.

import java.io.*;
import java.util.*;

public class MD5FileCheck {

	public static void main(String[] args) throws FileNotFoundException {
			Scanner input = new Scanner(new File("file_data.txt"));
      int count = uniqueCounts(input);
      System.out.println("Number of unique files is: " + count);
	}

   public static int uniqueCounts(Scanner input) {
      HashSet<String> strSet = new HashSet<String>();
      int count = 0;
      while (input.hasNextLine()) {
         String line = input.nextLine();
         if (!strSet.contains(line)) {
            strSet.add(line);
            count++;
         }
      }
      return count;
   }
}
