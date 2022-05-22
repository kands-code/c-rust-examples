use types::matrix::Matrix;

mod types;
mod utils;

fn main() {
    let m = Matrix::from_input().unwrap();
    println!("{}", m);
}
