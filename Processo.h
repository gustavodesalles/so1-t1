#include <string>
#include <Estado.h>

class Processo
{
private:
    /* data */
    long idProcesso;
public:
    Processo(long idProcesso, int dataInicio, int duracao, int prioridadeEstatica);
    ~Processo();
    int dataInicio;
    int dataConclusao;
    int duracao;
    int prioridadeEstatica;
    int prioridadeDinamica;
    int tempoEspera;
    int tempoExecutadoTotal;
    int tempoExecutadoQuantumAtual;
    Estado estado;
};

Processo::Processo(long idProcesso, int dataInicio, int duracao, int prioridadeEstatica)
{
    this->idProcesso = idProcesso;
    this->dataInicio = dataInicio;
    this->duracao = duracao;
    this->prioridadeEstatica = prioridadeEstatica;
}

Processo::~Processo()
{
}
