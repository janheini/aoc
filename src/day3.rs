use std::collections::HashMap;

fn is_valid(grid: &[Vec<char>], x: usize, y: usize) -> bool {
    const SYMBOLS: [char; 10] = ['@', '#', '$', '%', '&', '*', '-', '=', '+', '/'];

    let around = [
        grid.get(x.saturating_sub(1))
            .and_then(|row| row.get(y.saturating_sub(1))),
        grid.get(x.saturating_sub(1)).and_then(|row| row.get(y)),
        grid.get(x.saturating_sub(1)).and_then(|row| row.get(y + 1)),
        grid.get(x).and_then(|row| row.get(y.saturating_sub(1))),
        grid.get(x).and_then(|row| row.get(y + 1)),
        grid.get(x + 1).and_then(|row| row.get(y.saturating_sub(1))),
        grid.get(x + 1).and_then(|row| row.get(y)),
        grid.get(x + 1).and_then(|row| row.get(y + 1)),
    ];

    return around
        .iter()
        .any(|&c| c.is_some() && SYMBOLS.contains(c.unwrap()));
}

#[derive(Eq, Hash, PartialEq, Debug)]
struct Coordinate {
    x: usize,
    y: usize,
}

fn gear(
    grid: &[Vec<char>],
    position: &Coordinate,
    value: u32,
    map: &mut HashMap<Coordinate, u32>,
) -> u32 {
    /* Checks for gear on position
     *  stores value in map for first part of gear
     *  returns gear value or 0 */
    let size = value.to_string().len();

    for i in 1..=size {
        let pos = Coordinate {
            x: position.x.saturating_sub(i),
            y: position.y,
        };

        for hor in 0..=2 {
            for ver in 0..=2 {
                let x = (pos.x + 1).saturating_sub(hor);
                let y = (pos.y + 1).saturating_sub(ver);
                let gear = grid.get(y).and_then(|row| row.get(x));
                let coord = Coordinate { x, y };

                if let Some(&'*') = gear {
                    match map.remove(&coord) {
                        Some(val) => {
                            // gear found
                            return value * val;
                        }
                        None => {
                            // first part of a gear, save in map
                            map.insert(coord, value);
                            return 0;
                        }
                    }
                }
            }
        }
    }

    0
}

pub fn day3(input: &str) -> (u32, u32) {
    let mut part1 = 0;
    let mut part2 = 0;
    let mut map: HashMap<Coordinate, u32> = HashMap::new();

    let mut grid: Vec<Vec<char>> = vec![];

    for line in input.lines() {
        grid.push(line.chars().collect());
    }

    for (y, row) in grid.iter().enumerate() {
        let mut value = 0;
        let mut valid = false;

        for (x, c) in row.iter().enumerate() {
            if let Some(c) = c.to_digit(10) {
                value = (value * 10) + c;
                if !valid {
                    valid = is_valid(&grid, y, x);
                }
            } else {
                // number ended, add if valid
                if valid {
                    part1 += value;
                    // println!("{x}, {y}, {c}");
                    part2 += gear(&grid, &Coordinate { x, y }, value, &mut map);
                }

                value = 0;
                valid = false;
            }
        }

        // line ended, add if number at end of line was valid
        if valid {
            part1 += value;
            part2 += gear(&grid, &Coordinate { x: row.len(), y }, value, &mut map);
        }
    }

    (part1, part2)
}

#[cfg(test)]
mod tests {
    use core::panic;

    use super::super::*;
    use super::*;

    const EXAMPLE: &str = "467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..
";

    #[test]
    fn day3_example() {
        println!("{EXAMPLE}");
        assert_eq!(day3(EXAMPLE), (4361, 467835));
    }

    #[test]
    fn day3_into_iter() {
        let mut foo = [Some(1), Some(2), None, Some(4)]
            .iter()
            .filter(|x| x.is_some())
            .flatten();
        assert_eq!(foo.next(), Some(&1));
        assert_eq!(foo.next(), Some(&2));
        assert_eq!(foo.next(), Some(&4));
    }

    #[test]
    fn day3_part1() {
        let day = 3;
        let part = Part::One;
        let input = read_input(day);

        if let Some(solution) = read_solution(day, &part) {
            assert_eq!(day3(&input).0, solution, "day{day} part{part}");
        }
    }

    #[test]
    fn day3_part2() {
        let day = 3;
        let part = Part::Two;
        let input = read_input(day);

        if let Some(solution) = read_solution(day, &part) {
            assert_eq!(day3(&input).1, solution, "day{day} part{part}");
        } else {
            println!("Proposed Solution: {}", day3(&input).1);
            panic!("No solution yet.");
        }
    }
}
