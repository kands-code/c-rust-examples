use crate::utils::tools::{get_input_vec, Size};
use std::io::Write;

#[derive(Debug)]
pub struct Matrix {
    pub data: Vec<f64>,
    pub size: Size,
}

impl Matrix {
    pub fn new(r: usize, c: usize) -> Self {
        Matrix {
            data: vec![0.0; r * c],
            size: Size {
                row: r.clone(),
                col: c.clone(),
            },
        }
    }

    pub fn from(size: (usize, usize), data: Vec<f64>) -> Result<Matrix, &'static str> {
        if data.len() < size.0 * size.1 {
            Err("Size is too big!")
        } else {
            Ok(Matrix {
                data,
                size: Size {
                    row: size.0,
                    col: size.1,
                },
            })
        }
    }

    /// get a matrix by user input
    ///
    /// # Warning
    ///
    /// can only input on the same line, separated by spaces
    ///
    /// such as:
    /// ```text
    /// Input a size:
    /// 2 2
    /// Input data:
    /// 1 2 3 4
    /// ```
    pub fn from_input() -> Result<Matrix, &'static str> {
        println!("Input a size:");
        std::io::stdout().flush().unwrap();
        let size = get_input_vec::<usize>();
        if size.len() < 2 {
            return Err("Too few parameters!");
        }
        let size = Size {
            row: size[0],
            col: size[1],
        };
        println!("Input data:");
        std::io::stdout().flush().unwrap();
        let data = get_input_vec::<f64>();
        Ok(Matrix { size, data })
    }

    pub fn get(&self, r: usize, c: usize) -> Option<f64> {
        if r > self.size.row || c > self.size.col {
            None
        } else {
            Some(self.data[(r - 1) * self.size.col + (c - 1)])
        }
    }

    pub fn set(&mut self, r: usize, c: usize, val: f64) {
        if r > self.size.row || c > self.size.col {
            panic!("Out of size!");
        }
        self.data[(r - 1) * self.size.col + (c - 1)] = val;
    }

    pub fn size(&self) -> (usize, usize) {
        (self.size.row, self.size.col)
    }

    pub fn diagonal(&self) -> Vec<f64> {
        let mut diag: Vec<f64> = Vec::new();
        let len = self.size.row.max(self.size.col);

        for i in 1..=len {
            diag.push(self.get(i, i).unwrap());
        }
        diag
    }

    pub fn tr(&self) -> f64 {
        self.diagonal().iter().sum()
    }

    pub fn det(&self) -> Option<f64> {
        if self.size.row != self.size.col {
            None
        } else {
            Some(1.0)
        }
    }
}

impl std::fmt::Display for Matrix {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "<| Matrix")?;
        for i in 1..=self.size.row {
            write!(f, "[ ")?;
            for j in 1..=self.size.col {
                write!(f, "{:7.3} ", self.get(i, j).unwrap())?;
            }
            writeln!(f, "]")?;
        }
        writeln!(f, "|> Matrix")
    }
}

impl Eq for Matrix {}

impl PartialEq for Matrix {
    fn eq(&self, other: &Self) -> bool {
        self.data == other.data && self.size == other.size
    }
}

impl Clone for Matrix {
    fn clone(&self) -> Self {
        Self {
            data: self.data.clone(),
            size: self.size.clone(),
        }
    }
}

impl std::ops::Add for Matrix {
    type Output = Result<Matrix, &'static str>;
    fn add(self, rhs: Self) -> Self::Output {
        let mut data: Vec<f64> = Vec::new();
        if rhs.size != self.size {
            Err("Size mismatch!")
        } else {
            for i in 0..(self.size.row * self.size.col) {
                data.push(self.data[i] + rhs.data[i]);
            }
            Ok(Matrix {
                size: Size {
                    col: self.size.col,
                    row: self.size.row,
                },
                data,
            })
        }
    }
}

impl std::ops::Mul for Matrix {
    type Output = Result<Matrix, &'static str>;

    fn mul(self, rhs: Self) -> Self::Output {
        if self.size.col != rhs.size.row {
            Err("Size mismatch!")
        } else {
            let mut data = vec![0.0; self.size.row * rhs.size.col];
            for i in 1..=self.size.row {
                for j in 1..=self.size.col {
                    for k in 1..=rhs.size.col {
                        data[(i - 1) * rhs.size.col + (k - 1)] +=
                            self.get(i, j).unwrap() * rhs.get(j, k).unwrap();
                    }
                }
            }
            Ok(Matrix {
                data,
                size: Size {
                    row: self.size.row,
                    col: rhs.size.col,
                },
            })
        }
    }
}
