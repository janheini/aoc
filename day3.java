import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.lang.Math;

class day3 {

	public static void day3(Scanner input) throws Exception {
		char[] line;
		int[][] arr = new int[1000][12];
		// convert input into 2D-array
		// (we need to go through column-wise)
		for (int i = 0; i < 1000; i++) {
			line = input.nextLine().toCharArray();
			for (int j = 0; j < 12; j++) {
				arr[i][j] = Character.digit(line[j], 10);
			}
		}

		int zero = 0;
		int one = 0;
		int gamma = 0;
		int epsilon = 0;
		for (int i = 0; i < 12; i++) {
			// count the ones and zeros
			for (int j = 0; j < 1000; j++) {
				//System.out.print("[" + arr[j][i] + "]");
				if (arr[j][i] == 1) {
					one++;
				} else if (arr[j][i] == 0) {
					zero++;
				} else {
					throw new Exception("fail");
				}
			}
			//System.out.println("");

			// add corresponding value to epsilon/gamma
			if (one > zero) {
				gamma += Math.pow(2, 11-i);
				// System.out.println("Gamma is now " + gamma + ", increased by " + Math.pow(2, 11-i) + " " + (11-i));
			} else if (zero > one) {
				epsilon += Math.pow(2, 11-i);
				// System.out.println("Epsilon is now " + epsilon + ", increased by " + Math.pow(2, 11-i) + " " + (11-i));
			} else {
				throw new Exception("fail");
			}

			zero = 0;
			one = 0;

		}

		System.out.println("Part One: " + gamma*epsilon);

	}


	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(new File("day3_input.txt"));
		System.out.print("Part One: ");
		day3(sc);
	}
}
