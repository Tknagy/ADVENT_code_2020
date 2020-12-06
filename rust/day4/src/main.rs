use std::fs;

struct Passport {
    byr: Option<u32>,
    iyr: Option<u32>,
    eyr: Option<u32>,
    hgt: Option<String>,
    hcl: Option<String>,
    ecl: Option<String>,
    pid: Option<String>,
    cid: Option<u32>,
}

impl Passport {
    fn from(raw: &String) -> Passport {
        let mut pass = Passport {
            byr: Option::None,
            iyr: Option::None,
            eyr: Option::None,
            hgt: Option::None,
            hcl: Option::None,
            ecl: Option::None,
            pid: Option::None,
            cid: Option::None,
        };

        let pairs: Vec<&str> = raw.split_whitespace().collect();

        for pair in pairs {
            let mut split_separator = pair.split(':');
            let key = split_separator.next().unwrap();
            let value = split_separator.next().unwrap();

            match key {
                "byr" => pass.byr = Some(value.parse::<u32>().unwrap()),
                "iyr" => pass.iyr = Some(value.parse::<u32>().unwrap()),
                "eyr" => pass.eyr = Some(value.parse::<u32>().unwrap()),
                "hgt" => pass.hgt = Some(value.to_string()),
                "hcl" => pass.hcl = Some(value.to_string()),
                "ecl" => pass.ecl = Some(value.to_string()),
                "pid" => pass.pid = Some(value.to_string()),
                "cid" => pass.cid = Some(value.parse::<u32>().unwrap()),
                _ => panic!("unknown key"),
            }
        }

        pass
    }

    fn is_valid1(&self) -> bool {
        self.byr.is_some()
            && self.iyr.is_some()
            && self.eyr.is_some()
            && self.hgt.is_some()
            && self.hcl.is_some()
            && self.ecl.is_some()
            && self.pid.is_some()
    }

    fn is_valid2(&self) -> bool {
        let mut valid = true;

        valid &= match self.byr {
            Some(value) => 1920 <= value && value <= 2002,
            _ => false,
        };

        valid &= match self.iyr {
            Some(value) => 2010 <= value && value <= 2020,
            _ => false,
        };

        valid &= match self.eyr {
            Some(value) => 2020 <= value && value <= 2030,
            _ => false,
        };

        valid &= match &(self.hgt) {
            Some(value) => {
                let mut ret = false;
                if value.contains("cm") {
                    let height = value.split("cm").next().unwrap().parse::<u32>().unwrap();
                    ret = 150 <= height && height <= 193;
                } else if value.contains("in") {
                    let height = value.split("in").next().unwrap().parse::<u32>().unwrap();
                    ret = 59 <= height && height <= 76;
                }

                ret
            }
            _ => false,
        };

        valid &= match &(self.hcl) {
            Some(value) => {
                let mut ret = false;
                if value.contains("#") {
                    let hex = &value[1..];
                    let mut valid_c = true;
                    for c in hex.chars() {
                        valid_c &= ('0' <= c && c <= '9') || ('a' <= c && c <= 'f');
                    }

                    ret = hex.len() == 6 && valid_c;
                }

                ret
            }
            _ => false,
        };

        valid &= match &(self.ecl) {
            Some(value) => match value.as_str() {
                "amb" | "blu" | "brn" | "gry" | "grn" | "hzl" | "oth" => true,
                _ => false,
            },
            _ => false,
        };

        valid &= match &(self.pid) {
            Some(value) => match value.parse::<u32>() {
                Ok(_) => value.len() == 9,
                _ => false,
            },
            _ => false,
        };

        valid
    }
}

fn part1() {
    let contents = fs::read_to_string("input_curti_.txt").unwrap();
    let mut valid_passports = 0;

    for pass_str in contents.split("\n\n") {
        let passport = Passport::from(&String::from(pass_str));
        if passport.is_valid1() {
            valid_passports += 1;
        }
    }

    println!("{}", valid_passports);
}

fn part2() {
    let contents = fs::read_to_string("input_curti_.txt").unwrap();
    let mut valid_passports = 0;

    for pass_str in contents.split("\n\n") {
        let passport = Passport::from(&String::from(pass_str));
        if passport.is_valid2() {
            valid_passports += 1;
        }
    }

    println!("{}", valid_passports);
}

fn main() {
    part1();
    part2();
}
