public class SwapLinkedList {
  public static void main(String[] args) {
    Node front = new Node(1);
    Node cur = front;
    cur.next = new Node(2);
    cur = cur.next;
    cur.next = new Node(3);
    cur = cur.next;
    cur.next = new Node(4);
    cur = cur.next;
    cur.next = new Node(5);
    cur = cur.next;
    cur.next = new Node(6);
    cur = cur.next;
    cur.next = new Node(7);
    cur = cur.next;
    cur.next = new Node(8);
    printLinkedList(front);
    front = swap(1, 5, front);
    printLinkedList(front);
  }

  public static Node swap(int x, int y, Node front) {
    if (front == null) {
      return null;
    }
    Node cur = front;
    Node xPtr = null;
    Node yPtr = null;
    Node xPrev = null;
    Node yPrev = null;
    Node xPost = null;
    Node yPost = null;
    int frontCase = 0; // 0 = no front, 1 x is front, 2 y is front
    if (x == front.data) {
      xPtr = front;
      frontCase = 1;
    } else if (y == front.data) {
      yPtr = front;
      frontCase = 2;
    }

    while (frontCase != 2 && cur != null && cur.next != null ) {
      if (cur.next.data == y) {
        yPtr = cur.next;
        yPrev = cur;
      }
      cur = cur.next;
    }

    cur = front;
    while (frontCase != 1 && cur != null && cur.next != null) {
      if (cur.next.data == x) {
        xPtr = cur.next;
        xPrev = cur;
      }
      cur = cur.next;
    }
    cur = front;
    xPost = xPtr.next;
    yPost = yPtr.next;
    xPtr.next = yPost;
    yPtr.next = xPost;
    if (frontCase == 1) { // x is front
      yPrev.next = xPtr;
      front = yPtr;
    } else if (frontCase == 2) { // y is front
      xPrev.next = yPtr;
      front = xPtr;
    } else {
      xPrev.next = yPtr;
      yPrev.next = xPtr;
    }
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
