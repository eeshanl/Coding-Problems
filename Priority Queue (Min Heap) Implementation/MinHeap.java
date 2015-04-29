/* Eeshan Londhe
 * PriorityQueue implemented with a Binary Min Heap
 */

public class MinHeap implements PriorityQueue {
	private int[] heap;
	private int size;

	public static final int DEFAULT_SIZE = 100;

	// Constructs new MinHeap object
	public MinHeap() {
		this(DEFAULT_SIZE);
	}
	
	public MinHeap(int size) {
		this.heap = new int[size];
		this.size = 0;
	}

	// Returns true if minheap is empty, false otherwise.
	public boolean isEmpty() {
		return this.size == 0;
	}

	// returns the number of contents in the heap
	public int size() {
		return size;
	}

	// returns the minimum value in the heap
	public int findMin() {
		return heap[1];
	}

	// inserts the value passed into the heap
	public void insert(int x) {
		if (size == heap.length -1) {
			resize();
		}
		size++;
		int i = percolateUp(size, x);
		heap[i] = x;
	}

	// deletes the minimum value from the heap
	public int deleteMin() {
		if (isEmpty()) {
			throw new EmptyPQException();
		}
		int min = heap[1];
		int hole = percolateDown(1,heap[size]);
		heap[hole] = heap[size];
		size--;
		return min;
	}

	// makes the heap empty, contains 0 elements
	public void makeEmpty() {
		size = 0;
	}

	// percolate up
	private int percolateUp(int hole, int val) {
		while (hole > 1 && val < heap[hole/2]) {
			heap[hole] = heap[hole/2];
			hole = hole / 2;
		}
		return hole;
	}

	// percolate down
	private int percolateDown(int hole, int val) {
		while (2*hole <= size) {
			int left = 2*hole;
			int right = left + 1;
			int target = 0;
			if (right > size || heap[left] < heap[right]) {
				target = left;
			} else {
				target = right;
			}
			if (heap[target] < val) {
				heap[hole] = heap[target];
				hole = target;
			} else {
				break;
			}
		}
		return hole;
	}

	// resizes the array by doubling size
	private void resize() {
		int[] bigHeap = new int[heap.length*2];
		for (int i = 0; i < heap.length; i++) {
			bigHeap[i] = heap[i];
		}
		heap = bigHeap;
	}

	// returns String representing array of heap
	public String toString() {
		String str = "[";
		for (int i = 1; i < size; i++) {
			str += heap[i] + ", ";
		}
		if (isEmpty()) {
			str += "]";
		} else {
			str += heap[size] + "]";
		}
		return str;
	}

}
