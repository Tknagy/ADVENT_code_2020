use std::collections::HashSet;
use std::fs;

fn part1(group_answers: &Vec<&str>) {
    let all_answers: usize = group_answers
        .iter()
        .map(|group_answer| {
            group_answer
                .chars()
                .filter(|c| !c.is_whitespace())
                .collect::<HashSet<char>>()
                .len()
        })
        .sum();

    println!("{}", all_answers);
}

fn part2(group_answers: &Vec<&str>) {
    let all_answers: usize = group_answers
        .iter()
        .map(|group_answer| {
            let mut group_unique_answers: HashSet<char> = group_answer
                .chars()
                .filter(|c| !c.is_whitespace())
                .collect();

            let person_answers: Vec<&str> = group_answer.split_whitespace().collect();
            for person_answer in &person_answers {
                let person_unique_answers: HashSet<char> = person_answer.chars().collect();
                group_unique_answers = group_unique_answers
                    .intersection(&person_unique_answers)
                    .cloned()
                    .collect();
            }

            group_unique_answers.len()
        })
        .sum();

    println!("{}", all_answers);
}

fn main() {
    let contents = fs::read_to_string("input.txt").unwrap();
    let group_answers: Vec<&str> = contents.split("\n\n").collect();

    part1(&group_answers);
    part2(&group_answers);
}
