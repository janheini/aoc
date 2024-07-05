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

pub fn part1(input: &str) -> u32 {
    let mut result = 0;

    let mut grid: Vec<Vec<char>> = vec![];

    for line in input.lines() {
        grid.push(line.chars().collect());
    }

    for (x, row) in grid.iter().enumerate() {
        let mut value = 0;
        let mut valid = false;

        for (y, c) in row.iter().enumerate() {
            if let Some(c) = c.to_digit(10) {
                value = (value * 10) + c;
                println!("value {value}");
                if !valid {
                    valid = is_valid(&grid, x, y);
                }
            } else {
                // number ended, add if valid
                if valid {
                    result += value;
                }
                value = 0;
                valid = false;
            }
        }

        // line ended, add if number at end of line was valid
        if valid {
            result += value;
        }
    }

    result
}

#[cfg(test)]
mod tests {
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
        assert_eq!(part1(EXAMPLE), 4361);
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
            assert_eq!(part1(&input), solution, "day{day} part{part}");
        }
    }
}
