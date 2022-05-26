use types::matrix::Matrix;
use crate::utils::tools::permutation;

mod types;
mod utils;

fn main() {
    let m = Matrix::from_input().unwrap();
    println!("{}", m);

    println!("{:?}", permutation(&vec![1, 2, 4, 5]));
}
