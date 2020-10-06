Para compilar o projeto:
windows
gcc -c main.c
gcc -c spine.c
gcc -o teste.exe main.c spine.c

rodar: ./teste.exe

linux 
gcc -c main.c  -lm
gcc -c spine.c -lm
gcc -o teste.o main.c spine.c  -lm

rodar: ./teste.o

Este projeto visa criar uma arvore binaria de decisão para classificar as anomalias de coluna.
Foi utilizado como inspiração o algoritmo c45 e id3.

As imagens geradas pelo weka e uma imagem feita interpretando a arvore criada
por este algoritmo se encontram na pasta decision-tree-images

Os dados em formato ARFF estão na pasta data, assim como suas conversões para
csv que são usadas nesse algoritmo


Analise:

este algoritmo le o arquivo, classifica os pesos de cada atributo e monta
uma arvore binaria de decisões a partir do gainRatio e threshold que delimita
um valor significativo o suficiente para servir de linha de corte para decisão.

Em comparação ao algoritmo do WEKA j48 faltam alguns detalhes como decidir quel o primeiro
nó da arvore, sendoque essa é uma decisão importante na tomada de decisões.

A arvore gerada ficou diferente e mais desbalanceada do que a do WEKA distribuindo os nos de maneira
não muito uniforme.



referencias : https://sefiks.com/2017/11/20/a-step-by-step-id3-decision-tree-example/
            http://www2.cs.uregina.ca/~dbd/cs831/notes/ml/dtrees/dt_prob1.html
            https://sefiks.com/2018/05/13/a-step-by-step-c4-5-decision-tree-example/
            
            ordem dos dados

    Dados recebidos pelo algoritmo:

    double pelvic_incidence;
    double pelvic_tilt;
    double lumbar_lordosis_angle;
    double sacral_slope;
    double pelvic_radius;
    double degree_spondylolisthesis;
    double pelvic_slope;
    double direct_tilt;
    double thoracic_slope;
    double cervical_tilt;
    double sacrum_angle;
    double scoliosis_slope;