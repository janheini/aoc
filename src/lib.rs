#![warn(rust_2018_idioms)]

use std::fs;
pub mod day1;

pub enum Part {
    One = 1,
    Two,
}

impl std::fmt::Display for Part {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::One => write!(f, "{}", 1),
            Self::Two => write!(f, "{}", 2),
        }
    }
}

pub fn read_input(day: u8) -> String {
    fs::read_to_string(format!("input/day{day}.txt")).expect("should have input")
}

pub fn read_solution(day: u8, part: &Part) -> Option<usize> {
    let solution = match fs::read_to_string(format!("solutions/day{day}.txt")) {
        Ok(solution) => solution,
        Err(err) => {
            eprintln!("Could not read solution file for day{day}: {err}");
            return None;
        }
    };

    let mut lines = solution.lines();

    match part {
        Part::One => lines.next().unwrap_or_default().parse().ok(),
        Part::Two => lines.nth(1).unwrap_or_default().parse().ok(),
    }
}

#[test]
fn test_read_input() {
    assert!(read_input(1).lines().count() > 100);
}

#[test]
#[should_panic]
fn test_read_input_panic() {
    read_input(25);
}

#[test]
fn test_read_solution() {
    assert!(read_solution(1, &Part::One).is_some());
    assert!(read_solution(1, &Part::Two).is_some());
    assert!(read_solution(25, &Part::One).is_none());
    assert!(read_solution(25, &Part::Two).is_none());
}
