use std::collections::HashMap;
use std::error::Error;
use std::fs;

const DELTA: i32 = 3;

fn part1(adapters: &Vec<i32>) {
    let mut differences: Vec<i32> = Vec::new();
    for current_idx in 0..adapters.len() - 1 {
        differences.push(adapters[current_idx + 1] - adapters[current_idx]);
    }

    println!(
        "{}",
        differences.iter().filter(|&&d| d == 1).count()
            * differences.iter().filter(|&&d| d == 3).count()
    );
}

fn part2(adapters: &Vec<i32>) {
    let mut fw_edges: HashMap<i32, Vec<i32>> = HashMap::new();
    for idx in 0..adapters.len() - 1 {
        let output = adapters[idx];
        let next: Vec<i32> = adapters[idx + 1..]
            .iter()
            .filter(|&&d| (d - output) <= DELTA)
            .map(|d| *d) // why god
            .collect();
        fw_edges.insert(output, next);
    }

    let mut cache: HashMap<i32, i128> = HashMap::new();
    let all_combinations = adapters.iter().rev().map(|i| {
        let combinations = part2_search(&fw_edges, &cache, *i, *adapters.last().unwrap());
        cache.insert(*i, combinations);
        combinations
    });

    println!("{:?}", all_combinations.last().unwrap());
}

fn part2_search(
    fw_edges: &HashMap<i32, Vec<i32>>,
    cache: &HashMap<i32, i128>,
    search_key: i32,
    device_rating: i32,
) -> i128 {
    if device_rating == search_key {
        return 1;
    }

    let mut counter = 0;
    let values = fw_edges.get(&search_key).unwrap();
    for key in values {
        match cache.get(key) {
            Some(x) => counter += x,
            None => counter += part2_search(fw_edges, cache, *key, device_rating),
        }
    }

    return counter;
}

fn main() -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string("input.txt")?;
    let mut adapters: Vec<i32> = contents
        .lines()
        .flat_map(|line| line.parse::<i32>())
        .collect();
    adapters.sort();

    let device_rating = adapters.iter().max().unwrap() + DELTA;
    adapters.insert(0, 0);
    adapters.push(device_rating);

    part1(&adapters);
    part2(&adapters);

    Ok(())
}
