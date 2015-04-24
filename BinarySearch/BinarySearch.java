// Eeshan Londhe
// Binary search algorithm with O(log(n)) time complexity

public class BinarySearch {


	public static void main(String[] args) {
		int[] nums = {1,2,3,4,5,6,7,8,9};
		for (int i = 0; i < nums.length; i++) {
			System.out.println(binarySearch(nums, nums[i]) + " "); // should print 1 2 3 4 5 6 7 8 9
		}	
	}

	// binary search algorithm
	public static int binarySearch(int[] nums, int x) {
		return binarySearch(nums, x, 0, nums.length - 1);
	}

	// helper method for binary search
	private static int binarySearch(int[] nums, int x, int low, int high) {
		if (low > high) {
			return -1;
		}
		int mid = (low + high) / 2;
		if (nums[mid] == x) {
			return x;
		} else if (nums[mid] < x) {
			return binarySearch(nums, x, mid + 1, high);
		} else {
			return binarySearch(nums, x, low, mid - 1);
		}
	}

}