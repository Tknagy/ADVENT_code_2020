use std::collections::HashSet;
use std::fs;

fn hue() {
    let contents = fs::read_to_string("input.txt").unwrap();
    let contents: Vec<i64> = contents
        .lines()
        .map(|line| line.parse::<i64>().unwrap())
        .collect();

    let mut numbers: HashSet<i64> = HashSet::new();

    for i in 0..(contents.len() - 1) {
        let n1 = contents.get(i).unwrap();
        for j in (i + 1)..contents.len() {
            let n2 = contents.get(j).unwrap();
            let n3 = 2020 - n1 - n2;

            if numbers.contains(&n3) {
                println!("{}", n1 * n2 * n3);
                return;
            }

            numbers.insert(*n2);
        }
        numbers.insert(*n1);
    }
}

fn main() {
    hue()
}
