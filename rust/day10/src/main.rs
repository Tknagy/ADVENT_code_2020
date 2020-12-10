use std::cmp::min;
use std::collections::HashMap;
use std::error::Error;
use std::fs;

fn part1(adapters: &Vec<i32>) {
    let device_rating = adapters.iter().max().unwrap() + 3;
    let mut differences: Vec<i32> = Vec::new();
    let mut all_outputs = adapters.to_vec();

    // Add the power outlet
    all_outputs.insert(0, 0);
    //Add the target device
    all_outputs.push(device_rating);

    for current_idx in 0..all_outputs.len() - 1 {
        let current_output = all_outputs[current_idx];
        let next_output = all_outputs[current_idx + 1];
        differences.push(next_output - current_output);
    }

    println!(
        "{}",
        differences.iter().filter(|&&d| d == 1).count()
            * differences.iter().filter(|&&d| d == 3).count()
    );
}

fn part2(adapters: &Vec<i32>) {
    let device_rating = adapters.iter().max().unwrap() + 3;
    let mut all_outputs: Vec<i32> = adapters.to_vec();

    // Add the power outlet
    all_outputs.insert(0, 0);
    // Add the target device
    all_outputs.push(device_rating);

    let mut fw_edges: HashMap<i32, Vec<i32>> = HashMap::new();
    for idx in 0..all_outputs.len() - 1 {
        let output = all_outputs[idx];
        let rest = all_outputs.len() - 1 - idx;
        let next: Vec<i32> = all_outputs[idx + 1..=idx + min(3, rest)]
            .iter()
            .filter(|&&d| (d - output) <= 3)
            .map(|d| *d) // why god
            .collect();

        fw_edges.insert(output, next);
    }

    let mut cache: HashMap<i32, i128> = HashMap::new();

    for i in all_outputs.iter().rev() {
        if !cache.contains_key(i) {
            let mut combinations = 0;
            part2_search(&fw_edges, &cache, *i, device_rating, &mut combinations);
            cache.insert(*i, combinations);
        }
    }

    // root contains all accumulated combinations
    println!("{:?}", cache.get(&0).unwrap());
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
        .map(|line| line.parse::<i32>().unwrap())
        .collect();
    adapters.sort();
    part1(&adapters);
    part2(&adapters);

    Ok(())
}
