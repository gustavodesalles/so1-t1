#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <Processo.h>
#include <Escalonador.h>

class File
{

public:
	File(std::string filename) {
		myfile.open(filename);
		if (!myfile.is_open()) {
			std::cout << "Erro ao abrir o arquivo!\n";
		}
	}
	
	void read_file() {
	
		int a, b, c;
		
		if (!myfile.is_open()) {
			std::cout << "Arquivo não está aberto!" << std::endl;
		}
		
        long id = 1;
		while (myfile >> a >> b >> c) {
			Processo p(id, a, b, c);
			processes.push_back(p);
            id++;
		}

		// std::cout << "Quantidade de processos lidos do arquivo: " << processes.size() << std::endl;
	}

	~File() {
	}

private:
	std::ifstream myfile; 
	std::vector<Processo> processes;
};

bool compareDatasInicio(Processo p1, Processo p2)
{
    return (p1.dataInicio < p2.dataInicio);
}

bool compareDatasConclusaoDecrescente(Processo p1, Processo p2)
{
    return (p1.dataConclusao > p2.dataConclusao);
}

bool compareDuracoes(Processo p1, Processo p2)
{
    return (p1.duracao < p2.duracao);
}

bool comparePrioridadesEstaticas(Processo p1, Processo p2)
{
    return (p1.prioridadeEstatica > p2.prioridadeEstatica);
}

int obterDataConclusaoUltima(std::vector<Processo> &processos)
{
    std::stable_sort(processos.begin(), processos.end(), compareDatasConclusaoDecrescente);
    return processos[0].dataConclusao;
}

void sortFCFS(std::vector<Processo> &processos)
{
    std::stable_sort(processos.begin(), processos.end(), compareDatasInicio);
}

void sortSJF(std::vector<Processo> &processos)
{
    sortFCFS(processos);
    std::stable_sort(processos.begin(), processos.end(), compareDuracoes);
}

void sortPrioridadesNaoPreemptivo(std::vector<Processo> &processos)
{
    sortFCFS(processos);
    std::stable_sort(processos.begin(), processos.end(), comparePrioridadesEstaticas);
}

void FCFS(std::vector<Processo> &processos)
{
    sortFCFS(processos);
    calculoNaoPreemptivo(processos);
}

void SJF(std::vector<Processo> &processos)
{
    sortSJF(processos);
    calculoNaoPreemptivo(processos);
}

void prioridadesNaoPreemptivo(std::vector<Processo> &processos)
{
    sortPrioridadesNaoPreemptivo(processos);
    calculoNaoPreemptivo(processos);
}

void prioridadesPreemptivo(std::vector<Processo> &processos)
{
    sortPrioridadesNaoPreemptivo(processos);
    Processo atual = processos[0];
    
    int tempo = atual.dataInicio;
    std::cout << "Time ";
    for (int i = 0; i < processos.size(); ++i)
    {
        std::cout << " P" << i + 1;
    }
    std::cout << '\n';
    for (int i = 0; i < tempo; i++)
    {
        std::cout << i << "-" << i + 1;
        for (int j = 0; j < processos.size(); j++)
        {
            std::cout << "   ";
        }
        std::cout << '\n';
    }
    
    while (!todosProcessosConcluidos(processos))
    {
        std::vector<Processo> processosMaiorPrioridade = encontrarProcessosMaiorPrioridade(processos, atual.prioridadeEstatica, tempo);
        if (processosMaiorPrioridade.size() > 0)
        {
            //trocar de contexto com o primeiro item do vetor processosMAiorPrioridade
            //alterar o estado também
            atual = processosMaiorPrioridade[0];
        }
        atual.tempoJaExecutado++;
        imprimirEstadoAtual(processos, tempo);
        if (atual.tempoJaExecutado == atual.duracao)
        {
            // trocar o estado do atual para concluído
            // buscar o próximo processo da fila
        }
        tempo++;   
    }
}

