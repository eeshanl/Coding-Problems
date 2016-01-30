public class MingoGame {

  public static void main(String[] args) {
	 Mingo m = new Mingo();
	 boolean mingo = m.mingoGame();
    if(mingo)
   	 System.out.println("Mingo! after " + m.calledList.size() + " calls.");
     else 
   	 System.out.println("No mingo");
  }
  
}
