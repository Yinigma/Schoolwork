public class Q4 {
	public static String decimalToHex(String num) {
		int dec = 0;
		String res = "";
		boolean neg = false;
		try {
			dec = Integer.parseInt(num);
		} catch (NumberFormatException e) {
			return "Number format exception";
		}
		if (dec < 0) {
			dec = -dec;
			neg = true;
		}
		while (dec >= 16) {
			res = charCon(dec % 16) + res;
			dec /= 16;
		}
		res = charCon(dec) + res;
		if (neg) {
			res = "-" + res;
		}
		return res;
	}

	public static char charCon(int i) {
		if (i < 10) {
			return (char) ('0' + i);
		}
		char res = 'A';
		return (char) (res + i - 10);
	}
}
