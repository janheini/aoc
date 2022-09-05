import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

class day1 {

	public static void partOne(Scanner input) {

		Integer curr = input.nextInt();
		Integer next = input.nextInt();
		Integer result = 0;

		if (next > curr) {
			result++;
		}

		while (input.hasNext()) {
			curr = next;
			// System.out.println("Curr: " + curr);
			next = input.nextInt();
			// System.out.println("Next: " + next);
			if (next > curr) {
				result++;
			}
		}

		System.out.println(result);
	}

	public static void partTwo(Scanner input) {
		int result = 0;

		// init first sector
		int a1 = input.nextInt();
		int a2 = input.nextInt();
		int a3 = input.nextInt();
		int a = a1 + a2 +a3;

		int b1 = a2;
		int b2 = a3;
		int b3 = input.nextInt();
		int b = b1 + b2 + b3;

		if (b > a) {
			result++;
		}

		while (input.hasNext()) {
			a1 = b1;
			a2 = b2;
			a3 = b3;
			b1 = a2;
			b2 = a3;
			b3 = input.nextInt();
			a = a1 + a2 + a3;
			b = b1 + b2 + b3;

			if (b > a) {
				result++;
			}
		}

		System.out.println(result);
	}

	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(new File("day1_input.txt"));
		System.out.print("Part One: ");
		partOne(sc);

		sc = new Scanner(new File("day1_input.txt"));
		System.out.print("Part Two: ");
		partTwo(sc);
	}
}
