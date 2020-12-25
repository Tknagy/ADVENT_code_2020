use std::error::Error;
use std::fs;

fn main() -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string("input.txt")?;
    let config = day16::parse(contents.as_str());
    println!("{}", day16::part1(&config));
    println!("{}", day16::part2(&config));

    Ok(())
}
