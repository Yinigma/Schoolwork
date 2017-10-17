import java.util.Scanner;


/**
 * 
 * @author Ben "Kenobi" Denison
 * 
 * This is the math tools client for the fifth lab on 6/29/15
 * 
 * email: bdenison@purdue.edu fobjamin13@gmail.com
 * PUID: 0028399054
 *
 */

public class MathToolsClient {
	public static void main(String[] args){
		boolean notFinished = true;
		Scanner scan  = new Scanner(System.in);
		double uDub = 0;
		int uInt = 0;
		int choice = 0;
		MathTools m = new MathTools();
		do{
			System.out.println("Select a number from the menu choices:");
			System.out.println("1 - Absolute Value");
			System.out.println("2 - Power");
			System.out.println("3 - Scientific Notation");
			choice = m.getUInt(scan);
			switch(choice){
				case 1:
					System.out.println("Input a number you want to know the absolute value of");
					uDub = m.getUDub(scan);
					System.out.println("The absolute value of "+uDub+" is "+m.absoluteValue(uDub));
					break;
				case 2:
					System.out.println("Enter the base:");
					uDub = m.getUDub(scan);
					System.out.println("Enter the exponent:");
					uInt = m.getUInt(scan);
					System.out.printf("%f^%d=%f\n",uDub,uInt,m.power(uDub,uInt));
					break;
				case 3:
					System.out.println("***Scientific Notation***\n"
							+ "Input the number you want converted to scientific notation");
					uDub = m.getUDub(scan);
					System.out.println(m.scientificNotation(uDub));
					break;
				default:
					System.out.println("You dun guft.");
			}
			System.out.println("Do you wish to continue?(yes or no)");
			scan.nextLine();
			notFinished = m.yesNo(scan);
		}while(notFinished);
	}
}
