use std::cmp::{max, min};
use std::fs;

fn row_from_code(code: &str) -> u32 {
    let mut res = 0;

    for (i, c) in code.chars().enumerate() {
        match c {
            'F' => res += 0 * 2_u32.pow((7 - i - 1) as u32),
            'B' => res += 1 * 2_u32.pow((7 - i - 1) as u32),
            _ => {}
        }
    }

    res
}

fn col_from_code(code: &str) -> u32 {
    let mut res = 0;

    for (i, c) in code.chars().enumerate() {
        match c {
            'L' => res += 0 * 2_u32.pow((3 - i - 1) as u32),
            'R' => res += 1 * 2_u32.pow((3 - i - 1) as u32),
            _ => {}
        }
    }

    res
}

fn id_from_pos(row: u32, col: u32) -> u32 {
    row * 8 + col
}

fn part1() {
    let contents = fs::read_to_string("input.txt").unwrap();
    let mut max_id = 0;

    for line in contents.lines() {
        let row_code = &line[0..7];
        let col_code = &line[line.len() - 3..];
        let row = row_from_code(row_code);
        let col = col_from_code(col_code);
        let id = id_from_pos(row, col);
        max_id = max(max_id, id);
    }

    println!("{}", max_id);
}

fn part2() {
    let contents = fs::read_to_string("input.txt").unwrap();
    let mut all_ids: Vec<u32> = Vec::new();

    for line in contents.lines() {
        let row_code = &line[0..7];
        let col_code = &line[line.len() - 3..];
        let row = row_from_code(row_code);
        let col = col_from_code(col_code);
        let id = id_from_pos(row, col);

        all_ids.push(id);
    }

    all_ids.sort();

    for i in 1..all_ids.len() {
        if (all_ids[i] - all_ids[i - 1]) == 2 {
            println!("{}", all_ids[i] - 1);
            break;
        }
    }
}

fn main() {
    part1();
    part2();
}
