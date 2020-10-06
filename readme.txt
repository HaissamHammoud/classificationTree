Para compilar o projeto:
windows
gcc -c main.c
gcc -c spine.c
gcc -o teste.exe main.c spine.c

linux 
gcc -c main.c  -lm
gcc -c spine.c -lm
gcc -o teste.o main.c spine.c  -lm

Este projeto visa criar uma arvore binaria de decisão para classificar as anomalias de coluna.
Foi utilizado como inspiração o algoritmo c45 e id3.


references : https://sefiks.com/2017/11/20/a-step-by-step-id3-decision-tree-example/
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