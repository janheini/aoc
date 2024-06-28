use super::read_input;

/* Note: I know you don't _need_ iterators for part2. I just wanted to try them. */

pub struct Part2<'a> {
    line: &'a str,
    front: usize,
    back: usize,
}

impl<'a> Part2<'a> {
    pub fn new(line: &'a str) -> Self {
        Self {
            line,
            front: 0,
            back: line.len(),
        }
    }

    /// used by Iterator and DoubleEndedIterator
    fn next_number(&mut self, forward: bool) -> Option<usize> {
        if self.front >= self.back {
            /* This is for the correct semantics of DoubleEndedIterator:
             * "It is important to note that both back and forth work on the same range, and do not
             * cross: iteration is over when they meet in the middle." */
            return None;
        }

        const NUMBERS: &[[&str; 2]; 9] = &[
            ["1", "one"],
            ["2", "two"],
            ["3", "three"],
            ["4", "four"],
            ["5", "five"],
            ["6", "six"],
            ["7", "seven"],
            ["8", "eight"],
            ["9", "nine"],
        ];

        let mut first_pos: Option<usize> = None;
        let mut first_val: Option<usize> = None;
        let mut first_match: Option<&str> = None;

        let substr = if forward {
            &self.line[self.front..]
        } else {
            &self.line[..self.back]
        };

        for (value, pair) in NUMBERS.into_iter().enumerate() {
            for item in pair {
                let position = if forward {
                    substr.find(item)
                } else {
                    substr.rfind(item)
                };

                if let Some(position) = position {
                    match first_pos {
                        Some(pos) => {
                            if (forward && position < pos) || (!forward && position > pos) {
                                first_pos = Some(position);
                                first_match = Some(item);
                                first_val = Some(value + 1);
                            }
                        }
                        None => {
                            first_pos = Some(position);
                            first_match = Some(item);
                            first_val = Some(value + 1);
                        }
                    }
                }
            }
        }

        match first_val {
            Some(first_val) => {
                if forward {
                    self.front += first_pos.unwrap() + first_match.unwrap().len();
                } else {
                    self.back = first_pos.unwrap();
                }
                Some(first_val)
            }
            None => None,
        }
    }
}

impl<'a> Iterator for Part2<'a> {
    type Item = usize;

    fn next(&mut self) -> Option<Self::Item> {
        self.next_number(true)
    }
}

impl<'a> DoubleEndedIterator for Part2<'a> {
    fn next_back(&mut self) -> Option<Self::Item> {
        self.next_number(false)
    }
}

pub fn part1() -> usize {
    let input = read_input(1);
    let mut result = 0;

    for line in input.lines() {
        let numbers: &[_] = &['1', '2', '3', '4', '5', '6', '7', '8', '9'];
        let numbers_in_line = line.char_indices().filter(|c| numbers.contains(&c.1));
        let collect = numbers_in_line.map(|x| x.1).collect::<Vec<_>>();
        let first = collect.first().unwrap();
        let last = collect.last().unwrap();
        let number: usize = format!("{}{}", first, last).parse().unwrap();

        result += number;
        println!("{line} -> {collect:?}, ({first}, {last}), {number:?}, {result}");
    }

    return result;
}

pub fn part2() -> usize {
    let input = read_input(1);
    let mut result: usize = 0;

    for line in input.lines() {
        let mut iter = Part2::new(line);
        let first = iter.next();
        let last = iter.next_back();
        if let Some(first) = first {
            result += 10 * first;
            if let Some(last) = last {
                result += last;
            } else {
                result += first;
            }
        }
    }
    return result;
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::read_solution;
    use crate::Part;

    #[test]
    fn test_iter() {
        let t = |s: &str| Part2::new(s).into_iter().collect::<Vec<usize>>();

        assert_eq!(t(""), vec![]);
        assert_eq!(t("4"), vec![4]);
        assert_eq!(t("123"), vec![1, 2, 3]);
        assert_eq!(t("six"), vec![6]);
        assert_eq!(t("foobarnine"), vec![9]);
        assert_eq!(t("foothreebar"), vec![3]);
        assert_eq!(t("foothree4"), vec![3, 4]);
        assert_eq!(t("1two3nine"), vec![1, 2, 3, 9]);
        assert_eq!(t("1onefoobarbazone2one"), vec![1, 1, 1, 2, 1]);
        assert_eq!(t("linewithnonumbers"), vec![]);
    }

    #[test]
    fn test_iter_back() {
        let t = |s: &str| Part2::new(s).into_iter().rev().collect::<Vec<usize>>();

        assert_eq!(t(""), vec![]);
        assert_eq!(t("4"), vec![4]);
        assert_eq!(t("123"), vec![3, 2, 1]);
        assert_eq!(t("six"), vec![6]);
        assert_eq!(t("foobarnine"), vec![9]);
        assert_eq!(t("foothreebar"), vec![3]);
        assert_eq!(t("foothree4"), vec![4, 3]);
        assert_eq!(t("1two3nine"), vec![9, 3, 2, 1]);
        assert_eq!(t("1onefoobarbazone2one"), vec![1, 2, 1, 1, 1]);
        assert_eq!(t("linewithnonumbers"), vec![]);
    }

    #[test]
    fn test_iter_both() {
        let mut test = Part2::new("onetwothree").into_iter();

        assert_eq!(test.next(), Some(1));
        assert_eq!(test.next_back(), Some(3));
        assert_eq!(test.next(), Some(2));
        assert_eq!(test.next_back(), None);
    }

    #[test]
    fn test_part1() {
        let day = 1;
        let part = Part::One;

        if let Some(solution) = read_solution(day, &part) {
            assert_eq!(part1(), solution, "day{day} part{part}");
        }
    }

    #[test]
    fn test_part2() {
        let day = 1;
        let part = Part::Two;

        if let Some(solution) = read_solution(day, &part) {
            assert_eq!(part2(), solution, "day{day} part{part}");
        }
    }
}
