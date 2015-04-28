/* Eeshan Londhe
 * PriorityQueue implemented with a Binary Min Heap
 */


public class MinHeap implements PriorityQueue {
	private int[] heap;
	private int size;
	
	public static final int DEFAULT_SIZE = 1000;
	
	public MinHeap() {
		this.heap = new int[DEFAULT_SIZE];
		this.size = 0;
	}
	
	public boolean isEmpty() {
		return this.size == 0;
	}

	public int size() {
		return size;
	}

	public int findMin() {
		return heap[1];
	}

	public void insert(int x) {
		if (size == heap.length -1) {
			resize();
		}
		size++;
		int i = percolateUp(size, x);
		heap[i] = x;
	}

	// TODO
	public int deleteMin() {
		if (isEmpty()) {
			throw new EmptyPQException();
		}
		return 0;
	}

	public void makeEmpty() {
		heap = new int[DEFAULT_SIZE];
	}
	
	private int percolateUp(int hole, int val) {
		while (hole > 1 && val < heap[hole/2]) {
			heap[hole] = heap[hole/2];
			hole = hole / 2;
		}
		return hole;
	}
	
	// TODO
	private int percolateDown(int hole, int val) {
		return hole;
	}
	
	private void resize() {
		int[] bigHeap = new int[(size - 1)*2];
		for (int i = 0; i < heap.length; i++) {
			bigHeap[i] = heap[i];
		}
		heap = bigHeap;
	}

}
