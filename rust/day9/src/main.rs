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

fn part2(numbers: &Vec<i64>, target: &i64) {
    let mut left_idx = 0;
    let mut right_idx = 0;
    let mut sum = numbers[left_idx];

    while sum < *target {
        right_idx += 1;
        sum += numbers[right_idx];

        while sum > *target {
            sum -= numbers[left_idx];
            left_idx += 1
        }
    }

    println!(
        "{}",
        numbers[left_idx..right_idx + 1].iter().min().unwrap()
            + numbers[left_idx..right_idx + 1].iter().max().unwrap()
    );
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
