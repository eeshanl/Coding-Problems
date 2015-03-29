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
      temp.next = new Node(2);
      temp = front;
      System.out.print("List with duplicates: ");
      printList(temp);
      removeDups(temp);
      System.out.print("\nList without duplicates: ");
      printList(temp);
   }
   
   public static void removeDups(Node front) {
      Node current = front;
      while (current != null) {
         current = current.next;
      }
   }
   
   public static void printList(Node front) {
      Node cur = front;
      System.out.print("[");
      while (cur.next.next != null) {
         System.out.print(cur.data + ", ");
         cur = cur.next;
      }
      System.out.println(cur.next.data + "]");
   }

}