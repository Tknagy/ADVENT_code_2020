use std::collections::HashSet;
use std::error::Error;
use std::fs;

fn part1(numbers: &Vec<i64>, preamble_size: usize) -> Result<i64, Box<dyn Error>> {
    for i in preamble_size..numbers.len() {
        let previous: HashSet<i64> = numbers[i - preamble_size..i].iter().cloned().collect();
        let current = numbers[i];

        let valid = previous
            .iter()
            .map(|n| previous.contains(&(current - n)))
            .any(|b| b);

        if !valid {
            println!("{}", current);
            return Ok(current);
        }
    }
    Err(Box::from("no solution for part 1"))
}

/// The dumbest brute force solution.
fn part2(numbers: &Vec<i64>, target: &i64) {
    for i in 0..numbers.len() - 1 {
        for j in i + 1..numbers.len() {
            let slice = &numbers[i..j];
            let slice_sum: i64 = slice.iter().sum();

            if slice_sum == *target {
                println!(
                    "{}",
                    slice.iter().min().unwrap() + slice.iter().max().unwrap()
                );
                return;
            } else if slice_sum > *target {
                continue;
            }
        }
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string("input.txt")?;
    let numbers: Vec<i64> = contents
        .lines()
        .map(|line| line.parse::<i64>().unwrap())
        .collect();

    let target = part1(&numbers, 25)?;
    part2(&numbers, &target);

    Ok(())
}
