import java.util.ArrayList;
import java.util.Random;

public class Mingo {
		private int[][] matrix;
		private ArrayList<Integer> numList;
		public ArrayList<Integer> calledList;
		
		public Mingo() {
			matrix = new int[100][100];
			numList = new ArrayList<Integer>();
			calledList = new ArrayList<Integer>();
			Random r = new Random();
			for (int i = 0; i < matrix.length; i++) {
				for (int j = 0; j < matrix.length; j++) {
					matrix[i][j] = (r.nextInt() + 1) % 100;
				}
			}
			for (int i = 0; i < 1000000; i++) {
				numList.add((r.nextInt() + 1) % 100);
			}
		}
		
		public boolean mingoGame() {
			boolean mingo = false;
		   for (int i = 0; i < this.numList.size(); i++) {
			  calledList.add(this.numList.get(i));
			  if (calledList.size() >= matrix.length) {
				  for (int j = 0; j < matrix.length; j++) {
					  mingo = checkRow(j);
					  mingo = checkColumn(j);
				  }
				  mingo = checkDiagnal1();
				  mingo = checkDiagnal2();
				  if(mingo) {
					  return mingo;
				  }
			  }
		  }
		  return mingo;
		}
		
		private boolean checkRow(int row) {
			  if (calledList.size() < matrix.length) {
				  return false;
			  }
			  for (int i = 0; i < matrix.length; i++) {
				  if (!calledList.contains(matrix[row][i])) {
					  return false;
				  }
			  }
			  return true;
		  }
		  
		  private boolean checkColumn(int col) {
			  if (calledList.size() < matrix.length) {
				  return false;
			  }
			  for (int i = 0; i < matrix.length; i++) {
				  if (!calledList.contains(matrix[i][col])) {
					  return false;
				  }
			  }
			  return true;
		  }
		  
		  private boolean checkDiagnal1() {
			  for (int i = 0; i < matrix.length; i++) {
				  if (!calledList.contains(matrix[i][i])) {
					  return false;
				  }
			  }
			  return true;
		  }
		  
		  private boolean checkDiagnal2() {
			  for (int i = 0; i < matrix.length; i++) {
				  if (!calledList.contains(matrix[matrix.length - 1 - i][i])) {
					  return false;
				  }
			  }
			  return true;
		  }
	}