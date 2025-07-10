use clap::Parser;

#[derive(Debug, Parser)]
#[command(name = "cli_app")]
pub struct Args {
    /// Reads from a file with a name of your choice
    #[arg(short, long, value_name = "FILE", default_value = "trainers.txt")]
    pub file: String,

    /// Runs the example battle. Works like --file example.txt
    #[arg(short, long)]
    pub example: bool,

    /// Prints the trainers and exits the program
    #[arg(short, long)]
    pub print: bool,

    /// Prints the program usage instructions and exits the program
    #[arg(short, long)]
    pub instruct: bool,
}
