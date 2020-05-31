use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

/*
 *  An attempt to write some Rust with a vector of bools. Given the memory usage this
    is not a very efficient way of doing this, and some kind of custom bitset is probably
    needed. There seemed to have been a bitset in Rust, which was removed from the standard
    library some time after 1.2
 */

fn main() {
    let mut s = vec![false; 10000000];
    if let Ok(lines) = read_lines("/Users/rob/data.txt") {
        // Consumes the iterator, returns an (Optional) String
        for line in lines {
            if let Ok(num) = line {
                s[num.parse::<usize>().expect("Bad parse")] = true;
            }
        }
    }
    for (i, x) in s.iter().enumerate() {
        println!("{}", i);
    }
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

