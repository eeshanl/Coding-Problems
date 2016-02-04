import java.util.*;

public class Graph {
  private int numberOfNodes;
  private LinkedList<Integer>[] adjacencyList;

  public Graph(int numberOfNodes) {
    this.numberOfNodes = numberOfNodes;
    adjacencyList = new LinkedList[numberOfNodes];
    for (int i = 0; i < numberOfNodes; i++) {
      adjacencyList[i] = new LinkedList<Integer>();
    }
  }

  public void addEdge(int src, int dst) {
    if (src >= numberOfNodes || dst >= numberOfNodes) {
      throw new IllegalArgumentException("src and dst must be less than the value of numberOfNodes");
    }
    adjacencyList[src].add(dst);
  }

  public void printBFS(int node) {
    boolean[] visitedNodes = new boolean[numberOfNodes];
    Queue<Integer> q = new LinkedList<Integer>();

    visitedNodes[node] = true;
    q.add(node);
    while (!q.isEmpty()) {
      int num = q.remove();
      System.out.print(num + " ");

      for (int i = 0; i < adjacencyList[num].size(); i++) {

        int temp = adjacencyList[num].get(i);
        if (!visitedNodes[temp]) {
          visitedNodes[temp] = true;
          q.add(temp);
        }
      }
    }
    System.out.println();
  }

  public LinkedList<LinkedList<Integer>> printBottomUpBFS(int node) {
    LinkedList<LinkedList<Integer>> list = new LinkedList<LinkedList<Integer>>();
    boolean[] visitedNodes = new boolean[numberOfNodes];
    Queue<Integer> q = new LinkedList<Integer>();

    int index = 0;
    list.add(new LinkedList<Integer>());
    list.get(index).add(index);
    
    visitedNodes[node] = true;
    q.add(node);
    while (!q.isEmpty()) {
      int num = q.remove();

      for (int i = 0; i < adjacencyList[num].size(); i++) {
        int temp = adjacencyList[num].get(i);

        if (!visitedNodes[temp]) {
          visitedNodes[temp] = true;
          q.add(temp);
        }
      }
    }
    System.out.println();
    return list;
  }

  public void printDFS(int node) {
    boolean[] visitedNodes = new boolean[numberOfNodes];
    Stack<Integer> s = new Stack<Integer>();

    visitedNodes[node] = true;
    s.push(node);

    while (!s.isEmpty()) {
      int num = s.pop();
      System.out.print(num + " ");

      for (int i = 0; i < adjacencyList[num].size(); i++) {
        int temp = adjacencyList[num].get(i);
        if (!visitedNodes[temp]) {
          visitedNodes[temp] = true;
          s.push(temp);
        }
      }
    }
    System.out.println();
  }

  public void print() {
    for (int i = 0; i < numberOfNodes; i++) {
      System.out.print(i + ": ");
      for (int j = 0; j < adjacencyList[i].size(); j++) {
        if (j == adjacencyList[i].size() - 1) {
          System.out.print(adjacencyList[i].get(j));
        } else {
          System.out.print(adjacencyList[i].get(j) + ", ");
        }
      }
      System.out.println();
    }
  }


}
