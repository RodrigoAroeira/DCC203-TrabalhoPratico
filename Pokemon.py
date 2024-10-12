from __future__ import annotations

from dataclasses import dataclass, field


@dataclass(slots=True)
class Pokemon:

    nome: str
    ataque: float
    defesa: float
    vida: float
    tipo: str
    super_efetivo: str = field(init=False)

    def __post_init__(self) -> None:
        self.super_efetivo = self._get_super_efetividade()

    def _get_super_efetividade(self) -> str:
        tipos = ("eletrico", "agua", "fogo", "gelo", "pedra")
        contraTipos = ("agua", "fogo", "gelo", "pedra", "eletrico")

        for idx, tipo in enumerate(tipos):
            if self.tipo == tipo:
                return contraTipos[idx]

        print(f"Tipo {self.tipo} não encontrado, saindo do programa")
        exit(1)

    def _get_ataque_multiplier(self, defesa: Pokemon) -> float:
        multiplier = 1.0
        if self.super_efetivo == defesa.tipo:
            multiplier = 1.2
        elif defesa.super_efetivo == self.tipo:
            multiplier = 0.8

        return multiplier

    def atacar(self, defesa: Pokemon) -> None:
        multiplier = self._get_ataque_multiplier(defesa)
        dano = self.ataque * multiplier - defesa.defesa

        if dano <= 0:
            dano = 1
        defesa.vida -= dano
