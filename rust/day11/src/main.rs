use std::cmp::{max, min};
use std::error::Error;
use std::fs;

fn get_adjacent_occupied(seats: &Vec<Vec<char>>, row: &i32, col: &i32) -> usize {
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

    adjacent.iter().filter(|&&s| s == '#').count()
}

fn get_dirs_occupied(seats: &Vec<Vec<char>>, row: &i32, col: &i32) -> usize {
    let rows = seats.len();
    let cols = seats.first().unwrap().len();

    let dirs = vec![
        (-1, -1),
        (-1, 0),
        (-1, 1),
        (0, -1),
        (0, 1),
        (1, -1),
        (1, 0),
        (1, 1),
    ];

    let mut dirs_occupied = 0;
    for dir in dirs {
        let mut r = row + dir.0;
        let mut c = col + dir.1;

        while r >= 0 && r < rows as i32 && c >= 0 && c < cols as i32 {
            match seats[r as usize][c as usize] {
                'L' => break,
                '#' => {
                    dirs_occupied += 1;
                    break;
                }
                _ => {
                    r += dir.0;
                    c += dir.1;
                }
            }
        }
    }

    return dirs_occupied;
}

fn part1(seats: &Vec<Vec<char>>) {
    exec(seats, get_adjacent_occupied, 4);
}

fn part2(seats: &Vec<Vec<char>>) {
    exec(seats, get_dirs_occupied, 5);
}

fn exec(
    seats: &Vec<Vec<char>>,
    occupied_fn: impl Fn(&Vec<Vec<char>>, &i32, &i32) -> usize,
    tolerance: usize,
) {
    let rows = seats.len();
    let cols = seats.first().unwrap().len();

    let mut prev_seats: Vec<Vec<char>> = Vec::new();
    let mut new_seats = seats.to_vec();

    while prev_seats != new_seats {
        prev_seats = new_seats.to_vec();
        for i in 0..rows {
            for j in 0..cols {
                let dirs_occupied = occupied_fn(&prev_seats, &(i as i32), &(j as i32));

                match prev_seats[i][j] {
                    'L' => {
                        if dirs_occupied == 0 {
                            new_seats[i][j] = '#';
                        }
                    }
                    '#' => {
                        if dirs_occupied >= tolerance {
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
