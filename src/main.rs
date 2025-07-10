use clap::Parser;
use utils::PokemonResult;

mod cli;
mod pokemon;
mod trainer;
mod utils;

fn main() -> PokemonResult<()> {
    let args = cli::Args::parse();
    if args.instruct {
        return utils::print_instruct();
    }

    let file = if args.example {
        String::from("example.txt")
    } else {
        args.file
    };

    let mut trainers = utils::read_trainers(&file)?;

    if args.print {
        utils::print_trainers(&trainers);
        return Ok(());
    }

    utils::battle(&mut trainers)?;

    Ok(())
}
