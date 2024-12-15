// Thi is a file to parse exim logs. We need to find users with misconfigured user name and passwork who frequently get rejected by authenticator. 
// add nom crate to run this code. cargo add nom
use nom::bytes::complete::take_until;
use std::fs::read_to_string;
use std::io::{BufRead, BufReader};
use std::str::FromStr;

use nom::character::complete::{alphanumeric0, digit1};
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

#[derive(Serialize, Deserialize)]
struct Log {
    domain: String,
    date: String,
    time: String,
    user: String,
}
fn main() -> Result<(), std::io::Error> {
    //open file
    for line in read_to_string("rejectlog1").unwrap().lines() {
        match parse(line) {
            Ok(log_parsed) => println!("{}", user(log_parsed.0).unwrap().1),
            //ignore errors
            Err(e) => continue,
        }
    }
    Ok(())
}

fn test(i: &str) -> IResult<&str, &str> {
    recognize(terminated(take_until("set_id="), tag("set_id=")))(i)
}
fn date(i: &str) -> IResult<&str, Vec<u16>> {
    separated_list1(tag("-"), map_res(digit1, FromStr::from_str))(i)
}

fn time(i: &str) -> IResult<&str, Vec<u16>> {
    separated_list1(tag(":"), map_res(digit1, FromStr::from_str))(i)
}

fn parse(i: &str) -> IResult<&str, &str> {
    //(Vec<u16>, &str, Vec<u16>, &str,&str, &str, &str)
    recognize(tuple((
        date,
        space0,
        time,
        space0,
        alt((tag("plain"), tag("login"))),
        space0,
        tag("authenticator failed for"),
        recognize(terminated(take_until("set_id="), tag("set_id="))),
    )))(i)
}

fn user(i: &str) -> IResult<&str, &str> {
    alt((take_until("@"), rest))(i)
}
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn date_test() {
        assert_eq!(date("204-1-12"), Ok(("", vec![204u16, 1u16, 12u16])));
    }

    #[test]
    fn parse_test() {
        let log = "2024-12-11 19:30:45 plain authenticator failed for 126.115.126.78.rev.sfr.net [78.126.115.126]: 535 Incorrect authentication data (set_id=no-reply@sarzaminfile.ir";
        let remainder = "no-reply@sarzaminfile.ir";
        let parsed = "2024-12-11 19:30:45 plain authenticator failed for 126.115.126.78.rev.sfr.net [78.126.115.126]: 535 Incorrect authentication data (set_id=";
        println!("{:?}", test("this is a test set_id=1234").unwrap());
        assert_eq!(parse(log), Ok((remainder, parsed)));
    }
    fn user_test() {
        let remainder = "no-reply@sarzaminfile.ir";
        assert_eq!(user(remainder), Ok(("no-reply", "sarzaminfile.ir")));
    }
}
