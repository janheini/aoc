use super::read_input;

pub fn part1() -> i32 {
    let input = read_input(1);
    let mut result = 0;

    for line in input.lines() {
        let numbers: &[_] = &['1', '2', '3', '4', '5', '6', '7', '8', '9'];
        let numbers_in_line = line.char_indices().filter(|c| numbers.contains(&c.1));
        let collect = numbers_in_line.map(|x| x.1).collect::<Vec<_>>();
        let first = collect.first().unwrap();
        let last = collect.last().unwrap();
        let sum: i32 = format!("{}{}", first, last).parse().unwrap();

        result += sum;
        println!("{line} -> {collect:?}, ({first}, {last}), {sum:?}, {result}");
    }

    return result;
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::read_solution;
    use crate::Part;

    #[test]
    fn test_part1() {
        let day = 1;
        let part = Part::One;

        if let Some(solution) = read_solution(day, &part) {
            assert_eq!(part1(), solution, "day{day} part{part}");
        }
    }
}
