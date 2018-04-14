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

fn deep_copy(original: &BNode) -> BNode {
    match original {
        Some(x) => {
            return new_bnode(x.value, deep_copy(&x.left), deep_copy(&x.right))
        },
        None => None
    }
}

fn test_new_btree() -> BNode {
    return new_bnode(
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
}

fn test_check_btree(node: BNode)
{
}

fn main() {
    let node = test_new_btree();
    let copy = deep_copy(&node);
    test_check_btree(copy);
}
