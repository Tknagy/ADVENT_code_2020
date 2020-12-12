use std::cmp::{max, min};
use std::error::Error;
use std::fs;

fn get_adjacent_part1(seats: &Vec<Vec<char>>, row: &i32, col: &i32) -> Vec<char> {
    let mut adjacent: Vec<char> = Vec::new();
    let rows = seats.len();
    let cols = seats.first().unwrap().len();

    for r in max(0, row - 1)..=min(rows as i32 - 1, row + 1) {
        for c in max(0, col - 1)..=min(cols as i32 - 1, col + 1) {
            if &r == row && &c == col {
                continue;
            }
            adjacent.push(seats[r as usize][c as usize]);
        }
    }

    adjacent
}

fn part1(seats: &Vec<Vec<char>>) {
    let rows = seats.len();
    let cols = seats.first().unwrap().len();

    let mut prev_seats: Vec<Vec<char>> = Vec::new();
    let mut new_seats = seats.to_vec();

    while prev_seats != new_seats {
        prev_seats = new_seats.to_vec();
        for i in 0..rows {
            for j in 0..cols {
                let adjacent = get_adjacent_part1(&prev_seats, &(i as i32), &(j as i32));

                match prev_seats[i][j] {
                    'L' => {
                        if adjacent.iter().filter(|&&s| s == '.' || s == 'L').count()
                            == adjacent.len()
                        {
                            new_seats[i][j] = '#';
                        }
                    }
                    '#' => {
                        if adjacent.iter().filter(|&&s| s == '#').count() >= 4 {
                            new_seats[i][j] = 'L';
                        }
                    }
                    _ => {}
                }
            }
        }
    }

    let seats_occupied: usize = new_seats
        .iter()
        .map(|row| row.iter().filter(|&&c| c == '#').count())
        .sum();
    println!("{}", seats_occupied);
}

fn part2(seats: &Vec<Vec<char>>) {
    let rows = seats.len();
    let cols = seats.first().unwrap().len();

    let mut prev_seats: Vec<Vec<char>> = Vec::new();
    let mut new_seats = seats.to_vec();

    while prev_seats != new_seats {
        prev_seats = new_seats.to_vec();
        for i in 0..rows {
            for j in 0..cols {
                let adjacent_occupied =
                    get_adjacent_occupied_part2(&prev_seats, &(i as i32), &(j as i32));

                match prev_seats[i][j] {
                    'L' => {
                        if adjacent_occupied == 0 {
                            new_seats[i][j] = '#';
                        }
                    }
                    '#' => {
                        if adjacent_occupied >= 5 {
                            new_seats[i][j] = 'L';
                        }
                    }
                    _ => {}
                }
            }
        }
    }

    let seats_occupied: usize = new_seats
        .iter()
        .map(|row| row.iter().filter(|&&c| c == '#').count())
        .sum();
    println!("{}", seats_occupied);
}

fn get_adjacent_occupied_part2(seats: &Vec<Vec<char>>, row: &i32, col: &i32) -> usize {
    let rows = seats.len();
    let cols = seats.first().unwrap().len();

    let up = (0..*row as usize)
        .map(|r| seats[r as usize][*col as usize])
        .filter(|&seat| seat != '.')
        .last()
        .unwrap_or_default()
        == '#';

    let down = (*row as usize + 1..rows)
        .map(|r| seats[r as usize][*col as usize])
        .filter(|&seat| seat != '.')
        .next()
        .unwrap_or_default()
        == '#';

    let left = (0..*col as usize)
        .map(|c| seats[*row as usize][c as usize])
        .filter(|&seat| seat != '.')
        .last()
        .unwrap_or_default()
        == '#';

    let right = (*col as usize + 1..cols)
        .map(|c| seats[*row as usize][c as usize])
        .filter(|&seat| seat != '.')
        .next()
        .unwrap_or_default()
        == '#';

    let up_left = (0..*row as usize)
        .filter_map(|r| seats[(*row - r as i32 - 1) as usize].get((*col - r as i32 - 1) as usize))
        .filter(|&&seat| seat != '.')
        .map(|c| *c)
        .next()
        .unwrap_or_default()
        == '#';

    let up_right = (0..*row as usize)
        .filter_map(|r| seats[(*row - r as i32 - 1) as usize].get((*col + r as i32 + 1) as usize))
        .filter(|&&seat| seat != '.')
        .map(|c| *c)
        .next()
        .unwrap_or_default()
        == '#';

    let down_left = (0..rows - *row as usize - 1)
        .filter_map(|r| seats[(*row + r as i32 + 1) as usize].get((*col - r as i32 - 1) as usize))
        .filter(|&&seat| seat != '.')
        .map(|c| *c)
        .next()
        .unwrap_or_default()
        == '#';

    let down_right = (0..rows - *row as usize - 1)
        .filter_map(|r| seats[(*row + r as i32 + 1) as usize].get((*col + r as i32 + 1) as usize))
        .filter(|&&seat| seat != '.')
        .map(|c| *c)
        .next()
        .unwrap_or_default()
        == '#';

    let all = vec![
        up, down, left, right, up_left, up_right, down_left, down_right,
    ];

    all.iter().filter(|&&s| s).count()
}

fn main() -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string("input.txt")?;
    let seats: Vec<Vec<char>> = contents
        .lines()
        .map(|line| line.chars().collect::<Vec<char>>())
        .collect();

    part1(&seats);
    part2(&seats);

    Ok(())
}
