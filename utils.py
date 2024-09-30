from Pokemon import Pokemon, Treinador


def lerTreinadores(nomeArq: str) -> tuple[Treinador, Treinador]:
    with open(nomeArq, "r") as f:
        qtd1, qtd2 = map(int, f.readline().strip().split())

        treinador1 = Treinador(qtd1)
        for _ in range(qtd1):
            lineParts = f.readline().split()
            nome = lineParts[0]
            ataque = float(lineParts[1])
            defesa = float(lineParts[2])
            vida = float(lineParts[3])
            tipo = lineParts[4]
            treinador1.pokemons.append(Pokemon(nome, ataque, defesa, vida, tipo))

        treinador2 = Treinador(qtd2)
        for _ in range(qtd2):
            lineParts = f.readline().split()
            nome = lineParts[0]
            ataque = float(lineParts[1])
            defesa = float(lineParts[2])
            vida = float(lineParts[3])
            tipo = lineParts[4]
            treinador2.pokemons.append(Pokemon(nome, ataque, defesa, vida, tipo))

        return treinador1, treinador2


def printTreinadores(Treinadores: tuple[Treinador, Treinador]) -> None:

    for i, treinador in enumerate(Treinadores, start=1):
        print(f"Treinador {i}")
        for pokemon in treinador.pokemons:
            print("-----------------")
            print(f"Nome: {pokemon.nome}")
            print(f"Ataque: {pokemon.ataque}")
            print(f"Defesa: {pokemon.defesa}")
            print(f"Vida: {pokemon.vida}")
            print(f"Tipo: {pokemon.tipo}")
            print(f"Super Efetivo contra: {pokemon.super_efetivo}")
            print("-----------------")
