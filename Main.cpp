#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <locale>
#include <clocale>
using namespace std;

string privateNome;
int privateIdade;
double privatePeso;
double privateAltura;
double privateImc;

bool loopController = true;
int menuController = 0;
bool skipLoop = false;

class Pessoa
{
public:
    string nome;
    int idade;
    double peso;
    double altura;
    double imc;

    Pessoa(){};
    Pessoa(string nome, int idade, double peso, double altura, double imc)
    {
        this->nome = nome;
        this->idade = idade;
        this->peso = peso;
        this->altura = altura;
        this->imc = imc;
    };
};

string filter;
vector<Pessoa> pessoas;

void showMenu()
{
    cout << "\nVoce gostaria de cadastrar mais uma pessoa, listar as já cadastradas, ou encerrar o programa?\n\n1 - Cadastrar mais uma pessoa\n2 - Listar cadastradas \n3 - Filtrar pessoas pelo nome\n4 - Encerrar o programa\n\n";
    cin >> menuController;

    if (cin.fail())
        throw(2);

    switch (menuController)
    {
    case 1: // Dou sequência no loop e forço a introdução ser reapresentada.
        peopleRegistration();
        skipLoop = false;
        break;
    case 2: //  Pego todas as pessoas e exibo cada atributo. O cadastro de Pessoa é pulado também.
    {
        for (const Pessoa &obj : pessoas)
        {
            cout
                << "\n-------------------\n"
                << "Nome: " << obj.nome << endl;
            cout << "Idade: " << obj.idade << endl;
            cout << "Peso: " << obj.peso << "kg" << endl;
            cout << "Altura: " << obj.altura << "m" << endl;
            cout << "IMC: " << obj.imc << endl;
        }
        skipLoop = true;
        break;
    }
    case 3: // Filtro pelo nome
    {
        cout << "Insira o nome a ser filtrado:" << endl;
        getline(cin >> ws, filter);

        if (cin.fail())
            throw(2);

        vector<Pessoa> pessoasFiltradas;

        for (const Pessoa &obj : pessoas)
        {
            string nomeUpperCased = obj.nome;
            // Filtra sem ser case sensitive
            transform(nomeUpperCased.begin(), nomeUpperCased.end(), nomeUpperCased.begin(), ::toupper);
            transform(filter.begin(), filter.end(), filter.begin(), ::toupper);

            if (nomeUpperCased.find(filter) != string::npos)
            {
                pessoasFiltradas.push_back(obj);
            }
        }

        // Exibo o Filtro
        for (const Pessoa &obj : pessoasFiltradas)
        {
            cout
                << "\n-------------------\n"
                << "Nome: " << obj.nome << endl;
            cout << "Idade: " << obj.idade << endl;
            cout << "Peso: " << obj.peso << "kg" << endl;
            cout << "Altura: " << obj.altura << "m" << endl;
            cout << "IMC: " << obj.imc << endl;
        }
        skipLoop = true;

        break;
    }
    case 4: // Encerro o programa, matando o loop.
        loopController = false;
        skipLoop = false;
        break;
    default: // Se no menu eu receber um número diferente dos esperados essa mensagem é exibida. O cadastro de Pessoa é pulado também.
        cout << "O número digitado nao compreende aos esperados\n";
        skipLoop = true;
        break;
    };
}

void peopleRegistration()
{
    // Inserção de dados
    cout << "Insira seu nome abaixo:" << endl;
    getline(cin >> ws, privateNome);
    cout << "Insira a sua idade:" << endl;
    cin >> privateIdade;
    cout << "Insira o seu peso:" << endl;
    cin >> privatePeso;
    cout << "Insira a sua altura:" << endl;
    cin >> privateAltura;

    if (cin.fail())
        throw(1);

    // Calculo de IMC
    privateImc = privatePeso / (privateAltura * privateAltura);
    cout << "\nSeu imc é: " << privateImc << endl;

    // Cadastro da Pessoa
    Pessoa pessoa(privateNome, privateIdade, privatePeso, privateAltura, privateImc);
    pessoas.push_back(pessoa);
}

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    try
    {
        while (loopController)
        {
            if (!skipLoop)
            {
                peopleRegistration();
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
        switch (meuErro)
        {
        case 1: // Exception no Cadastro
            cout << "\n\nO que foi digitado não era o esperado. Apenas números são permitidos.\n\n";
            break;
        case 2: // Exception no Menu
            cout << "\n\nO que foi digitado não era o esperado. Apenas números são permitidos.\n\n";
            break;
        }

        cin.clear();
    }

    return 0;
};