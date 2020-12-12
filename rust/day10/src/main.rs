use std::collections::HashMap;
use std::error::Error;
use std::fs;

const DELTA: i32 = 3;

fn part1(adapters: &Vec<i32>) {
    let device_rating = adapters.iter().max().unwrap() + DELTA;
    let mut all_outputs = adapters.to_vec();

    // Add the power outlet
    all_outputs.insert(0, 0);
    //Add the target device
    all_outputs.push(device_rating);

    let mut differences: Vec<i32> = Vec::new();
    for current_idx in 0..all_outputs.len() - 1 {
        differences.push(all_outputs[current_idx + 1] - all_outputs[current_idx]);
    }

    println!(
        "{}",
        differences.iter().filter(|&&d| d == 1).count()
            * differences.iter().filter(|&&d| d == 3).count()
    );
}

fn part2(adapters: &Vec<i32>) {
    let device_rating = adapters.iter().max().unwrap() + DELTA;
    let mut all_outputs: Vec<i32> = adapters.to_vec();

    // Add the power outlet
    all_outputs.insert(0, 0);
    // Add the target device
    all_outputs.push(device_rating);

    let mut fw_edges: HashMap<i32, Vec<i32>> = HashMap::new();
    for idx in 0..all_outputs.len() - 1 {
        let output = all_outputs[idx];
        let next: Vec<i32> = all_outputs[idx + 1..]
            .iter()
            .filter(|&&d| (d - output) <= DELTA)
            .map(|d| *d) // why god
            .collect();
        fw_edges.insert(output, next);
    }

    let mut cache: HashMap<i32, i128> = HashMap::new();
    let all_combinations = all_outputs.iter().rev().map(|i| {
        let mut combinations = 0;
        part2_search(&fw_edges, &cache, *i, device_rating, &mut combinations);
        cache.insert(*i, combinations);
        combinations
    });

    // root contains all accumulated combinations
    println!("{:?}", all_combinations.last().unwrap());
}

fn part2_search(
    fw_edges: &HashMap<i32, Vec<i32>>,
    cache: &HashMap<i32, i128>,
    search_key: i32,
    device_rating: i32,
    counter: &mut i128,
) {
    if device_rating == search_key {
        *counter += 1;
        return;
    }

    let values = fw_edges.get(&search_key).unwrap();
    for key in values {
        match cache.get(key) {
            Some(x) => *counter += x,
            None => part2_search(fw_edges, cache, *key, device_rating, counter),
        }
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string("input.txt")?;
    let mut adapters: Vec<i32> = contents
        .lines()
        .flat_map(|line| line.parse::<i32>())
        .collect();
    adapters.sort();
    part1(&adapters);
    part2(&adapters);

    Ok(())
}
