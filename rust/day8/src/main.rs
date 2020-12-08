use std::collections::HashSet;
use std::fs;

#[derive(Clone)]
enum InstructionType {
    NOP,
    ACC,
    JMP,
}

#[derive(Clone)]
struct Instruction {
    itype: InstructionType,
    arg: i32,
}

struct State {
    pc: u32,
    acc: i32,
}

impl Instruction {
    fn from(instruction_str: &str) -> Self {
        let mut split = instruction_str.split_whitespace();
        let type_str = split.next().unwrap();
        let itype = match type_str {
            "nop" => InstructionType::NOP,
            "acc" => InstructionType::ACC,
            "jmp" => InstructionType::JMP,
            _ => panic!("unknown instruction type"),
        };
        let arg = split.next().unwrap().parse::<i32>().unwrap();

        Self { itype, arg }
    }
}

fn part1(instructions: &Vec<Instruction>) {
    let mut state = State { pc: 0, acc: 0 };
    let mut visited_pcs: HashSet<u32> = HashSet::new();

    loop {
        let instruction = &instructions[state.pc as usize];
        if !visited_pcs.insert(state.pc) {
            println!("{}", state.acc);
            break;
        }
        match &instruction.itype {
            InstructionType::NOP => state.pc += 1,
            InstructionType::ACC => {
                state.acc += instruction.arg;
                state.pc += 1
            }
            InstructionType::JMP => state.pc = (state.pc as i32 + instruction.arg) as u32,
        }
    }
}

fn part2(original_instructions: &Vec<Instruction>) {
    let jmps_nops_indices: Vec<usize> = original_instructions
        .iter()
        .enumerate()
        .map(|(i, inst)| match inst.itype {
            InstructionType::JMP | InstructionType::NOP => Some(i),
            _ => None,
        })
        .filter(|i| i.is_some())
        .flat_map(|i| i)
        .collect();

    for i in jmps_nops_indices {
        let mut instructions: Vec<Instruction> = original_instructions.to_vec();

        match instructions[i].itype {
            InstructionType::JMP => instructions[i].itype = InstructionType::NOP,
            InstructionType::NOP => instructions[i].itype = InstructionType::JMP,
            _ => {}
        }

        let mut state = State { pc: 0, acc: 0 };
        let mut visited_pcs: HashSet<u32> = HashSet::new();

        let terminates = {
            let mut result = false;
            loop {
                if state.pc as usize >= instructions.len() {
                    result = true;
                    break;
                }

                let instruction = &instructions[state.pc as usize];
                if !visited_pcs.insert(state.pc) {
                    break;
                }
                match &instruction.itype {
                    InstructionType::NOP => state.pc += 1,
                    InstructionType::ACC => {
                        state.acc += instruction.arg;
                        state.pc += 1
                    }
                    InstructionType::JMP => state.pc = (state.pc as i32 + instruction.arg) as u32,
                }
            }
            result
        };

        if terminates {
            println!("{}", state.acc);
        }
    }
}

fn main() {
    let contents = fs::read_to_string("input.txt").unwrap();
    let instructions: Vec<Instruction> = contents
        .lines()
        .map(|line| Instruction::from(line))
        .collect();
    part1(&instructions);
    part2(&instructions);
}
