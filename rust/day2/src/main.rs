use std::fs;

fn hue() {
    let contents = fs::read_to_string("input.txt").unwrap();
    let mut valid_pws = 0;

    for line in contents.lines() {
        let minus_idx = line.find("-").unwrap();
        let space_idx = line.find(" ").unwrap();
        let points_idx = line.find(":").unwrap();

        let min = &line[0..minus_idx].parse::<usize>().unwrap();
        let max = &line[minus_idx + 1..space_idx].parse::<usize>().unwrap();
        let letter = &line[points_idx - 1..points_idx]
            .to_string()
            .chars()
            .nth(0)
            .unwrap();

        let pw: String = line.split(" ").last().unwrap().to_string();

        if (&pw.chars().nth(min - 1).unwrap() == letter
            && &pw.chars().nth(max - 1).unwrap() != letter)
            || (&pw.chars().nth(min - 1).unwrap() != letter
                && &pw.chars().nth(max - 1).unwrap() == letter)
        {
            valid_pws += 1;
        }
    }

    println!("Valid pws: {}", valid_pws);
}

fn main() {
    hue()
}
