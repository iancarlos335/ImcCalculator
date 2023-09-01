#include <iostream>
#include <vector>

std::string privateNome;
int privateIdade;
double privatePeso;
double privateAltura;
double privateImc;

int i = 0;
int loopController = 1;
int loopQuit = 0;
int loopSkip = 1;

class Pessoa
{
public:
    std::string nome;
    int idade;
    double peso;
    double altura;
    double imc;

    Pessoa(){};
    Pessoa(std::string nome, int idade, double peso, double altura, double imc)
    {
        this->nome = nome;
        this->idade = idade;
        this->peso = peso;
        this->altura = altura;
        this->imc = imc;
    };
};

std::string filter;
std::vector<Pessoa> pessoas;

void showMenu()
{
    std::cout << "\nVoce gostaria de cadastrar mais uma pessoa, listar as ja cadastradas, ou encerrar o programa?\n\n1 - Cadastrar mais uma pessoa\n2 - Listar cadastradas \n3 - Filtrar pessoas pelo nome\n4 - Encerrar o programa\n\n";
    std::cin >> loopQuit;

    if (std::cin.fail())
        throw(1);

    switch (loopQuit)
    {
    case 1: // Dou sequência no loop e forço a introdução ser reapresentada.
        loopController++;
        loopSkip = 1;
        break;
    case 2: //  Pego todas as pessoas e exibo cada atributo. O cadastro de Pessoa é pulado também.
    {
        for (const Pessoa &obj : pessoas)
        {
            std::cout
                << "\n-------------------\n"
                << "Nome: " << obj.nome << std::endl;
            std::cout << "Idade: " << obj.idade << std::endl;
            std::cout << "Peso: " << obj.peso << "kg" << std::endl;
            std::cout << "Altura: " << obj.altura << "m" << std::endl;
            std::cout << "IMC: " << obj.imc << std::endl;
        }
        loopController++;
        loopSkip = 0;
        break;
    }
    case 3: // Filtro pelo nome
    {
        std::cout << "Insira o nome a ser filtrado:\n";
        std::cin >> filter;

        std::vector<Pessoa> pessoasFiltradas;

        for (const Pessoa &obj : pessoas)
        {
            if (obj.nome.find(filter) != std::string::npos)
            {
                pessoasFiltradas.push_back(obj);
            }
        }

        for (const Pessoa &obj : pessoasFiltradas)
        {
            std::cout
                << "\n-------------------\n"
                << "Nome: " << obj.nome << std::endl;
            std::cout << "Idade: " << obj.idade << std::endl;
            std::cout << "Peso: " << obj.peso << "kg" << std::endl;
            std::cout << "Altura: " << obj.altura << "m" << std::endl;
            std::cout << "IMC: " << obj.imc << std::endl;
        }
        loopController++;
        loopSkip = 0;

        break;
    }
    case 4: // Encerro o programa, matando o loop.
        loopController = 0;
        loopSkip = 0;
        break;
    default: // Se no menu eu receber um número diferente dos esperados essa mensagem é exibida. O cadastro de Pessoa é pulado também.
        std::cout << "O numero digitado nao compreende aos esperados\n";
        loopController++;
        loopSkip = 0;
        break;
    };
}

int main()
{
    try
    {
        while (i < loopController)
        {
            if (loopSkip == 1)
            {
                // Cadastro de Pessoa
                std::cout << "\nInsira seu nome abaixo:\n";
                std::cin >> privateNome;
                std::cout << "Insira a sua idade:\n";
                std::cin >> privateIdade;
                std::cout << "Insira o seu peso:\n";
                std::cin >> privatePeso;
                std::cout << "Insira a sua altura:\n";
                std::cin >> privateAltura;

                if (std::cin.fail())
                    throw(1);

                // Calculo de IMC
                privateImc = privatePeso / (privateAltura * privateAltura);
                std::cout << "\nSeu imc e: " << privateImc << std::endl;

                // População do vetor
                Pessoa pessoa(privateNome, privateIdade, privatePeso, privateAltura, privateImc);
                pessoas.push_back(pessoa);

                showMenu();
            }
            else
            {
                showMenu();
            }
        }
    }
    catch (int meuErro)
    {
        if (meuErro == 1)
            std::cout << "\n\nO que foi digitado nao e o esperado. Apenas numeros sao permitidos.\n\n";
    }

    return 0;
};
