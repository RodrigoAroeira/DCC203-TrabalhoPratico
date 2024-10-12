from dataclasses import dataclass, field

from Pokemon import Pokemon


@dataclass(slots=True)
class Treinador:

    pokemons: list[Pokemon] = field(default_factory=list, init=False)
    pokemons_total: int
    pokemons_vivos: int = field(init=False)
    vencedor: bool = field(default=False, init=False)

    def __post_init__(self):
        self.pokemons_vivos = self.pokemons_total
