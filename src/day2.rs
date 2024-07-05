use super::read_input;

pub fn possible(line: &str) -> Result<bool, &'static str> {
    println!("{}", line);
    let (_, line) = line.split_once(':').ok_or("fail")?;
    for element in line.split(|c: char| c == ',' || c == ';') {
        let mut iter = element.split_whitespace();
        let value: usize = iter.next().unwrap().parse().unwrap();
        match iter.next() {
            Some("red") => {
                if value > 12 {
                    return Ok(false);
                }
            }
            Some("green") => {
                if value > 13 {
                    return Ok(false);
                }
            }
            Some("blue") => {
                if value > 14 {
                    return Ok(false);
                }
            }
            _ => (),
        };
    }

    Ok(true)
}

pub fn power(line: &str) -> Result<u32, &'static str> {
    println!("{}", line);
    let mut red = 1;
    let mut green = 1;
    let mut blue = 1;

    let (_, line) = line.split_once(':').ok_or("fail")?;
    for element in line.split(|c: char| c == ',' || c == ';') {
        let mut iter = element.split_whitespace();
        let value = iter.next().unwrap().parse().unwrap();
        match iter.next() {
            Some("red") => red = std::cmp::max(red, value),
            Some("green") => green = std::cmp::max(green, value),
            Some("blue") => blue = std::cmp::max(blue, value),
            _ => return Err("failed to parse color"),
        };
    }

    Ok(red * green * blue)
}

pub fn part1() -> usize {
    let input = read_input(2);
    let mut sum = 0;
    for (index, line) in input.lines().enumerate() {
        if possible(line).expect("possible should always work") {
            sum += index + 1;
        }
    }

    sum
}

pub fn part2() -> u32 {
    let input = read_input(2);
    let mut sum = 0;

    for line in input.lines() {
        sum += power(line).expect("power should always work");
    }

    sum
}

#[cfg(test)]
mod tests {
    use super::super::*;
    use super::*;

    const EXAMPLE: &str = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
";

    #[test]
    fn day2_possible() {
        assert_eq!(
            EXAMPLE
                .lines()
                .map(|line| possible(line).expect("none of these should fail"))
                .collect::<Vec<bool>>(),
            vec![true, true, false, false, true]
        );
    }

    #[test]
    fn day2_power() {
        assert_eq!(
            EXAMPLE
                .lines()
                .map(|line| power(line).expect("none of these should fail"))
                .collect::<Vec<_>>(),
            vec![48, 12, 1560, 630, 36]
        )
    }

    #[test]
    fn day2_part1() {
        let day = 2;
        let part = Part::One;

        if let Some(solution) = read_solution(day, &part) {
            assert_eq!(part2(), solution, "day{day} part{part}");
        }
    }

    #[test]
    fn day2_part2() {
        let day = 2;
        let part = Part::Two;

        if let Some(solution) = read_solution(day, &part) {
            assert_eq!(part2(), solution, "day{day} part{part}");
        }
    }
}
