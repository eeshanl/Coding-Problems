// Eeshan Londhe
// Testing code to check if my min heap works.


public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		PriorityQueue minHeap = new MinHeap();
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
		minHeap.insert(10);
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
		
	}

}
