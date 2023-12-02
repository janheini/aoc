import { readFileSync } from "node:fs";

console.log(
  readFileSync("./day1_input.txt", "utf8")
    .split("\n") // this breaks if trailing newline ...
    .map((line) => Array.from(line).filter((char) => Number(char)))
    .map((line) => Number(line[0] + line[line.length - 1]))
    .reduce((a, b) => a + b),
);
