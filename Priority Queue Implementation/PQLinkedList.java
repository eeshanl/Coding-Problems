/* Eeshan Londhe
 * PriorityQueue implemented with a Linked List
 */

public class PQLinkedList {
	private Node front;
	private int size;

	// Private node class used for linked list.
	private class Node {
		private int data;
		private Node next;
		
		// constructs a new Node object
		public Node(int data) {
			this.data = data;
			this.next = null;
		}
	}
	
	// constructs a new PGLinkedList object
	public PQLinkedList() {
		front = null;
		this.size = 0;
	}
	
	
	// Returns true if the list is empty, false otherwise.
	public boolean isEmpty() {
		return front == null;
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
    	return front.data;
    }
    
    /**
     * *** TODO ***
     * 
     * 
     * Inserts a new element into the priority queue. Duplicate values ARE
     * allowed.
     *
     * @param x
     *            element to be inserted into the priority queue.
     */
    public void insert(int x) {
    	
    }

    /**
     * Removes and returns the minimum element from the priority queue.
     *
     * @return the minimum element
     * @throws EmptyPQException
     *             if priority queue contains no elements
     */
    public int deleteMin() {
    	int value = front.data;
    	front = front.next;
    	return value;
    }

    /**
     * Resets the priority queue to appear as not containing any elements.
     */
    public void makeEmpty() {
    	front = null;
    	size = 0;
    }

    /**
     * Returns String array representation of heap
     */
    public String toString() {
        Node cur = front;
        String str = "[";
        while(cur.next != null) {
        	str += cur.data + ", ";
        	cur = cur.next;
        }
        str += cur.data + "]";
        return str;
    }
	
}