void roundRobin(std::vector<Processo> &processos, int quantum) {
    sortFCFS(processos);
    Processo atual = processos[0];
    int tempo = atual.dataInicio;
    std::cout << "Time ";
    for (int i = 0; i < processos.size(); ++i)
    {
        std::cout << " P" << i + 1;
    }
    std::cout << '\n';
    for (int i = 0; i < tempo; i++)
    {
        std::cout << i << "-" << i + 1;
        for (int j = 0; j < processos.size(); j++)
        {
            std::cout << "   ";
        }
        std::cout << '\n';
    }

    while (!todosProcessosConcluidos)
    {
        for (int i = 0; i < quantum; i++)
        {
            atual.tempoJaExecutado++;
            imprimirEstadoAtual(processos, tempo);
            tempo++;
            if (atual.tempoJaExecutado == atual.duracao)
            {
                // trocar o estado do atual para concluído
                break;
            }
            
        }
        if (atual.tempoJaExecutado == atual.duracao) //verifica de novo no fim do quantum
            {
                // trocar o estado do atual para concluído
            } else {
                // trocar o estado do atual para pronto
            }
        // buscar o próximo processo da fila
    }
    
}

bool todosProcessosConcluidos(std::vector<Processo> &processos)
{
    for (int i = 0; i < processos.size(); i++)
    {
        if (processos[i].estado != TERMINADO)
        {
            return false;
        } 
    }
    return true;
}

std::vector<Processo> encontrarProcessosMaiorPrioridade(std::vector<Processo> &processos, int prioridade, int tempo)
{
    std::vector<Processo> processosMaiorPrioridade;
    for (int i = 0; i < processos.size(); i++)
    {
        if (processos[i].prioridadeEstatica > prioridade && processos[i].dataInicio == tempo)
        {
            processosMaiorPrioridade.push_back(processos[i]);
        } 
    }
    sortPrioridadesNaoPreemptivo(processosMaiorPrioridade); // garantir que o processo de maior prioridade vem primeiro
    return processosMaiorPrioridade;
}

int calculoNaoPreemptivo(std::vector<Processo> &processos)
{
    int tempo = 0;
    for (int i = 0; i < processos.size(); ++i)
    {
        if (tempo < processos[i].dataInicio)
        {
            tempo = tempo + (processos[i].dataInicio - tempo);
        }
        tempo += processos[i].duracao;
        processos[i].dataConclusao = tempo;
        processos[i].tempoExecutadoTotal = processos[i].dataConclusao - processos[i].dataInicio;
        processos[i].tempoEspera = processos[i].tempoExecutadoTotal - processos[i].duracao;
    }
    return tempo;
}

// void calculoPP(std::vector<Processo> &processos)
// {
//     std::vector<Processo> processosConcluidos;
//     int tempo = 0;

// }

void imprimirNaoPreemptivo(std::vector<Processo> &processos, int tempo)
{
    std::cout << "Time ";
    for (int i = 0; i < processos.size(); ++i)
    {
        std::cout << " P" << i + 1;
    }
    std::cout << '\n';
    for (int i = 0; i < tempo; i++)
    {
        std::cout << i << "-" << i + 1;
        for (int j = 0; j < processos.size(); j++)
        {
            imprimirTempoProcesso(processos[j], i);
        }
        std::cout << '\n';
    }
}

void imprimirEstadoAtual(std::vector<Processo> &processos, int tempo)
{
    for (int i = 0; i < processos.size(); i++)
    {
        if (processos[i].estado == EXECUTANDO) {
            std::cout << " ##";
        } else if (processos[i].estado == PRONTO) {
            std::cout << " --";
        } else {
            std::cout << "  ";
        }
    }
    
}

void imprimirTempoProcesso(Processo p, int i)
{
    if (i >= p.dataInicio && i < p.dataInicio + p.tempoEspera) //processo foi criado, mas não começou a execução
    {
        std::cout << " --";
    } else if (i >= p.dataInicio + p.tempoEspera && i < p.dataConclusao) //processo está em execução
    {
        std::cout << " ##";
    } else {
        std::cout << "   ";
    }
    
    
}

int main() 
{
    File f("entrada.txt");
    Escalonador e;

}