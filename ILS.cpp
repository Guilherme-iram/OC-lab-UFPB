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
        double valorObj;

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

        void calcularValorObj(){

            this->valorObj = 0;
            
            for(int i = 0; i < this->sequencia.size() - 2; i++){

                this->valorObj += matrizAdj[this->sequencia[i]][this->sequencia[i+1]];
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

    Solution solucao = {{}};
    solucao = Construcao();
    solucao.exibirSolucao();
    solucao.calcularValorObj();
    cout << solucao.valorObj << endl;

    return 0;
}
