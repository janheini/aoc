import { readFileSync } from "node:fs";

const input = readFileSync("./day2_input.txt", "utf8").split("\n");
input.pop(); // remove final newline

// part one and two
let result_one = 0;
let result_two = 0;

for (const line of input) {
  const index = line.split(":")[0].split(" ")[1];
  let legal = true;
  let l = line.split(":")[1].split(/[ ;,]/);
  const max_cubes = { red: 0, green: 0, blue: 0 };

  while (l.length > 0) {
    switch (l.pop()) {
      case "red":
        let red = Number(l.pop());
        if (red > 12) legal = false;
        if (red > max_cubes.red) max_cubes.red = red;
        break;
      case "green":
        let green = Number(l.pop());
        if (green > 13) legal = false;
        if (green > max_cubes.green) max_cubes.green = green;
        break;
      case "blue":
        let blue = Number(l.pop());
        if (blue > 14) legal = false;
        if (blue > max_cubes.blue) max_cubes.blue = blue;
        break;
    }
  }
  if (legal) {
    result_one += Number(index);
  }
  result_two += max_cubes.red * max_cubes.blue * max_cubes.green;
}

console.log(result_one);
console.log(result_two);
