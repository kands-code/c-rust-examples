pub mod Vector {
    use std::ops::{AddAssign, Mul};

    #[derive(Debug, PartialEq, Eq)]
    pub struct Vector<T> {
        data: Vec<T>,
        orient: char,
    }
    pub fn dot_product<T>(v1: &Vector<T>, v2: &Vector<T>) -> T
    where
        T: Mul<Output = T>,
        T: AddAssign,
    {
        assert!(v1.data.len() == v2.data.len() && v1.orient == v2.orient);
        let mut res: T;
        for i in 0..v1.data.len() {
            res += v1.data[i] * v2.data[i];
        }
        return res;
    }
}
