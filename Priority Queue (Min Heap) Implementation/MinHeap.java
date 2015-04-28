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
	
	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		return this.size == 0;
	}

	@Override
	public int size() {
		// TODO Auto-generated method stub
		return size;
	}

	@Override
	public int findMin() {
		// TODO Auto-generated method stub
		return heap[1];
	}

	@Override
	public void insert(int x) {
		// TODO Auto-generated method stub
		if (size == heap.length -1) {
			resize();
		}
		size++;
		int i = percolateUp(size, x);
		heap[i] = x;
	}

	@Override
	public int deleteMin() {
		// TODO Auto-generated method stub
		if (isEmpty()) {
			throw new EmptyPQException();
		}
		return 0;
	}

	@Override
	public void makeEmpty() {
		// TODO Auto-generated method stub
		heap = new int[DEFAULT_SIZE];
	}
	
	private int percolateUp(int hole, int val) {
		while (hole > 1 && val < heap[hole/2]) {
			heap[hole] = heap[hole/2];
			hole = hole / 2;
		}
		return hole;
	}
	
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
