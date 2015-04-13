// Eeshan Londhe
// Removes duplicate items from a linkedlist and maintains order.

public class removeDups {

   public static void main(String[] args) {
      Node front = new Node(1);
      Node temp = front;
      temp.next = new Node(2);
      temp = temp.next;
      temp.next = new Node(3);
      temp = temp.next;
      temp.next = new Node(4);
      temp = temp.next;
      temp.next = new Node(4);
      temp = temp.next;
      temp.next = new Node(5);
      temp = temp.next;
      temp.next = new Node(2);
      temp = temp.next;
      temp.next = new Node(3);
      temp = temp.next;
      temp.next = new Node(5);
      temp = front;
      
      System.out.print("List with duplicates: ");
      printList(temp);
      removeDups(temp);
      System.out.print("\nList without duplicates: ");
      printList(temp);
   }
   
   // Solution with o(n^2) complexity with no auxilary storage
   //
   // Removes duplicate items from list and maintains order
   public static void removeDups(Node front) {
      if (front.next != null) {
         Node current = front;
         Node check = front;
         while(current != null) {
            while(check.next != null) {
               if (check.next.data == current.data) {
                  check.next = check.next.next;
               } else {
                  check = check.next;
               }
            }
            current = current.next;
            check = current;
         }
      }
   }
   
   // Prints the linkedlist in order
   public static void printList(Node front) {
      Node cur = front;
      System.out.print("[");
      while(cur.next != null) {
         System.out.print(cur.data + ", ");
         cur = cur.next;
      }
      System.out.println(cur.data + "]");
   }

}
