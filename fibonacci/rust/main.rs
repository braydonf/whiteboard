fn fib(n: usize) -> u64 {
    if n == 0 {
        return 0;
    }

    let mut prev: u64 = 0;
    let mut next: u64 = 1;
    let mut i: usize = 1;

    while i < n {
        let _prev: u64 = prev;
        prev = next;
        next = _prev + next;
        i += 1;
    }

    return next;
}

fn main() {
    let green = "\x1B[32m";
    let red = "\x1B[31m";
    let reset = "\x1b[0m";

    let expected : [u64; 51] = [0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,5702887,9227465,14930352,24157817,39088169,63245986,102334155,165580141,267914296,433494437,701408733,1134903170,1836311903,2971215073,4807526976,7778742049,12586269025];

    for n in 1..51 as usize {
        let result = fib(n);

        if result != expected[n] {
            println!("{}failed{} for {}, actual: {}, expected: {}", red, reset, n, result, expected[n]);
        } else {
            println!("{}passed{} for {}, actual: {}", green, reset, n, result);
        }

    }
}
