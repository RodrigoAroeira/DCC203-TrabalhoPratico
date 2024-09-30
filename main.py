from utils import lerTreinadores
from batalha import Batalha


def main():
    arquivo = "treinadores.txt"

    treinadores = lerTreinadores(arquivo)
    # for treinador in treinadores:
    #     print(len(treinador.pokemons))
    # exit(0)
    Batalha(treinadores)


if __name__ == "__main__":
    main()
