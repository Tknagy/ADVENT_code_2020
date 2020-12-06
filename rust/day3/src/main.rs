use std::fs;

fn part1() {
    let contents = fs::read_to_string("input.txt").unwrap();
    let n_rows = contents.lines().count();
    let n_cols = contents.lines().next().unwrap().chars().count();

    let rows: Vec<&str> = contents.lines().collect();

    let mut n_trees = 0;
    let mut current_row = 0;
    let mut current_col = 0;

    for row in rows {
        if row.chars().nth(current_col).unwrap() == '#' {
            n_trees += 1;
        }
        current_col += 3;
        current_row += 1;

        if current_col >= n_cols {
            current_col = current_col % n_cols;
        }

        if current_row >= n_rows {
            break;
        }
    }

    println!("{}", n_trees);
}

fn part2() {
    let contents = fs::read_to_string("input.txt").unwrap();
    let n_rows = contents.lines().count();
    let n_cols = contents.lines().next().unwrap().chars().count();

    let rows: Vec<&str> = contents.lines().collect();

    let n_trees = |stride_row, stride_col| -> u128 {
        let mut counter = 0;
        let mut current_row = stride_row;
        let mut current_col = stride_col;

        loop {
            let row: &str = rows[current_row];
            if row.chars().nth(current_col).unwrap() == '#' {
                counter += 1;
            }

            current_col += stride_col;
            current_row += stride_row;

            current_col = current_col % n_cols;

            if current_row >= n_rows {
                break;
            }
        }

        counter
    };

    let n1 = n_trees.clone()(1, 1);
    let n2 = n_trees.clone()(1, 3);
    let n3 = n_trees.clone()(1, 5);
    let n4 = n_trees.clone()(1, 7);
    let n5 = n_trees.clone()(2, 1);

    println!("{}", n1 * n2 * n3 * n4 * n5);
}

fn main() {
    //part1();
    part2();
}
