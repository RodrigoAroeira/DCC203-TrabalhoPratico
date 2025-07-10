use crate::utils::{PokemonResult, get_super_effective};

#[derive(Debug)]
pub struct Pokemon {
    name: String,
    typ: String,
    super_effective: String,
    attack: f32,
    defense: f32,
    hp: f32,
}

/// Public methods
impl Pokemon {
    pub fn new(
        name: String,
        typ: String,
        attack: f32,
        defense: f32,
        hp: f32,
    ) -> PokemonResult<Self> {
        let super_effective = get_super_effective(&typ)?;
        Ok(Self {
            name,
            typ,
            super_effective,
            attack,
            defense,
            hp,
        })
    }

    pub fn attack(&self, defense: &mut Pokemon) {
        let multiplier = self.get_attack_multiplier(defense);
        let dmg = {
            let tmp = self.attack * multiplier - defense.defense;
            if tmp <= 0.0 { 1.0 } else { tmp }
        };

        defense.hp -= dmg;
    }

    pub fn hp(&self) -> f32 {
        self.hp
    }

    pub fn alive(&self) -> bool {
        self.hp > 0.0
    }

    pub fn name(&self) -> &str {
        &self.name
    }
}

/// Private methods
impl Pokemon {
    fn get_attack_multiplier(&self, defense: &Pokemon) -> f32 {
        if self.super_effective == defense.typ {
            1.2
        } else if defense.super_effective == self.typ {
            0.8
        } else {
            1.0
        }
    }
}
