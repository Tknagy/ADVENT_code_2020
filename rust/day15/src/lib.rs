use std::collections::{HashMap, VecDeque};

pub fn sol(input_numbers: &Vec<usize>, limit: usize) -> usize {
    let current_turn = input_numbers.len() + 1;
    let mut current_spoken = *input_numbers.last().unwrap();

    let mut spoken_turns = input_numbers
        .iter()
        .enumerate()
        .map(|(turn, n)| (*n, VecDeque::from(vec![turn + 1])))
        .collect::<HashMap<usize, VecDeque<usize>>>();
    spoken_turns.remove_entry(&current_spoken);

    for turn in current_turn..=limit {
        let last_spoken = current_spoken;
        if spoken_turns.contains_key(&last_spoken) {
            spoken_turns
                .get_mut(&last_spoken)
                .unwrap()
                .push_back(turn - 1);
            current_spoken = spoken_turns[&last_spoken].iter().nth_back(0).unwrap()
                - spoken_turns[&last_spoken].iter().nth_back(1).unwrap();
            spoken_turns.get_mut(&last_spoken).unwrap().pop_front();
        } else {
            spoken_turns.insert(last_spoken, VecDeque::from(vec![turn - 1]));
            current_spoken = 0;
        }
    }

    current_spoken
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part1_demo() {
        assert_eq!(sol(&vec![0, 3, 6], 2020), 436);
        assert_eq!(sol(&vec![1, 3, 2], 2020), 1);
        assert_eq!(sol(&vec![2, 1, 3], 2020), 10);
        assert_eq!(sol(&vec![3, 2, 1], 2020), 438);
    }

    #[test]
    fn part2_demo1() {
        assert_eq!(sol(&vec![0, 3, 6], 30000000), 175594);
    }

    #[test]
    fn part2_demo2() {
        assert_eq!(sol(&vec![1, 3, 2], 30000000), 2578);
    }

    #[test]
    fn part2_demo3() {
        assert_eq!(sol(&vec![3, 2, 1], 30000000), 18);
    }
}
