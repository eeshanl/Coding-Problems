/** Eeshan Londhe
 * Testing code to test PQ implementations
 */

public class Test {

	public static void main(String[] args) {
		PriorityQueue linky = new PQLinkedList(); // PQ as linked list
		PriorityQueue minHeap = new PQLinkedList(); // PQ as min heap
		
		// heap
		System.out.println("HEAP:\n\n\n");
		System.out.println(minHeap);
		minHeap.insert(5);
		System.out.println(minHeap);
		minHeap.insert(2);
		System.out.println(minHeap);
		minHeap.insert(4);
		System.out.println(minHeap);
		minHeap.insert(1);
		System.out.println(minHeap);
		minHeap.insert(9);
		System.out.println(minHeap);
		minHeap.insert(7);
		System.out.println(minHeap);
		minHeap.insert(9);
		System.out.println(minHeap);
		minHeap.insert(5);
		System.out.println(minHeap);
		minHeap.deleteMin();
		System.out.println(minHeap);
		minHeap.deleteMin();
		System.out.println(minHeap);
		minHeap.deleteMin();
		System.out.println(minHeap);
		minHeap.deleteMin();
		System.out.println(minHeap);
		minHeap.deleteMin();
		System.out.println(minHeap);
		minHeap.deleteMin();
		System.out.println(minHeap);
		minHeap.deleteMin();
		System.out.println(minHeap);
		minHeap.deleteMin();
		System.out.println(minHeap);
		
		// linkedlist
		System.out.println("\n\n\nLinkedList:\n\n\n");
		System.out.println(linky);
		linky.insert(7);
		System.out.println(linky);
		linky.insert(5);
		System.out.println(linky);
		linky.insert(3);
		System.out.println(linky);
		linky.insert(7);
		System.out.println(linky);
		linky.insert(9);
		System.out.println(linky);
		linky.insert(23);
		System.out.println(linky);
		linky.insert(63);
		System.out.println(linky);
		linky.insert(4);
		System.out.println(linky);
		linky.insert(2);
		System.out.println(linky);
		linky.insert(5);
		System.out.println(linky);
		linky.insert(69);
		System.out.println(linky);
		linky.insert(36);
		System.out.println(linky);
		linky.deleteMin();
		System.out.println(linky);
		linky.deleteMin();
		System.out.println(linky);
		linky.deleteMin();
		System.out.println(linky);
		linky.deleteMin();
		System.out.println(linky);
		linky.deleteMin();
		System.out.println(linky);
		linky.deleteMin();
		System.out.println(linky);
		linky.deleteMin();
		System.out.println(linky);
		linky.deleteMin();
		System.out.println(linky);
		linky.deleteMin();
		System.out.println(linky);
		linky.deleteMin();
		System.out.println(linky);
		linky.deleteMin();
		System.out.println(linky);
		linky.deleteMin();
		System.out.println(linky);
	}

}
