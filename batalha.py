from Pokemon import Treinador

type dupla = tuple[Treinador, Treinador]


def set_vencedor(treinadores: dupla) -> None:
    for treinador in treinadores:
        treinador.vencedor = False if treinador.pokemons_vivos == 0 else True

    return


def print_overview(treinadores: dupla) -> None:

    for i, treinador in enumerate(treinadores, start=1):
        if not treinador.vencedor:
            continue

        print(f"Jogador {i} venceu")
        print("Pokemons sobreviventes:")
        for pokemon in treinador.pokemons:
            if pokemon.vida > 0:
                print(pokemon.nome)

    print("Pokemons derrotados:")
    for treinador in treinadores:
        for pokemon in treinador.pokemons:
            if pokemon.vida <= 0:
                print(pokemon.nome)


def Batalha(treinadores: dupla) -> None:
    treinador1, treinador2 = treinadores

    i, j = 0, 0
    pokemon1 = treinador1.pokemons[i]
    pokemon2 = treinador2.pokemons[j]

    # while treinador1.pokemons_vivos and treinador2.pokemons_vivos:
    while i < treinador1.pokemons_total and j < treinador2.pokemons_total:

        pokemon1.atacar(pokemon2)
        if pokemon2.vida <= 0:
            print(f"{pokemon1.nome} venceu {pokemon2.nome}")
            treinador2.pokemons_vivos -= 1
            j += 1

            if not treinador2.pokemons_vivos:
                break

            pokemon2 = treinador2.pokemons[j]

        pokemon2.atacar(pokemon1)
        if pokemon1.vida <= 0:
            print(f"{pokemon2.nome} venceu {pokemon1.nome}")
            treinador1.pokemons_vivos -= 1
            i += 1

            if not treinador1.pokemons_vivos:
                break

            pokemon1 = treinador1.pokemons[i]

    set_vencedor(treinadores)
    print_overview(treinadores)
