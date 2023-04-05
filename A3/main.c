#include <stdio.h>
#include <string.h>
#include <time.h>

#include "vector.h"

int main()
{   
    srand(time(NULL));
    Vector *v;
    int M = 1000;
    v = vector_construct();
    
    printf("N menor    maior       media\n");
    for(int N = 1; N < 2000; N+=200){
        double menor;
        double maior;
        double media;
        //Faça um programa que crie iterativamente vetores com N valores, para N variando de 1 até 2000 de 200 em 200
        for(int i = 0; i < N; i++){
            int x = rand();
            vector_push_back(v, x);
        }
        
        for(int i = 0; i < M; i++){
            int idx = rand() % N;
            int valor = vector_get(v, idx);
            double inicio = get_timestamp();
            vector_find(v, valor);
            double fim = get_timestamp();
            double duracao = fim - inicio;
            
            if(i == 0){
                menor = duracao;
                maior = duracao;
                media = duracao;
            }else{
                if(duracao < menor){
                    menor = duracao;
                }
                if(duracao > maior){
                    maior = duracao;
                }
                media += duracao;
            }
        }
        double mediaf = media / M;
        printf("%d %f %f %f\n", N, menor, maior, mediaf); 
    }
    vector_destroy(v);

    return 0;
}

double get_timestamp()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return now.tv_sec + (((double)now.tv_nsec) / 1e9);
}
