/** Eeshan Londhe
 *  PriorityQueue implemented with a Binary Min Heap
 */

public class MinHeap implements PriorityQueue {
	private int[] heap;
	private int size;

	public static final int DEFAULT_SIZE = 100;

    /**
     * Constructs new PQLinkedList object with default size
     *
     */
	public MinHeap() {
		this(DEFAULT_SIZE);
	}
	
    /**
     * Constructs new PQLinkedList object with size value passed in
     *
     */
	public MinHeap(int size) {
		this.heap = new int[size];
		this.size = 0;
	}

    /**
     * Returns true if priority queue has no elements
     *
     * @return true if the priority queue has no elements
     */
	public boolean isEmpty() {
		return this.size == 0;
	}

    /**
     * Returns the number of elements in this priority queue.
     *
     * @return the number of elements in this priority queue.
     */
	public int size() {
		return size;
	}

    /**
     * Returns the minimum element in the priority queue
     *
     * @return the minimum element
     * @throws EmptyPQException
     *             if priority queue contains no elements
     */
	public int findMin() {
		throwException();
		return heap[1];
	}

    /**
     * Inserts a new element into the priority queue. Duplicate values ARE
     * allowed.
     *
     * @param x
     *            element to be inserted into the priority queue.
     */
	public void insert(int x) {
		if (size == heap.length -1) {
			resize();
		}
		size++;
		int i = percolateUp(size, x);
		heap[i] = x;
	}

    /**
     * Removes and returns the minimum element from the priority queue.
     *
     * @return the minimum element
     * @throws EmptyPQException
     *             if priority queue contains no elements
     */
	public int deleteMin() {
		throwException();
		int min = heap[1];
		int hole = percolateDown(1,heap[size]);
		heap[hole] = heap[size];
		size--;
		return min;
	}

    /**
     * Resets the priority queue to appear as not containing any elements.
     */
	public void makeEmpty() {
		size = 0;
	}

    /**
     * percolate up
     */
	private int percolateUp(int hole, int val) {
		while (hole > 1 && val < heap[hole/2]) {
			heap[hole] = heap[hole/2];
			hole = hole / 2;
		}
		return hole;
	}

    /**
     * percolate down
     */
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

    /**
     * Resizes the array, by doubling size
     */
	private void resize() {
		int[] bigHeap = new int[heap.length*2];
		for (int i = 0; i < heap.length; i++) {
			bigHeap[i] = heap[i];
		}
		heap = bigHeap;
	}

    /**
     * Returns String array representation of PQ
     */
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
	
    /**
     * Throws EmptyPQException if PQ is empty
     */
    private void throwException() {
		if (isEmpty()) {
			throw new EmptyPQException();
		}
    }

}
