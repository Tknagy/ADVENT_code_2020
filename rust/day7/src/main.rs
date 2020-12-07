use std::collections::HashMap;
use std::fs;

#[macro_use]
extern crate lazy_static;
extern crate regex;

use regex::Regex;

fn get_rules(contents: &String) -> HashMap<String, Vec<(u32, String)>> {
    lazy_static! {
        static ref RE_FIRST: Regex = Regex::new(r"([a-z]+\s+[a-z]+)\sbags?").unwrap();
        static ref RE_CONTAINED: Regex = Regex::new(r"([0-9]+)\s([a-z]+\s+[a-z]+)\sbags?").unwrap();
    }

    let mut rules: HashMap<String, Vec<(u32, String)>> = HashMap::new();

    for line in contents.lines() {
        let first = String::from(&RE_FIRST.captures(line).unwrap()[1]);
        let caps: Vec<_> = RE_CONTAINED.captures_iter(line).collect();

        let mut contained: Vec<(u32, String)> = Vec::new();
        for cap in caps {
            let quantity = &cap[1].parse::<u32>().unwrap();
            let bag_type = String::from(&cap[2]);
            contained.push((quantity.clone(), bag_type));
        }
        rules.insert(first, contained);
    }

    rules
}

fn part1(rules: &HashMap<String, Vec<(u32, String)>>) {
    let mut contains_shiny = 0;
    for key in rules.keys() {
        contains_shiny += part1_search(&rules, &String::from(key));
    }
    println!("{}", contains_shiny);
}

fn part1_search(rules: &HashMap<String, Vec<(u32, String)>>, key: &String) -> u32 {
    let values = rules.get(key).unwrap();
    if values.is_empty() {
        return 0;
    } else {
        for value in values {
            if value.1.contains(&String::from("shiny gold")) {
                return 1;
            }
        }

        let mut matches = 0;
        for value in values {
            matches += part1_search(&rules, &String::from(&value.1));
        }
        if matches > 0 {
            return 1;
        } else {
            return 0;
        }
    }
}

fn part2(rules: &HashMap<String, Vec<(u32, String)>>) {
    let matches = part2_search(&rules, &String::from("shiny gold"));
    println!("{}", matches);
}

fn part2_search(rules: &HashMap<String, Vec<(u32, String)>>, key: &String) -> u32 {
    let values = rules.get(key).unwrap();
    if values.is_empty() {
        return 0;
    } else {
        let mut matches = 0;
        for value in values {
            matches += value.0 + value.0 * part2_search(&rules, &String::from(&value.1));
        }
        matches
    }
}

fn main() {
    let contents = fs::read_to_string("input.txt").unwrap();
    let rules = get_rules(&contents);
    part1(&rules);
    part2(&rules);
}
