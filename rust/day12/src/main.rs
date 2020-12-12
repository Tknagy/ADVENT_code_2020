use std::error::Error;
use std::fs;

#[derive(Debug)]
enum Action {
    N,
    S,
    E,
    W,
    L,
    R,
    F,
}

#[derive(Debug)]
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
                let orig_dir = dir;
                dir.0 = ((command.arg as f32).to_radians().cos() * orig_dir.0 as f32).round()
                    as i64
                    - ((command.arg as f32).to_radians().sin() * orig_dir.1 as f32).round() as i64;
                dir.1 = ((command.arg as f32).to_radians().sin() * orig_dir.0 as f32).round()
                    as i64
                    + ((command.arg as f32).to_radians().cos() * orig_dir.1 as f32).round() as i64;
            }
            Action::R => {
                let orig_dir = dir;
                dir.0 = ((-command.arg as f32).to_radians().cos() * orig_dir.0 as f32).round()
                    as i64
                    - ((-command.arg as f32).to_radians().sin() * orig_dir.1 as f32).round() as i64;
                dir.1 = ((-command.arg as f32).to_radians().sin() * orig_dir.0 as f32).round()
                    as i64
                    + ((-command.arg as f32).to_radians().cos() * orig_dir.1 as f32).round() as i64;
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
                let orig_dir = (pos_waypoint.0 - pos_ship.0, pos_waypoint.1 - pos_ship.1);
                let dir_x = ((command.arg as f32).to_radians().cos() * orig_dir.0 as f32).round()
                    as i64
                    - ((command.arg as f32).to_radians().sin() * orig_dir.1 as f32).round() as i64;
                let dir_y = ((command.arg as f32).to_radians().sin() * orig_dir.0 as f32).round()
                    as i64
                    + ((command.arg as f32).to_radians().cos() * orig_dir.1 as f32).round() as i64;
                pos_waypoint.0 = pos_ship.0 + dir_x;
                pos_waypoint.1 = pos_ship.1 + dir_y;
            }
            Action::R => {
                let orig_dir = (pos_waypoint.0 - pos_ship.0, pos_waypoint.1 - pos_ship.1);
                let dir_x = ((-command.arg as f32).to_radians().cos() * orig_dir.0 as f32).round()
                    as i64
                    - ((-command.arg as f32).to_radians().sin() * orig_dir.1 as f32).round() as i64;
                let dir_y = ((-command.arg as f32).to_radians().sin() * orig_dir.0 as f32).round()
                    as i64
                    + ((-command.arg as f32).to_radians().cos() * orig_dir.1 as f32).round() as i64;
                pos_waypoint.0 = pos_ship.0 + dir_x;
                pos_waypoint.1 = pos_ship.1 + dir_y;
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
