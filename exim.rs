use chrono::DateTime;
use nom::bytes::complete::{take_until, take_while};
use nom::character::complete::{alphanumeric0, digit1};
use nom::AsChar;
use nom::{
    branch::alt,
    bytes::complete::{tag, take},
    character::complete::{anychar, char, multispace0, one_of, space0},
    combinator::{map, map_opt, map_res, recognize, rest, value, verify},
    error::{ErrorKind, ParseError},
    multi::{many1_count, separated_list1},
    number::complete::{double, u16},
    sequence::{delimited, preceded, separated_pair, terminated, tuple},
    IResult, Parser,
};
use serde::{Deserialize, Serialize};
use std::fs::read_to_string;
use std::io::{BufRead, BufReader};
use std::str::FromStr;
use tokio::signal::unix::{signal, SignalKind};

#[derive(Serialize, Deserialize, Default)]
struct Log {
    domain: String,
    date: String,
    time: String,
    user: String,
}
// we want to add support for reading domin from 1.hyper-server 2.standard-input
// https://blog.logrocket.com/a-minimal-web-service-in-rust-using-hyper
// https://hyper.rs
// interrupt signal handing via signal(SignalKind::interrupt())?;

#[tokio::main]
async fn main() -> Result<(), std::io::Error> {
    //open file
    for line in read_to_string("rejectlog1").unwrap().lines() {
        parse(line);
    }
    let mut sigint = signal(SignalKind::interrupt())?;
    let pid = std::process::id();
    println!("{pid}");
    loop {
        match sigint.recv().await {
            Some(_) => {
                println!("shutting down");
                return Ok(());
            }
            None => eprintln!("Stream terminated before receiving SIGINT signal"),
        }
    }
    Ok(())
}

fn test(i: &str) -> IResult<&str, &str> {
    recognize(terminated(take_until("set_id="), tag("set_id=")))(i)
}
fn date(i: &str) -> IResult<&str, &str> {
    recognize(separated_list1(tag("-"), digit1))(i)
}

fn time(i: &str) -> IResult<&str, &str> {
    recognize(separated_list1(tag(":"), digit1))(i)
}

fn parse(i: &str) -> Log {
    //(Vec<u16>, &str, Vec<u16>, &str,&str, &str, &str)
    let a = tuple((
        date,
        space0,
        time,
        space0,
        alt((tag("plain"), tag("login"))),
        space0,
        tag("authenticator failed for"),
        recognize(terminated(take_until("set_id="), tag("set_id="))),
    ))(i);

    match a {
        Ok(yes) => println!("time: {:?}", yes.0),
        Err(no) => {
            println!("Error Ocurred:{:?}", no)
        }
    }
    //take_while(is_username)
    Log::default()
}

fn is_username(c: char) -> bool {
    if c.is_alphanum() {
        return true;
    } else {
        for i in "-.?_".chars() {
            if i == c {
                return true;
            }
        }
    }

    false
}

#[cfg(test)]
mod tests {
    use chrono::{Date, NaiveDateTime};

    use super::*;

    #[test]
    fn date_test() {
        //   assert_eq!(date("204-1-12"), Ok(("", vec![204u16, 1u16, 12u16])));
    }

    #[test]
    fn parse_test() {
        let log = "2024-12-11 19:30:45 plain authenticator failed for 126.115.126.78.rev.sfr.net [78.126.115.126]: 535 Incorrect authentication data (set_id=no-reply@sarzaminfile.ir";
        let remainder = "no-reply@sarzaminfile.ir";
        let parsed = "2024-12-11 19:30:45 plain authenticator failed for 126.115.126.78.rev.sfr.net [78.126.115.126]: 535 Incorrect authentication data (set_id=";
        println!("{:?}", test("this is a test set_id=1234").unwrap());
        //   assert_eq!(parse(log), Ok((remainder, parsed)));
    }

    fn user_test() {
        let remainder = "no-reply@sarzaminfile.ir";
        //  assert_eq!(user(remainder), Ok(("no-reply", "sarzaminfile.ir")));
    }
    #[test]
    fn _1725_test() {
        assert_eq!(
            nom::number::complete::recognize_float::<_, (_, _)>("123episode"),
            Ok(("episode", "123"))
        );
    }

    #[test]
    fn parse_time() {
        assert_eq!(
            format!(
                "{:?}",
                DateTime::parse_from_str("2014-11-28 21:00:09 +09:00", "%Y-%m-%d %H:%M:%S %z")
            ),
            "2024-12-07"
        );
    }
}
