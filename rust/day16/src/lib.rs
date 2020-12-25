use regex::Regex;

#[derive(Debug, Clone)]
struct Field {
    name: String,
    first_range: (usize, usize),
    second_range: (usize, usize),
}

pub struct Config {
    fields: Vec<Field>,
    my_ticket: Vec<usize>,
    other_tickets: Vec<Vec<usize>>,
}

pub fn parse(contents: &str) -> Config {
    let mut contents = contents.split("\n\n");
    let fields = contents.next().unwrap();

    let re_field: Regex = Regex::new(r"([A-Za-z\s]+): (\d+)\-(\d+) or (\d+)-(\d+)").unwrap();

    let fields: Vec<Field> = fields
        .lines()
        .map(|line| {
            let caps = re_field.captures(line).unwrap();
            Field {
                name: String::from(&caps[1]),
                first_range: (
                    caps[2].parse::<usize>().unwrap(),
                    caps[3].parse::<usize>().unwrap(),
                ),
                second_range: (
                    caps[4].parse::<usize>().unwrap(),
                    caps[5].parse::<usize>().unwrap(),
                ),
            }
        })
        .collect();

    let my_ticket: Vec<usize> = contents.next().unwrap().lines().collect::<Vec<&str>>()[1..]
        .iter()
        .map(|line| {
            line.trim_end()
                .split(",")
                .map(|n| n.parse::<usize>().unwrap())
                .collect()
        })
        .next()
        .unwrap();

    let other_tickets: Vec<Vec<usize>> = contents.next().unwrap().lines().collect::<Vec<&str>>()
        [1..]
        .iter()
        .map(|line| {
            line.trim_end()
                .split(",")
                .map(|n| n.parse::<usize>().unwrap())
                .collect()
        })
        .collect();

    Config {
        fields,
        my_ticket,
        other_tickets,
    }
}

fn get_invalid_fields(ticket: &Vec<usize>, fields: &Vec<Field>) -> Vec<usize> {
    ticket
        .iter()
        .filter(|&&f| {
            fields
                .iter()
                .map(|field| {
                    !((f >= field.first_range.0 && f <= field.first_range.1)
                        || (f >= field.second_range.0 && f <= field.second_range.1))
                })
                .all(|v| v)
        })
        .cloned()
        .collect::<Vec<_>>()
}

pub fn part1(config: &Config) -> usize {
    let sol: Vec<usize> = config
        .other_tickets
        .iter()
        .map(|other| get_invalid_fields(&other, &config.fields))
        .flatten()
        .collect();

    println!("{:?}", sol);
    sol.iter().sum::<usize>()
}

pub fn part2(config: &Config) -> usize {
    // Collect all valid tickets including my ticket
    let mut valid_other: Vec<Vec<usize>> = config
        .other_tickets
        .iter()
        .filter(|other| get_invalid_fields(&other, &config.fields).is_empty())
        .cloned()
        .collect();
    valid_other.push(config.my_ticket.clone());

    // Transpose tickets such that the same field logic can be used
    let cols: Vec<Vec<_>> = (0..config.fields.len())
        .into_iter()
        .map(|c| valid_other.iter().map(|v| v[c]).collect())
        .collect();

    let mut ordered_fields_indices = vec![None; config.fields.len()];

    //Iterate while there are unmatched columns. Only unique matches are considered as valid
    //indices
    while ordered_fields_indices.iter().any(|x| x.is_none()) {
        for (i, col) in cols.iter().enumerate() {
            if ordered_fields_indices[i].is_some() {
                continue;
            }
            let mut matches: Vec<usize> = Vec::new();
            for (idx, field) in config.fields.iter().enumerate() {
                if get_invalid_fields(&col, &vec![field.clone()]).is_empty()
                    && !ordered_fields_indices.contains(&Some(idx))
                {
                    matches.push(idx);
                }
            }

            if matches.len() == 1 {
                ordered_fields_indices[i] = Some(*matches.first().unwrap());
            }
        }
    }

    config
        .my_ticket
        .iter()
        .enumerate()
        .filter(|(i, _)| {
            config.fields[ordered_fields_indices[*i].unwrap()]
                .name
                .contains("departure")
        })
        .map(|(_, v)| *v)
        .product()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part1_demo() {
        let data = r"class: 1-3 or 5-7
row: 6-11 or 33-44
seat: 13-40 or 45-50

your ticket:
7,1,14

nearby tickets:
7,3,47
40,4,50
55,2,20
38,6,12";
        let config = parse(data);
        let sol = part1(&config);
        assert_eq!(sol, 71);
    }

    #[test]
    fn part2_demo() {
        let data = r"class: 0-1 or 4-19
row: 0-5 or 8-19
seat: 0-13 or 16-19

your ticket:
11,12,13

nearby tickets:
3,9,18
15,1,5
5,14,9";
        let config = parse(data);
        let sol = part2(&config);
        assert_eq!(sol, 1);
    }
}
