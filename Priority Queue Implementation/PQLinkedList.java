/** Eeshan Londhe
 *  PriorityQueue implemented with a Linked List
 */

public class PQLinkedList implements PriorityQueue {
	private Node front;
	private int size;

    /**
     * Private node class used for linked list.
     */
	private class Node {
		private int data;
		private Node next;
		
	    /**
	     * Constructs new Node object
	     *
	     */
		public Node(int data) {
			this.data = data;
			this.next = null;
		}
	}
	
    /**
     * Constructs new PQLinkedList object
     *
     */
	public PQLinkedList() {
		front = null;
		this.size = 0;
	}
	
	
    /**
     * Returns true if priority queue has no elements
     *
     * @return true if the priority queue has no elements
     */
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
		if (isEmpty()) {
			throw new EmptyPQException();
		}
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
    	Node newNode = new Node(x);
    	if (front == null) {
    		front = newNode;
    	} else {
			if (front.data > x) {
				Node temp = front;
				front = newNode;
				front.next = temp;
			} else {
	    		Node current = front.next;
	    		Node prev = front;
	    		while (current != null && x > current.data) {
	    			prev = prev.next;
	    			current = current.next;
	    		}
	    		prev.next = newNode;
	    		newNode.next = current;
			}
		}
    	size++;
    }

    /**
     * Removes and returns the minimum element from the priority queue.
     *
     * @return the minimum element
     * @throws EmptyPQException
     *             if priority queue contains no elements
     */
    public int deleteMin() {
		if (isEmpty()) {
			throw new EmptyPQException();
		}
		size--;
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
     * Returns String array representation of PQ
     */
    public String toString() {
        if (front == null) {
        	return "[]";
        }
        Node cur = front;
        String str = "[";
        while(cur != null) {
        	if(cur.next != null) {
        		str += cur.data + ", ";
        	} else {
        		str += cur.data + "]";
        	}
        	cur = cur.next;
        }
        return str;
    }
	
}
