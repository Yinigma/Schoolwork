/**
 * CS 180 - Lab 07 - CollegeFeeCalculator
 * 
 * @author Ben "Kenobi" Denison bdenison@purdue.edu
 * 
 * This is the collegefeecalculator from lab seven. It's pretty butt-ugly, and I'm sorry about that.
 */

import java.util.InputMismatchException;
import java.util.Scanner;

import javax.swing.JOptionPane;

public class CollegeFeeCalculator {

	public static final int FULL = 0;
	public static final int PART = 1;
	public static final int IN = 0;
	public static final int OUT = 1;
	public static final int INTER = 2;
	public static final int EARHART = 0;
	public static final int HILL = 1;
	public static final int OWEN = 2;
	public static final int WINDSOR = 3;
	public static final int ON = 0;
	public static final int OFF = 1;
	public static final String[] RESARR = new String[] { "In-state",
			"Out-of-State", "International" };
	public static final String[] HOUSEARR = new String[] { "On-campus",
			"Off-campus" };
	public static final String[] HALLARR = new String[] { "Earhart",
			"Hillenbrand", "Owen", "Windsor" };

	public static int calcTuition(int enroll, int res, int cred) {
		int partTotal = 1;
		if (enroll == FULL) {
			if (res == IN) {
				return 4996;
			} else if (res == OUT) {
				return 14397;
			} else if (res == INTER) {
				return 15397;
			} else {
				return -1;
			}
		} else if (enroll == PART) {
			if (res == IN) {
				partTotal = 350;
			} else if (res == OUT) {
				partTotal = 950;
			} else if (res == INTER) {
				partTotal = 1020;
			} else {
				return -1;
			}
			return partTotal * cred;
		} else {
			return -1;
		}
	}

	public static int calcHousing(int house, int hall) {
		if (house == ON) {
			switch (hall) {
			case EARHART:
				return 4745;
			case HILL:
				return 5307;
			case OWEN:
				return 4130;
			case WINDSOR:
				return 4150;
			default:
				return -1;
			}
		} else if (house == OFF) {
			return 0;
		} else {
			return -1;
		}
	}

	public static int protectedParse(String s) {
		int i = 0;
		try {
			i = Integer.parseInt(s);
			return i;
		} catch (NumberFormatException e) {
			return -1;
		}
	}

	public static int arrLookup(String s, String[] a) {
		int dex = -1;
		for (int i = 0; i < a.length; i++) {
			if (a[i].equals(s)) {
				dex = i;
			}
		}
		return dex;
	}

	public static String checkNull(String s) {
		if (s == null) {
			return "null";
		} else {
			return s;
		}
	}

	public static String finString(String name, int cred, int enroll, int res,
			int house, int hall) {
		name = checkNull(name);
		int tut = calcTuition(enroll, res, cred);
		int housing = calcHousing(house, hall);
		int total = tut + housing;
		String residence = "";
		String e = "null";
		if (enroll == PART) {
			e = "Part-time";
		} else if (enroll == FULL) {
			e = "Full-time";
		}
		try {
			residence = RESARR[res];
		} catch (ArrayIndexOutOfBoundsException ex) {
			residence = "null";
		}
		String result = "name: " + name + "\n" + "Credit Hours: " + cred + "\n"
				+ "Enrollment: " + e + "\n" + "Residency: " + residence + "\n"
				+ "Tuition fee: " + tut + "\n" + "Housing expense: " + housing
				+ "\n" + "Total sem. cost: " + total + "\n";
		return result;
	}

	public static void main(String[] args) {

		boolean finished = false;
		boolean invalidHours = true;
		int cred = 1;
		int enroll = -1;
		int res = -1;
		int house = -1;
		int hall = -1;

		do {
			JOptionPane.showMessageDialog(null,
					"Welcome to CollegeFeeCalculator!", "CollegeFeeCalculator",
					JOptionPane.INFORMATION_MESSAGE);

			String name = JOptionPane.showInputDialog(null,
					"Plese enter your name, then press \'OK\'", "Name",
					JOptionPane.QUESTION_MESSAGE);

			do {
				enroll = JOptionPane.showOptionDialog(null,
						"Please select your enrollment", "Enrollment",
						JOptionPane.DEFAULT_OPTION,
						JOptionPane.QUESTION_MESSAGE, null, new String[] {
								"Full time", "Part time" }, null);
				cred = protectedParse(JOptionPane
						.showInputDialog(
								null,
								"Please enter the no. of credit hours, then press \'OK\'",
								"Credit Hours", JOptionPane.QUESTION_MESSAGE));
				if (cred > 0 && (cred < 8 && enroll == PART)
						|| (cred >= 8 && enroll == FULL)) {
					invalidHours = false;
				} else {
					JOptionPane
							.showMessageDialog(
									null,
									"Please enter valid credit hours for the current enrollment",
									"Invalid no. of credits",
									JOptionPane.ERROR_MESSAGE);
				}
			} while (invalidHours);

			res = arrLookup((String) JOptionPane.showInputDialog(null,
					"Please select the appropriate residency", "Residency",
					JOptionPane.QUESTION_MESSAGE, null, RESARR, "In-State"),
					RESARR);

			house = arrLookup((String) JOptionPane.showInputDialog(null,
					"Please select your housing", "Housing",
					JOptionPane.QUESTION_MESSAGE, null, HOUSEARR, "On-campus"),
					HOUSEARR);

			if (house == 0) {
				hall = arrLookup(
						(String) JOptionPane.showInputDialog(null,
								"Please select your residence hall",
								"Residence-Hall", JOptionPane.QUESTION_MESSAGE,
								null, HALLARR, "Earhart"), HALLARR);
			}

			JOptionPane.showMessageDialog(null,
					finString(name, cred, enroll, res, house, hall),
					"CollegeFeeCalculator", JOptionPane.INFORMATION_MESSAGE);

		} while (JOptionPane.showOptionDialog(null,
				"Would you like to continue?", "Are You Done?",
				JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null,
				null, null) == 0);
	}
}
