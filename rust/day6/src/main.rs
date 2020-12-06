use std::collections::HashSet;
use std::fs;

fn part1(group_answers: &Vec<&str>) {
    let mut all_answers = 0;

    for answer in group_answers {
        let answer: String = answer.split_whitespace().collect();
        let group_unique_answers: HashSet<char> = answer.chars().collect();
        all_answers += group_unique_answers.len();
    }

    println!("{}", all_answers);
}

fn part2(group_answers: &Vec<&str>) {
    let mut all_answers = 0;

    for group_answer in group_answers {
        let mut group_unique_answers: HashSet<char> = HashSet::new();
        let person_answers: Vec<&str> = group_answer.split_whitespace().collect();

        for person_answer in &person_answers {
            let person_answer = person_answer.to_string();
            let person_unique_answers: HashSet<char> = person_answer.chars().collect();
            group_unique_answers = group_unique_answers
                .union(&person_unique_answers)
                .cloned()
                .collect();
        }

        for person_answer in &person_answers {
            let person_unique_answers: HashSet<char> = person_answer.chars().collect();
            group_unique_answers = group_unique_answers
                .intersection(&person_unique_answers)
                .cloned()
                .collect();
        }

        all_answers += group_unique_answers.len();
    }

    println!("{}", all_answers);
}

fn main() {
    let contents = fs::read_to_string("input.txt").unwrap();
    let group_answers: Vec<&str> = contents.split("\n\n").collect();

    part1(&group_answers);
    part2(&group_answers);
}
