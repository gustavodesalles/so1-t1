#include <string>
#include <queue>
#include <Processo.h>

class Escalonador
{
private:
    std::queue<Processo> processosProntos;
    static int countTrocasContexto;
public:
    Escalonador();
    ~Escalonador();
};

Escalonador::Escalonador()
{
    this->countTrocasContexto = 0;
}

Escalonador::~Escalonador()
{
}
