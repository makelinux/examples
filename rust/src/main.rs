// system packages: rust-all rust-src

fn main() {
    // to stdout:
    print!("output");
    println!(" + new line");
    // to stderr:
    eprint!("error");
    eprintln!(" + new line");
}

#[test]
fn constants() {
    fn func(arg: i32) -> i32 {
        // immutable: arg += 1;
        arg + 1 // last value is return value
    }

    assert_eq!(func(1), 2);
    let logical: bool;
    logical = true;
    assert!(logical);

    let int: i32 = 100;
    assert_eq!(int, 100);
}

#[test]
fn sample_test() {
    assert_eq!(format!("{}", 0xf), "15");

    let mut variable = 1; // mutable means variable

    variable += 1;
    assert_eq!(variable, 2);
}

#[test]
fn casting_test() {
    let decimal = 65.4321_f32;
    let integer = decimal as u8;
    let character = integer as char;
    assert_eq!(character, 'A');
}

#[test]
fn types_test() {
    let elem = 5; // i32 by default
    let mut vec = Vec::new(); // generic vector declaration
    vec.push(elem);

    // formatting debug representation
    assert_eq!(format!("{:?}", vec), "[5]");

    #[allow(dead_code)]
    type NanoSecond = u64; // type alias

    let my_str;
    my_str = "1"; // like char* in C

    #[allow(unused_assignments)]
    let mut my_string = String::from(my_str);

    my_string = my_str.into();
    assert_eq!(my_string, "1");

    let s2 = my_string.clone();
    assert_eq!(s2, "1");

    my_string = "aaa".to_string();
    assert!(!my_string.is_empty());
}

#[test]
fn parsing_test() {
    // inferred type
    let parsed1: i32 = "5".parse().unwrap();
    // explicit type
    let parsed2 = "5".parse::<i32>().unwrap();
    assert_eq!(parsed1, parsed2);
}

#[test]
fn controls_test() {
    if 1 > 0 {
    } else {
    };
    // blocks are expressions, the last expression without ';' is a return value
    let mut res = {
        let a = 1;
        a // without ';'
    };
    assert_eq!(res, 1);
    assert_eq!({}, ()); // like void return value in C

    res = if 1 > 0 { 2 } else { 3 };
    assert_eq!(res, 2);

    // like switch in C
    match true {
        // like case in C
        true => assert!(true),
        _ => assert!(false),
    };
}

#[test]
fn loops() {
    // match as expression
    let m = match 1 {
        0 => 0,
        _ => 1, // default match
    };
    assert_eq!(m, 1);

    loop {
        break;
    }

    while false {
        continue;
    }

    for n in 0..10 {
        assert!(n < 10);
    }

    for n in 1..=10 {
        assert!(n <= 10);
    }
}

#[test]
fn references() {
    let reference1 = &4;
    let ref reference2 = 4;
    // dereferencing
    assert_eq!(*reference1, 4);
    assert_eq!(*reference2, 4);
    let &val = reference1;
    assert_eq!(val, 4);

    let s1: &str = "abc"; // like char*
    let ref s2 = *"abc"; // like char*
    assert_eq!(s1, s2);
}

#[test]
fn data_structures() {
    // classsic struct

    #[allow(dead_code)]
    #[derive(Debug)] // requried for `format!("{:?}", p)`
    struct Person {
        name: String,
        age: u8,
    }

    let p = Person {
        name: "Peter".to_string(),
        age: 27,
    };
    assert_eq!(format!("{:?}", p), "Person { name: \"Peter\", age: 27 }");
}

#[test]
fn tuples() {
    // A tuple struct

    #[derive(Debug)]
    struct Pair(i32, f32);
    let pair = Pair(1, 0.1);
    assert_eq!(format!("{:?}", pair), "Pair(1, 0.1)");
    // destruction (decomposition)
    assert_eq!(pair.0, 1);
    assert_eq!(pair.1, 0.1);
    let Pair(integer, decimal) = pair;
    assert_eq!(integer, 1);
    assert_eq!(decimal, 0.1);
    static GLOBAL: i32 = 1; // statics need to be upppercase
    assert_eq!(GLOBAL, 1);

    // generics are like template in C++

    struct SampleGeneric<T>(T); // generic tuple
    let _char = SampleGeneric('a');
    assert_eq!(_char.0, 'a');
}

#[test]
fn traits() {
    // a trait is like an intrafce, can contain virtual functions
    trait Zero {
        const ZERO: Self;
        fn is_zero(&self) -> bool;
    }

    // implemenataions must implement their interface
    impl Zero for i32 {
        const ZERO: Self = 0;

        fn is_zero(&self) -> bool {
            *self == Self::ZERO
        }
    }

    assert_eq!(i32::ZERO, 0);
    assert!(i32::ZERO.is_zero());
    assert!(!4.is_zero());
}

#[test]
fn destructor_test() {
    static mut DROPPED: bool = false;
    struct Droppper;
    impl Drop for Droppper {
        // destructor
        fn drop(&mut self) {
            unsafe {
                // because `static mut` is unsafe
                DROPPED = true; // must be static (global)
            }
        }
    }
    {
        let _x = Droppper;
    }
    unsafe { assert!(DROPPED) };
}

#[test]
fn options() {
    let x: Option<u32> = Some(2);
    assert_eq!(x.is_some(), true);

    let x: Option<u32> = None;
    assert_eq!(x.is_some(), false);
}

#[test]
fn raw_pointers() {
    let mut var: i32 = 3;
    let ptr: *mut i32 = &mut var;
    unsafe {
        if !ptr.is_null() {
            assert_eq!(*ptr, 3);
        }
    }
}

#[test]
fn scope() {
    let mut a = String::from("a");
    fn delete(_arg: String) {
        // argument is moved end deleted by destructor
    }
    if false {
        delete(a); // the value is moved here even under the "if false"
    }
    // value of a is unusable here
    a = "1".to_string();
    let c = a;
    // value of a is unusable here
    assert_eq!(c, "1")
}

#[test]
fn mutable_function_argument() {
    let mut a = String::from("a");
    fn append(arg: &mut String, s: &str) {
        arg.push_str(s);
        // immutable: arg += 1;
        //arg + 1 // last value is return value
    }
    append(&mut a, "b");
    append(&mut a, "c");
    assert_eq!(a, "abc");
}

#[test]
#[ignore]
fn failing_test() {
    assert!(false)
}

