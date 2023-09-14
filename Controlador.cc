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

void calculoNaoPreemptivo(std::vector<Processo> &processos)
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
}

// void calculoPP(std::vector<Processo> &processos)
// {
//     std::vector<Processo> processosConcluidos;
//     int tempo = 0;

// }

void imprimirNaoPreemptivo(std::vector<Processo> &processos)
{
    std::cout << "Time ";
    for (int i = 0; i < processos.size(); ++i)
    {
        std::cout << " P" << i + 1;
    }
    std::cout << '\n';
    int dataFinal = obterDataConclusaoUltima(processos);
    for (int i = 0; i < dataFinal; i++)
    {
        std::cout << i << "-" << i + 1;
        for (int j = 0; j < processos.size(); j++)
        {
            imprimirTempoProcesso(processos[j], i);
        }
        std::cout << '\n';
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