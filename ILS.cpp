#include <iostream>
#include <vector>
#include <string>

int matrizAdj[6][6] = 
        {
            {0, 2, 1, 4, 9, 1},
            {2, 0, 5, 9, 7, 2},
            {1, 5, 0, 3, 8, 6},
            {4, 9, 3, 0, 2, 5},
            {9, 7, 8, 2, 0, 2},
            {1, 2, 6, 5, 2, 0}
        };

class Solution{

    public:
        std::vector<int> sequencia;
        int valorObj;

    public:
        Solution(std::vector<int> sequencia):
        sequencia(sequencia)
        {
        }

        void exibirSolucao(){
            for (int i = 0; i < this->sequencia.size() - 1; i++)
                std::cout << this->sequencia[i] + 1 << " -> ";
                std::cout << this->sequencia.back() + 1 << std::endl;
            }

        int calcularValorObj(){

            this->valorObj = 0;
            
            for(int i = 0; i < this->sequencia.size() - 1; i++){
                this->valorObj += matrizAdj[this->sequencia[i]][this->sequencia[i+1]];
            }

            return this->valorObj;

        }

        void movimento(int a, int b){

            int aux, i_a = -1, i_b = - 1;
            for (int i = 0; i < this->sequencia.size(); i++){
                if (a == this->sequencia[i])
                    i_a = i;
                if (b == this->sequencia[i])
                    i_b = i;
            }

            if (i_a == -1 || i_b == -1){
                std::cout << "MOVIMENTO INVALIDO!" << std::endl;
                return;
            }

            this->sequencia[i_a] = b;
            this->sequencia[i_b] = a;

        }

        int calculaCustoSwap(int a, int b){
            
            Solution aux = {{this->sequencia}};
            int custoAntesSwap = aux.calcularValorObj();
            aux.movimento(a, b);
            int custoDepoisSwap = aux.calcularValorObj();
            return (custoDepoisSwap - custoAntesSwap);
            
        }

        void bestImprovementSwap(){
            int bestDelta = 0;
            int best_i, best_j;
            for (int i = 0; i < this->sequencia.size() - 1; i++){
                for (int j = 1; j < this->sequencia.size(); j++){
                    int delta = calculaCustoSwap(i, j);
                    if (delta < bestDelta)
                    {
                        bestDelta = delta;
                        best_i = i;
                        best_j = j;
                    }
                }
            }

            if (bestDelta < 0){
                this->movimento(best_i, best_j);
            }
        }

};

Solution Construcao(){ //Insersao mais barata
    
    Solution s({0, 2, 1});
    std::vector<int> caminhos_disponiveis = {3, 4, 5};

    int i, j, i_menor;
    int custo_atual, menor_custo;
    int maximo = caminhos_disponiveis.size();
    
    std::vector<std::vector<int>> arestas;
    std::vector<int> custo_aresta;
    std::vector<int> aux;
    
    for (int k = 0; k < maximo; k++){

        arestas.clear();
        custo_aresta.clear();
        
        for (i = 0; i < caminhos_disponiveis.size(); i++){
            for (j = 0; j < s.sequencia.size() - 1; j++){
                
                aux.clear();
                    
                custo_atual += matrizAdj[s.sequencia[j]][caminhos_disponiveis[i]];
                custo_atual += matrizAdj[s.sequencia[j + 1]][caminhos_disponiveis[i]];
                custo_atual -= matrizAdj[s.sequencia[j]][s.sequencia[j + 1]];

                aux.push_back(j);
                aux.push_back(caminhos_disponiveis[i]);
                aux.push_back(j + 1);

                arestas.push_back(aux);
                custo_aresta.push_back(custo_atual);

                custo_atual = 0;
            }

            int cont = 0;

            for (int custo : custo_aresta){
                if (cont == 0){
                    menor_custo = custo;
                    i_menor = cont;
                }

                if (menor_custo > custo){
                menor_custo = custo;
                i_menor = cont;
                }

                cont++;

            }
            
        }
    
        s.sequencia.insert(s.sequencia.begin() + arestas[i_menor][0], arestas[i_menor][1]);

        int indice_para_excluir;

        for (i = 0; i < caminhos_disponiveis.size(); i++){
            if (arestas[i_menor][1] == caminhos_disponiveis[i]){
                indice_para_excluir = i;
                break;
            }
        }

        caminhos_disponiveis.erase(caminhos_disponiveis.begin() + indice_para_excluir);

    }

    return s;

} 

using namespace std;

int main()

{
    int iterIls = 0;
    int maxIterIls = 10;

    Solution solucao = {{}};
    solucao = Construcao();
    Solution best = solucao;
    best.exibirSolucao();
    cout << "Custo: " << best.calcularValorObj() << endl;

    while (iterIls <= maxIterIls)
    {
        solucao.bestImprovementSwap(); //Busca local
        if (solucao.calcularValorObj() < best.calcularValorObj()){
            best = solucao;
            iterIls = 0;
        }
        iterIls++;
    }

    cout << endl;
    best.exibirSolucao();
    cout << "Custo: " << best.calcularValorObj() << endl;
    
    return 0;
    
}