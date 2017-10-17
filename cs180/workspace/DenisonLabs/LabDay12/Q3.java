public class Q3 {
	public static int findGCD(int num1, int num2) {
		int least = Math.abs(num1);
		int greatest = Math.abs(num2);
		int GCD = 1;
		if (num1 == num2) {
			return num1;
		}
		if (num1 > num2) {
			least = num2;
			greatest = num1;
		}
		if (least == 0) {
			return greatest;
		}
		if (greatest % least == 0) {
			return least;
		}
		least /= 2;
		for (int i = 2; i < least; i++) {
			if (num1 % i == 0 && num2 % i == 0) {
				GCD = i;
			}
		}
		return GCD;
	}
}
