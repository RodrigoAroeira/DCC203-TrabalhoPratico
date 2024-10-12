from utils import lerTreinadores
from batalha import Batalha


def main():
    arquivo = "treinadores.txt"

    treinadores = lerTreinadores(arquivo)

    Batalha(treinadores)


if __name__ == "__main__":
    main()
