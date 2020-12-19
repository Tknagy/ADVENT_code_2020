use std::collections::HashMap;
use std::error::Error;
use std::fs;

#[macro_use]
extern crate lazy_static;
extern crate regex;

use regex::Regex;

#[derive(Debug)]
struct MemInput {
    address: usize,
    value: usize,
}

impl MemInput {
    fn from(raw: &str) -> Self {
        lazy_static! {
            static ref RE_MEM_STR: Regex = Regex::new(r"mem\[([0-9]+)\]\s+=\s+([0-9]+)").unwrap();
        }

        let caps = RE_MEM_STR.captures(raw).unwrap();

        Self {
            address: caps[1].parse::<usize>().unwrap(),
            value: caps[2].parse::<usize>().unwrap(),
        }
    }
}

fn apply_mask_value(mask: &str, mem_value: &usize) -> usize {
    let bin_value = format!("{:036b}", mem_value);
    bin_value
        .chars()
        .enumerate()
        .map(|(i, c)| {
            let mask_c = mask.chars().nth(i).unwrap();
            if mask_c != 'X' {
                mask_c
            } else {
                c
            }
        })
        .enumerate()
        .map(|(i, c)| c.to_digit(2).unwrap_or(0) as u64 * 2_u64.pow(35 - i as u32))
        .sum::<u64>() as usize
}

fn apply_mask_address(mask: &str, mem_address: &usize) -> Vec<usize> {
    let bin_value = format!("{:036b}", mem_address);
    let floating_address: String = bin_value
        .chars()
        .enumerate()
        .map(|(i, c)| {
            let mask_c = mask.chars().nth(i).unwrap();
            match mask_c {
                '1' => mask_c,
                '0' => c,
                _ => 'X',
            }
        })
        .collect();

    let n_x = floating_address.chars().filter(|&c| c == 'X').count();
    let perms: Vec<Vec<char>> = (0..2_u32.pow(n_x as u32))
        .map(|n| format!("{:0width$b}", n, width = n_x).chars().collect())
        .collect();

    perms
        .iter()
        .map(|perm| {
            let mut perm = perm.clone();
            floating_address
                .clone()
                .chars()
                .map(|c| match c {
                    'X' => perm.pop().unwrap(),
                    _ => c,
                })
                .enumerate()
                .map(|(i, c)| c.to_digit(2).unwrap_or(0) as u64 * 2_u64.pow(35 - i as u32))
                .sum::<u64>() as usize
        })
        .collect()
}

fn part1(contents: &str) {
    let mut mem: HashMap<usize, usize> = HashMap::new();
    let mut mask = "";

    for line in contents.lines() {
        if line.contains("mask") {
            mask = line.split_whitespace().next_back().unwrap();
        } else if line.contains("mem") {
            let mem_input = MemInput::from(line);
            mem.insert(mem_input.address, apply_mask_value(mask, &mem_input.value));
        }
    }

    let sum = mem.values().map(|&v| v as u64).sum::<u64>();
    println!("{}", sum);
}

fn part2(contents: &str) {
    let mut mem: HashMap<usize, usize> = HashMap::new();
    let mut mask = "";

    for line in contents.lines() {
        if line.contains("mask") {
            mask = line.split_whitespace().next_back().unwrap();
        } else if line.contains("mem") {
            let mem_input = MemInput::from(line);
            for address in apply_mask_address(mask, &mem_input.address) {
                mem.insert(address, mem_input.value);
            }
        }
    }

    let sum = mem.values().map(|&v| v as u64).sum::<u64>();
    println!("{}", sum);
}

fn main() -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string("input.txt")?;
    part1(&contents);
    part2(&contents);

    Ok(())
}
