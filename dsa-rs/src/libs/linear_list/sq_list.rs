use std::vec;

#[derive(Eq, PartialEq, Debug)]
pub struct SqList<E> {
    data: vec::Vec<E>,
}

impl<E> SqList<E> {
    pub const fn new() -> SqList<E> {
        SqList {
            data: vec::Vec::new(),
        }
    }

    pub fn from_arr(arr: &[E]) -> SqList<E> {}
}
