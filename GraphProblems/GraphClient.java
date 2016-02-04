import java.util.*;

public class GraphClient {
  public static void main(String[] args) {
    Graph graph = new Graph(8);
    System.out.println("adjacencyList table: ");
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(1, 5);
    graph.addEdge(2, 6);
    graph.addEdge(3, 7);
    //graph.print();
    System.out.println();
    System.out.print("BFS Traversal: ");
    graph.printBFS(0);
    //System.out.print("DFS Traversal: ");
    //graph.printDFS(0);
  }

}
