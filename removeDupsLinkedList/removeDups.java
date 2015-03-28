public class removeDups {

   public static void main(String[] args) {
      Node front = new Node(1);
      Node temp = front;
      front.next = new Node(2);
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
      printList(temp);
      removeDups(temp);
      printList(temp);
   }
   
   public static void removeDups(Node front) {
      
   }
   
   public static void printList(Node front) {
   
   }

}