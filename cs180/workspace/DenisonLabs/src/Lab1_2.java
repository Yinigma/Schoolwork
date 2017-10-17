/*
 * Lab 02
 * This program converts a user given temperature in Fahrenheit to Celsius.
 * Ben Denison
 */


import java.util.Scanner;

public class Lab1_2 {
	public static void main(String[] args){
		
		Scanner scan = new Scanner(System.in);
		float fTemp = 0;
		float cTemp = 0;
		
		System.out.println("Input the temperature in Fahrenheit.");
		fTemp = scan.nextFloat();
		cTemp = (fTemp-32)*5/9;
		System.out.printf("\n*************************************\n"
			+"Temperature in Fahrenheit:\t%.3f\n"
			+"Temperature in Celsius:\t\t%.3f", fTemp,cTemp);
	}
}
