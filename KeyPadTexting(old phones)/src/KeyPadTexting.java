import java.util.*;

public class KeyPadTexting {

	public static void main(String[] args) {
		if (args.length == 0) {
			System.out.println("Input an argument");
		} else if (args.length > 1) {
			System.out.println("Input only 1 argument");
		} else {
			String str = args[0];
			keyPad(str);
		}
	}
	
	public static String keyPad(String input) {
		String str = "";
		String[] tokens = input.split("#");
		HashMap<Character, List<Character>> numberPad = new HashMap<Character, List<Character>>();
		
		numberPad.put('2', Arrays.asList('A', 'B', 'C'));
		numberPad.put('3', Arrays.asList('D', 'E', 'F'));
		numberPad.put('4', Arrays.asList('G', 'H', 'I'));
		numberPad.put('5', Arrays.asList('J', 'K', 'L'));
		numberPad.put('6', Arrays.asList('M', 'N', 'O'));
		numberPad.put('7', Arrays.asList('P', 'Q', 'R', 'S'));
		numberPad.put('8', Arrays.asList('T', 'U', 'V'));
		numberPad.put('9', Arrays.asList('W', 'X', 'Y', 'Z'));
		for (int i = 0; i < tokens.length; i++) {
			String s = tokens[i];
			ArrayList<Character> list = new ArrayList<Character>();
			for (int j = 0; j < s.length(); i++) {
				if (!list.contains(s.charAt(j))) {
					int size = list.size();
					if (list.get(0) == '7' || list.get(0) == '9') {
						int modAmount = size % 4;
						int numChars = 0;
						int index = 0;
						if (modAmount != 0) {
							index = (size % 4) - 1;
							numChars = size / 3;
							for (int k = 0; k < numChars; k++) {
								str += numberPad.get(list.get(0)).get(3);
							}
							str += numberPad.get(list.get(0)).get(index);
						} else {
							for (int k = 0; k < numChars; k++) {
								str += numberPad.get(list.get(0)).get(3);
							}
						}	
					} else {
						int modAmount = size % 3;
						int numChars = 0;
						int index = 0;
						if (modAmount != 0) {
							index = (size % 3) - 1;
							numChars = size / 3;
							for (int k = 0; k < numChars; k++) {
								str += numberPad.get(list.get(0)).get(2);
							}
							str += numberPad.get(list.get(0)).get(index);
						} else {
							for (int k = 0; k < numChars; k++) {
								str += numberPad.get(list.get(0)).get(2);
							}
						}	
					}
					list.clear();
				}
				list.add(s.charAt(j));
				
			}
		}
		return str;
	}
}