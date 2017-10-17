import java.util.Scanner;

public class StringManipulator {
	
	public static String getName(Scanner scan){
		String name = "";
		boolean b = false; 
		do{
			System.out.println("Enter both your first and last name separated by a space.");
			name = scan.nextLine();
			b = testName(name);
		}while(!b);
		
		return name;
	}
	
	public static boolean testName(String s){
		boolean b = true;
		int dex = s.indexOf(" ");
		if(s==null||dex==-1||s.substring(dex+1).isEmpty()){
			b = false;
		}
		return b;
	}
	
	public static String makeUsername(String s){
		int dex = s.indexOf(" ");
		String fInit = s.substring(0,1);
		String lName = s.substring(dex+1);
		fInit = fInit.toLowerCase();
		lName = lName.toLowerCase();
		return fInit+lName;
	}
	
	public static String makeEmail(String s, String d){
		return s+d;
	}
	
	public static void main(String[] args){
		
		Scanner scan  = new Scanner(System.in);
		String name = getName(scan);
		String username = makeUsername(name);
		String email = makeEmail(username,"@purdue.edu");
		System.out.println("username: "+username+", email: "+email);
		
	}
}
