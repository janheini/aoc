import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

class day2 {

	public static void partOne(Scanner input) throws Exception {
		int horizontal = 0;
		int depth = 0;

		while (input.hasNext()) {
			switch (input.next()) {
				case "forward": horizontal += input.nextInt(); break;
				case "down": depth += input.nextInt(); break;
				case "up": depth -= input.nextInt(); break;
				default: throw new Exception("Format not ok...");
			}
		}

		System.out.println(horizontal * depth);
	}

	public static void partTwo(Scanner input) throws Exception {
		int aim = 0;
		int next = 0;
		int horizontal = 0;
		int depth = 0;

		while (input.hasNext()) {
			switch (input.next()) {
				case "forward":
					next = input.nextInt();
					horizontal += next;
					depth += aim * next;
					break;
				case "down": aim += input.nextInt(); break;
				case "up": aim -= input.nextInt(); break;
				default: throw new Exception("Format not ok...");
			}
		}

		System.out.println(horizontal * depth);
	}

	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(new File("day2_input.txt"));
		System.out.print("Part One: ");
		partOne(sc);

		sc = new Scanner(new File("day2_input.txt"));
		System.out.print("Part Two: ");
		partTwo(sc);
	}
}
