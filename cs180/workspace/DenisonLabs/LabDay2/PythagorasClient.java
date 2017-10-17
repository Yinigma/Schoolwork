
/**
 * Lab Day 2
 * 
 * This class is meant to test the getHypotenuse() method of the Pythogoras class
 * 
 * Ben Denison bdenison@purdue.edu 
 */

import java.util.Scanner;

public class PythagorasClient {
	public static void main(String[] args){
		int i = 0;
		System.out.println(++i<1);
		Pythagoras p = new Pythagoras();
		Scanner scan = new Scanner(System.in);
		System.out.print("Input an integer for the length of the first side\n");
		int a = scan.nextInt();
		System.out.print("Input an integer for the length of the second side\n");
		int b = scan.nextInt();
		double hypotenuse = p.getHypotenuse(a, b);
		System.out.printf("side a: %d\n",a);
		System.out.printf("side b: %d\n",b);
		System.out.printf("hypotenuse: %.3f",hypotenuse);
	}
}
