/**
 * 
 * @author Ben "Kenobi" Denison
 * PUID: 0028399054
 * email: bdenison@purdue.edu fobjamin13@gmail.com
 * 
 * This program calculates the amount of financial aid, if any, a student is eligible to receive based 
 * on if they're enrolled, if they've registered for the draft, if they have a valid residence, if they have a valid SSN
 * their age, their income, their parents' income, whether or not they are dependent, and their class standing. If you
 * ask me to do any more selection statements, then I will be pissed, otherwise I'm gonna go home.
 * 
 * 
 */


import java.util.Scanner;

public class FAFSAClient {
	
	public static boolean yesNo(Scanner scan){
		int b = -1;
		String yn = "";
		do{
			yn = scan.nextLine();
			if(yn.equalsIgnoreCase("yes")){
				b = 1;
			}
			else if(yn.equalsIgnoreCase("no")){
				b = 0;
			}
			else{
				System.out.println("It's a yes or no question. Good God, man.");
			}
		}while(b==-1);
		return (b==1);
	}
	
	public static void main(String[] args){
		Scanner scan = new Scanner(System.in);
		double parentIncome;
		boolean selecServ;
		 
		System.out.println("Have you been accepted into a degree or certificate program?");
		boolean accepted = FAFSAClient.yesNo(scan);
		System.out.println("What is your age?");
		int age = scan.nextInt();scan.nextLine();
		if(age>=18&&age<=25){
			System.out.println("Have you registered for selective service?");
			selecServ = FAFSAClient.yesNo(scan);
		}
		else{
			selecServ = true;
		}
		System.out.println("Do you have a valid social security number?");
		boolean hasSSN = FAFSAClient.yesNo(scan);
		System.out.println("Do you have a valid residency status?");
		boolean resStatus = FAFSAClient.yesNo(scan);
		System.out.println("Are you a dependent?");
		boolean dependent = FAFSAClient.yesNo(scan);
		if(dependent){
			System.out.println("What is your parent(s)' income?");
			parentIncome = scan.nextDouble();
		}
		else{
			parentIncome = 0.00;
		}
		System.out.println("What is your income?");
		double studentIncome = scan.nextDouble();
		System.out.println("How many credit hours are you taking?");
		int credHours = scan.nextInt();
		scan.nextLine();
		System.out.println("What is your class standing?");
		String classStanding = scan.nextLine();
		FAFSA f = new FAFSA(accepted,selecServ,hasSSN,resStatus,dependent,age,credHours,parentIncome,studentIncome,
				classStanding);
		System.out.println("Estimated total federal aid award: $" + f.calcFederalAidAmount());
	}
	
}
