use crate::pokemon::Pokemon;

pub struct Trainer {
    pokemons: Vec<Pokemon>,
}

impl Trainer {
    pub fn new(pokemons: Vec<Pokemon>) -> Self {
        Self { pokemons }
    }

    pub fn pokemons(&self) -> &[Pokemon] {
        &self.pokemons
    }

    pub fn pokemons_mut(&mut self) -> &mut [Pokemon] {
        &mut self.pokemons
    }

    pub fn pokemon_alive(&self) -> usize {
        self.pokemons.iter().filter(|p| p.hp() > 0.0).count()
    }

    pub fn winner(&self) -> bool {
        self.pokemon_alive() != 0
    }
}
