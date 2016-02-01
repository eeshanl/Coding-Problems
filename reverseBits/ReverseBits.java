import java.util.*;

public class ReverseBits {

  public static void main(String[] args) {
    if (args.length != 1) {
      System.err.println("Please input 1 number as an argument.");
    } else {
      int num = Integer.parseInt(args[0]);
      System.out.println("The original number: " + num);
      System.out.println("The bit reversed number of " + num + ": " + reverseBits(num));
    }
  }

  // returns the bit reversed number of x
  public static int reverseBits(int x) {
    int y = x;
    Queue<Integer> q = new LinkedList<Integer>();
    for (int i = 0; i < 32; i++) {
      q.add(y & 0x1);
      y = y >> 1;
    }

    y = 0;
    while (!q.isEmpty()) {
      y = y << 1;
      y |= q.remove();
    }

    return y;
  }

}
