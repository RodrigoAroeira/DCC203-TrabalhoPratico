use std::{error::Error, str::Lines};

use crate::{pokemon::Pokemon, trainer::Trainer};

pub type PokemonResult<T> = Result<T, Box<dyn Error>>;

pub fn get_super_effective(ty: &str) -> PokemonResult<String> {
    let counter = match ty {
        "electric" => "water",
        "water" => "fire",
        "fire" => "ice",
        "ice" => "rock",
        "rock" => "electric",
        _ => Err(format!("Type {ty} not found."))?,
    };

    Ok(counter.to_string())
}

fn print_overview(trainers: &[Trainer; 2]) {
    for (i, t) in trainers.iter().enumerate() {
        if t.winner() {
            println!("Player {} won", i + 1);
            println!("Surviving pokemon:");
            for pokemon in t.pokemons() {
                if pokemon.alive() {
                    println!("{}", pokemon.name());
                }
            }
        }
    }

    println!("Defeated pokemon:");
    for t in trainers {
        for pokemon in t.pokemons() {
            if !pokemon.alive() {
                println!("{}", pokemon.name())
            }
        }
    }
}

pub fn read_trainers(filename: &str) -> PokemonResult<[Trainer; 2]> {
    let Ok(contents) = std::fs::read_to_string(filename) else {
        Err(format!("Error while opening {filename:}"))?
    };

    let mut lines = contents.lines();
    let [n1, n2]: [usize; 2] = {
        let Some(first_line) = lines.next() else {
            Err(format!("File {filename} is empty"))?
        };
        let mut parts = first_line.split_whitespace();
        let Some(n1) = parts.next().and_then(|s| s.parse().ok()) else {
            Err(format!("Error while reading line {first_line:?}"))?
        };

        let Some(n2) = parts.next().and_then(|s| s.parse().ok()) else {
            Err(format!("Error while reading line {first_line:?}"))?
        };

        let res = [n1, n2];
        for &n in res.iter() {
            if n == 0 || n > 100 {
                let msg = format!("Number of pokemon must be in range (0, 100]. Given: {}", n);
                Err(msg)?
            }
        }

        res
    };

    fn get_pokemons(n: usize, lines: &mut Lines<'_>) -> PokemonResult<Vec<Pokemon>> {
        let mut pokemons = Vec::new();
        for _ in 0..n {
            let Some(line) = lines.next() else {
                Err("File doesn't have enough lines for each pokemon")?
            };
            let parts: Vec<&str> = line.split_whitespace().collect();
            if parts.len() < 5 {
                Err(format!("Line {line:?} doesn't have all necessary elements"))?
            } else if parts.len() > 5 {
                eprintln!(
                    "WARNING: Line {line:?} has more than 5 elements. Ignoring extra elements."
                )
            }

            let name = parts[0].to_string();
            let attack: f32 = parts[1].parse()?;
            let defense: f32 = parts[2].parse()?;
            let hp: f32 = parts[3].parse()?;
            let ty = parts[4].to_string();
            let p = Pokemon::new(name, ty, attack, defense, hp)?;
            pokemons.push(p);
        }
        Ok(pokemons)
    }

    let team1 = get_pokemons(n1, &mut lines)?;
    let team2 = get_pokemons(n2, &mut lines)?;

    for (i, (&n, t)) in [n1, n2].iter().zip([&team1, &team2]).enumerate() {
        if n != t.len() {
            Err(format!("Trainer {i} has {} pokemon. Expected {n}", t.len()))?
        }
    }

    let t1 = Trainer::new(team1);
    let t2 = Trainer::new(team2);

    Ok([t1, t2])
}

fn attack_and_handle<'a, I>(
    attacker: &mut &'a mut Pokemon, // Reference to reference in order to switch them
    defender: &mut &'a mut Pokemon,
    defender_iter: &mut I,
) -> bool
where
    I: Iterator<Item = &'a mut Pokemon>,
{
    attacker.attack(defender);

    if !defender.alive() {
        println!("{} won {}", attacker.name(), defender.name());

        if let Some(next) = defender_iter.next() {
            *defender = next;
        } else {
            return true;
        }
    }

    false
}

pub fn battle(trainers: &mut [Trainer; 2]) -> PokemonResult<()> {
    let [t1, t2] = trainers;
    let mut team1 = t1.pokemons_mut().iter_mut();
    let mut team2 = t2.pokemons_mut().iter_mut();

    let mut p1 = team1.next().ok_or("Trainer 1 doesn't have any pokemon")?;

    let mut p2 = team2.next().ok_or("Trainer 2 doesn't have any pokemon")?;

    loop {
        if attack_and_handle(&mut p1, &mut p2, &mut team2) {
            break;
        }

        if attack_and_handle(&mut p2, &mut p1, &mut team1) {
            break;
        }
    }
    print_overview(trainers);
    Ok(())
}

pub fn print_instruct() -> PokemonResult<()> {
    const INSTRUCT: &str = "instructions.txt";

    let contents =
        std::fs::read_to_string(INSTRUCT).map_err(|_| format!("Unable to open {INSTRUCT:?}"))?;

    println!("{contents}");
    Ok(())
}

pub fn print_trainers(trainers: &[Trainer; 2]) {
    const COLOURS: [&str; 2] = ["\x1b[32m", "\x1b[31m"]; // GREEN, RED

    const DIV: &str = "-----------------";
    for (i, trainer) in trainers.iter().enumerate() {
        print!("{}", COLOURS[i]);
        println!("Trainer {}", i + 1);
        for pokemon in trainer.pokemons() {
            println!("{DIV}");
            println!("{pokemon:?}");
            println!("{DIV}");
        }
    }
}
