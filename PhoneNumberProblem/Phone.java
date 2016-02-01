public class Phone {

  private static String digits = "0134568";
  private static int numLength;

  public static void main(String[] args) {
    printPhoneNums(4);
  }

  public static void printPhoneNums(int length) {
    numLength = length;
    printPhoneNums("");
  }

  private static void printPhoneNums(String prefix) {
    if(prefix.length() == numLength){
			System.out.println(prefix);
			return;
		}

		for(int i = 0; i < digits.length(); i++){
			if(prefix.length() > 0) {
				if(prefix.charAt(prefix.length()-1) == digits.charAt(i))
					continue;
				if(prefix.length() > 0 && digits.charAt(i) == '4' && prefix.charAt(0) != '4')
					continue;
			}
			printPhoneNums(prefix + digits.charAt(i));
		}
  }

}
