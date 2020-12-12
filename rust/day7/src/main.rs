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

    let rules = contents
        .lines()
        .map(|line| {
            let first = String::from(&RE_FIRST.captures(line).unwrap()[1]);
            let caps: Vec<_> = RE_CONTAINED.captures_iter(line).collect();

            let contained = caps
                .iter()
                .map(|cap| {
                    let quantity = &cap[1].parse::<u32>().unwrap();
                    let bag_type = String::from(&cap[2]);
                    (quantity.clone(), bag_type)
                })
                .collect();
            (first, contained)
        })
        .collect();

    rules
}

fn part1(rules: &HashMap<String, Vec<(u32, String)>>) {
    let contains_shiny = rules
        .keys()
        .filter_map(|key| part1_search(&rules, &String::from(key)))
        .count();
    println!("{}", contains_shiny);
}

fn part1_search(rules: &HashMap<String, Vec<(u32, String)>>, key: &String) -> Option<()> {
    let values = rules.get(key).unwrap();
    if values
        .iter()
        .filter(|value| {
            value.1.contains(&String::from("shiny gold"))
                || part1_search(&rules, &String::from(&value.1)).is_some()
        })
        .next()
        .is_some()
    {
        return Some(());
    }
    None
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
        values
            .iter()
            .map(|value| value.0 + value.0 * part2_search(&rules, &String::from(&value.1)))
            .sum()
    }
}

fn main() {
    let contents = fs::read_to_string("input.txt").unwrap();
    let rules = get_rules(&contents);
    println!("{:?}", rules);
    part1(&rules);
    part2(&rules);
}
