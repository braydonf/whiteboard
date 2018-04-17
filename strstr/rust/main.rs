// rustc -o main main.rs

static GREEN: &str = "\x1B[32m";
static RED: &str = "\x1B[31m";
static RESET: &str = "\x1b[0m";

fn strstr(haystack: String, needle: String) -> Option<String> {
    let nl = needle.len();
    let hl = haystack.len();
    if (nl == 0) | (hl == 0) || (nl > hl) {
        return None
    }
    for i in 0 .. hl - nl + 1 {
        if haystack[i..i + nl] == needle[..] {
            return Some(String::from(&haystack[i..]));
        }
    }
    return None;
}

fn test_strstr(haystack: String, needle: String, expected: Option<String>, index: u32) -> bool {
    let found = strstr(haystack, needle);
    if found == expected {
        println!("{}passed{} for {}: result: {:?}",
                 GREEN, RESET, index, found);
        return true;
    } else {
        println!("{}failed{} for {}: result: {:?}, expected: {:?}",
                 RED, RESET, index, found, expected);
        return false;
    }
}

fn main() {
    let mut failed = 0;
    let mut status = 0;

    if test_strstr(String::from("some of the words that are random"),
                   String::from("that"),
                   Some(String::from("that are random")),
                   0) {
        failed += 1;
    }

    if test_strstr(String::from("some more words ending with a t"),
                   String::from("that"),
                   None,
                   1) {
        failed += 1;
    }

    if test_strstr(String::from("therefore than this thanks that"),
                   String::from("that"),
                   Some(String::from("that")),
                   2) {
        failed += 1;
    }

    if test_strstr(String::from("haystack"),
                   String::from("h"),
                   Some(String::from("haystack")),
                   3) {
        failed += 1;
    }

    if test_strstr(String::from("n"),
                   String::from("needle"),
                   None,
                   4) {
        failed += 1;
    }

    if test_strstr(String::from(""),
                   String::from("overflow"),
                   None,
                   5) {
        failed += 1;
    }

    if test_strstr(String::from("overflow"),
                   String::from(""),
                   None,
                   6) {
        failed += 1;
    }

    if failed > 0 { status = 1 }

    std::process::exit(status);
}
