struct INode {
    left: Option<Box<INode>>,
    right: Option<Box<INode>>,
    value: u64
}

type BNode = Option<Box<INode>>;

fn new_bnode(value: u64, left: BNode, right: BNode) -> BNode {
    Some(Box::new(INode {
        left: left,
        right: right,
        value: value
    }))
}

fn deep_copy(node: &BNode) -> BNode {
    match node {
        Some(x) => {
            return new_bnode(x.value, deep_copy(&x.left), deep_copy(&x.right))
        },
        None => None
    }
}

fn deep_compare(a: &BNode, b: &BNode) -> bool {
    match (a, b) {
        (Some(_a), Some(_b)) => {
            if _a.value != _b.value {
                return false;
            }
            if !deep_compare(&_a.left, &_b.left) || !deep_compare(&_a.right, &_b.right) {
                return false;
            }
            return true;
        },
        (Some(_a), None) => false,
        (None, Some(_b)) => false,
        (None, None) => true
    }
}

fn main() {
    let node = new_bnode(
        10,
        new_bnode(
            6,
            new_bnode(
                3,
                new_bnode(
                    1,
                    None,
                    None
                ),
                None
            ),
            new_bnode(
                7,
                None,
                None
            )
        ),
        new_bnode(
            18,
            None,
            None
        )
    );

    let copy = deep_copy(&node);
    let same = deep_compare(&node, &copy);

    let mut status: i32 = 0;
    let green = "\x1B[32m";
    let red = "\x1B[31m";
    let reset = "\x1b[0m";

    if !same {
        println!("{}failed{}", red, reset);
        status = 1;
    } else {
        println!("{}passed{}", green, reset);
    }

    std::process::exit(status);
}
