#include <string>
#include <vector>
#include <Processo.h>

class Escalonador
{
private:
    std::vector<Processo> processosProntos;
    static int countTrocasContexto;
public:
    Escalonador();
    ~Escalonador();
    std::vector<Processo> getProcessosProntos() {
        return processosProntos;
    }
    void setProcessosProntos(std::vector<Processo> processosProntos) {
        this->processosProntos = processosProntos;
    }
};

Escalonador::Escalonador()
{
    this->countTrocasContexto = 0;
}

Escalonador::~Escalonador()
{
}
