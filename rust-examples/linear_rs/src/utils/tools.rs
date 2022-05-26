use std::io::BufRead;

pub fn permutation<T>(v: &Vec<T>) -> Vec<Vec<T>>
    where
        T: Clone,
{
    let mut elem = v.clone();
    let mut perm: Vec<Vec<T>> = Vec::new();
    perm.push(elem.clone());
    for _ in 1..v.len() {
        let mut s = elem[1..].to_vec();
        s.push(elem[0].clone());
        perm.push(s.clone());
        elem = s;
    }
    perm
}

pub fn get_input_vec<T>() -> Vec<T>
    where
        T: std::str::FromStr,
        <T as std::str::FromStr>::Err: std::fmt::Debug,
{
    std::io::stdin()
        .lock()
        .lines()
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| -> T { x.parse::<T>().expect("Not a valid input!") })
        .collect::<Vec<_>>()
}

#[derive(Debug)]
pub struct Size {
    pub row: usize,
    pub col: usize,
}

impl Eq for Size {}

impl PartialEq for Size {
    fn eq(&self, other: &Self) -> bool {
        self.row == other.row && self.col == other.col
    }
}

impl Clone for Size {
    fn clone(&self) -> Self {
        Self {
            row: self.row.clone(),
            col: self.col.clone(),
        }
    }
}

impl Copy for Size {}
