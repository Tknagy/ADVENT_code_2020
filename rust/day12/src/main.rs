use std::error::Error;
use std::fs;

enum Action {
    N,
    S,
    E,
    W,
    L,
    R,
    F,
}

struct Command {
    action: Action,
    arg: i64,
}

impl Command {
    fn from(raw: &String) -> Self {
        let mut raw_chars = raw.chars();
        let action = match raw_chars.next().unwrap() {
            'N' => Action::N,
            'S' => Action::S,
            'E' => Action::E,
            'W' => Action::W,
            'L' => Action::L,
            'R' => Action::R,
            'F' => Action::F,
            _ => panic!(),
        };

        Self {
            action,
            arg: raw.chars().as_str()[1..].parse::<i64>().unwrap(),
        }
    }
}

fn rotate(dir: &(i64, i64), degrees: &i64) -> (i64, i64) {
    let orig_dir = dir;

    (
        ((*degrees as f32).to_radians().cos() * orig_dir.0 as f32).round() as i64
            - ((*degrees as f32).to_radians().sin() * orig_dir.1 as f32).round() as i64,
        ((*degrees as f32).to_radians().sin() * orig_dir.0 as f32).round() as i64
            + ((*degrees as f32).to_radians().cos() * orig_dir.1 as f32).round() as i64,
    )
}

fn part1(commands: &Vec<Command>) {
    let mut pos = (0, 0);
    let mut dir = (1, 0);

    for command in commands {
        match command.action {
            Action::F => {
                pos.0 += dir.0 * command.arg;
                pos.1 += dir.1 * command.arg;
            }
            Action::N => {
                pos.1 += command.arg;
            }
            Action::S => {
                pos.1 -= command.arg;
            }
            Action::E => {
                pos.0 += command.arg;
            }
            Action::W => {
                pos.0 -= command.arg;
            }
            Action::L => {
                dir = rotate(&dir, &command.arg);
            }
            Action::R => {
                dir = rotate(&dir, &-command.arg);
            }
        }
    }

    println!("{}", pos.0.abs() + pos.1.abs());
}

fn part2(commands: &Vec<Command>) {
    let mut pos_ship = (0, 0);
    let mut pos_waypoint = (10, 1);

    for command in commands {
        match command.action {
            Action::F => {
                let relative = (pos_waypoint.0 - pos_ship.0, pos_waypoint.1 - pos_ship.1);
                pos_ship.0 += (pos_waypoint.0 - pos_ship.0) * command.arg;
                pos_ship.1 += (pos_waypoint.1 - pos_ship.1) * command.arg;
                pos_waypoint.0 = relative.0 + pos_ship.0;
                pos_waypoint.1 = relative.1 + pos_ship.1;
            }
            Action::N => {
                pos_waypoint.1 += command.arg;
            }
            Action::S => {
                pos_waypoint.1 -= command.arg;
            }
            Action::E => {
                pos_waypoint.0 += command.arg;
            }
            Action::W => {
                pos_waypoint.0 -= command.arg;
            }
            Action::L => {
                let dir = (pos_waypoint.0 - pos_ship.0, pos_waypoint.1 - pos_ship.1);
                let dir = rotate(&dir, &command.arg);
                pos_waypoint.0 = pos_ship.0 + dir.0;
                pos_waypoint.1 = pos_ship.1 + dir.1;
            }
            Action::R => {
                let dir = (pos_waypoint.0 - pos_ship.0, pos_waypoint.1 - pos_ship.1);
                let dir = rotate(&dir, &-command.arg);
                pos_waypoint.0 = pos_ship.0 + dir.0;
                pos_waypoint.1 = pos_ship.1 + dir.1;
            }
        }
    }

    println!("{}", pos_ship.0.abs() + pos_ship.1.abs());
}

fn main() -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string("input.txt")?;
    let commands: Vec<Command> = contents
        .lines()
        .map(|line| Command::from(&String::from(line)))
        .collect();
    part1(&commands);
    part2(&commands);

    Ok(())
}
