import { readFileSync } from "node:fs";

// part one
console.log(
  readFileSync("./day1_input.txt", "utf8")
    .split("\n") // this breaks if trailing newline
    .map((line) => Array.from(line).filter((char) => Number(char)))
    .map((line) => Number(line[0] + line[line.length - 1]))
    .reduce((a, b) => a + b),
);

// part two
const stats = {
  one: { index: -1, value: 1 as const },
  two: { index: -1, value: 2 as const },
  three: { index: -1, value: 3 as const },
  four: { index: -1, value: 4 as const },
  five: { index: -1, value: 5 as const },
  six: { index: -1, value: 6 as const },
  seven: { index: -1, value: 7 as const },
  eight: { index: -1, value: 8 as const },
  nine: { index: -1, value: 9 as const },
  "1": { index: -1, value: 1 as const },
  "2": { index: -1, value: 2 as const },
  "3": { index: -1, value: 3 as const },
  "4": { index: -1, value: 4 as const },
  "5": { index: -1, value: 5 as const },
  "6": { index: -1, value: 6 as const },
  "7": { index: -1, value: 7 as const },
  "8": { index: -1, value: 8 as const },
  "9": { index: -1, value: 9 as const },
};

console.log(
  readFileSync("./day1_input.txt", "utf8")
    .split("\n")
    .reduce((acc, line) => {
      // get the first occurance
      Object.keys(stats).forEach(
        (key) => (stats[key].index = line.indexOf(key)),
      );
      let min = { index: Infinity, value: 0 };
      Object.keys(stats).forEach((key) => {
        if (stats[key].index > -1 && stats[key].index < min.index) {
          min = stats[key];
        }
      });

      // get the last occurance
      Object.keys(stats).forEach(
        (key) => (stats[key].index = line.lastIndexOf(key)),
      );
      let max = { index: -1, value: 0 };
      Object.keys(stats).forEach((key) => {
        if (stats[key].index > -1 && stats[key].index > max.index) {
          max = stats[key];
        }
      });

      // accumulate
      return acc + min.value * 10 + max.value;
    }, 0),
);
