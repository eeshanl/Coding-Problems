public class ReverseLinkedList {
   
   public static void main(String[] args) {
      Node front = new Node(1);
      front.next = new Node(2);
      front.next.next = new Node(3);
      front.next.next.next = new Node(4);
      System.out.println("<------ Original List ------>");
      printLinkedList(front);
      System.out.println();
      front = reverseList(front);
      System.out.println("<------ Reversed List ------>");
      printLinkedList(front);
      System.out.println();
   }
   
   // Reversing a linkedlist
   public static Node reverseList(Node front) {
      Node current = front;
      Node previous = null;
      while(current != null) { 
         Node cur2 = current.next;
         current.next = previous;
         previous = current;
         current = cur2;
      }
      front = previous;
      return front;
   }
   
   public static void printLinkedList(Node cur) {
      System.out.print("front -> ");
      while (cur != null && cur.next != null) {
         System.out.print("[" + cur.data + "]" + " -> ");
         cur = cur.next;
      }
      System.out.println("["+ cur.data + "]");
   }

}