import java.util.InputMismatchException;
import java.util.Scanner;
import java.math.RoundingMode;
import java.text.DecimalFormat;

/**
 * 
 * @author Ben "Kenobi" Denison
 * 
 * This is the math tools class for the fifth lab on 6/29/15
 * ...I can't believe I had to deal with decimal format crap to get this to work...
 * 
 * email: bdenison@purdue.edu fobjamin13@gmail.com
 * PUID: 0028399054
 *
 */

public class MathTools {
	
	public static final DecimalFormat f = new DecimalFormat("#.0#####");
	
	public static double absoluteValue(double n){
		if(n<0){
			return -n;
		}
		else{
			return n;
		}
	}
	public static double power(double base, int exp){
		if(exp<0){
			base = 1/base;
			exp = -exp;
		}
		double res = 1;
		for(int i = 0; i<exp; i++){
			res *= base;
		}
		return res;
	}
	public static String scientificNotation(double d){
		f.setRoundingMode(RoundingMode.DOWN);
		String sciNote = "";
		int expCount = 0;
		boolean n = (d<0);
		d = absoluteValue(d);
		if(d>1){
			while(d>=10){
				d/=10; 
				expCount++;
			}
		}
		else{
			while(d<1){
				d*=10;
				expCount--;
			}
		}
		if(n){
			sciNote=" x 10 ^ "+expCount;
			return "-"+f.format(d)+sciNote;
		}
		else{
			sciNote=" x 10 ^ "+expCount;
			return f.format(d)+sciNote;
		}
	}
	public static double getUDub(Scanner scan){
		double d = 0;
		try{
			d = scan.nextDouble();
		}
		catch(InputMismatchException e){
			System.out.println("Input a number. C'mon, it's not that hard.");
			scan.nextLine();
			d = getUDub(scan);
		}
		return d;
	}
	public static int getUInt(Scanner scan){
		int i = 0;
		try{
			i = scan.nextInt();
		}
		catch(InputMismatchException e){
			System.out.println("Input a number. C'mon, it's not that hard.");
			scan.nextLine();
			i = getUInt(scan);
		}
		return i;
	}
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
	
}
