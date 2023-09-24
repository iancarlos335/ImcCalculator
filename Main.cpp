#include <iostream>
#include <vector>
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
bool loopSkip = true;

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
        throw(1);

    switch (menuController)
    {
    case 1: // Dou sequência no loop e forço a introdução ser reapresentada.
        loopSkip = true;
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
        loopSkip = false;
        break;
    }
    case 3: // Filtro pelo nome
    {
        cout << "Insira o nome a ser filtrado:" << endl;
        cin >> filter;

        if (cin.fail())
            throw(1);

        vector<Pessoa> pessoasFiltradas;

        for (const Pessoa &obj : pessoas)
        {
            if (obj.nome.find(filter) != string::npos)
            {
                pessoasFiltradas.push_back(obj);
            }
        }

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
        loopSkip = false;

        break;
    }
    case 4: // Encerro o programa, matando o loop.
        loopController = false;
        loopSkip = false;
        break;
    default: // Se no menu eu receber um número diferente dos esperados essa mensagem é exibida. O cadastro de Pessoa é pulado também.
        cout << "O número digitado nao compreende aos esperados\n";
        loopSkip = false;
        break;
    };
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    locale::global(locale());
    cout.imbue(locale());

    try
    {
        while (loopController)
        {
            if (loopSkip)
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
            cout << "\n\nO que foi digitado não era o esperado. Apenas números são permitidos.\n\n";
    }

    return 0;
};