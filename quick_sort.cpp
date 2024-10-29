#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<random>
#include<fstream>
#include<chrono>

using namespace std;
using namespace chrono;

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int gerar_numero_aleatorio(int min, int max) {
    static random_device rd; // Objeto para obter uma seed aleatória
    static mt19937 gen(rd()); // Gerador de números aleatórios Mersenne Twister
    uniform_int_distribution<> dis(min, max); // Distribuição uniforme entre min e max
    return dis(gen); // Gerar e retornar o número aleatório
}
int mediana3 (int c[],int i , int f){
    int mediana = 0;
    int first , last , middle , indice_metade;
    
    indice_metade = (i+f)/2;
    first = c[i];
    last = c[f];
    middle = c[indice_metade];

    if(middle > first){
        if(middle < last){
            mediana = indice_metade;
        }
        else{
            if(last > first){
                mediana = f;
            }
            else{
                mediana = i;
            }
        }
    }
    // middle menor que o first
    else{
        if(middle > last){
            mediana = indice_metade;
        }
        else{
            if(last < first){
                mediana = f;
            }
            else{
                mediana = i;
            }
        }
    }

    return mediana;
}

int particionamento_hoare(int c[],int left,int right , int* trocas ){
    int key , i , j;
    key = c[left];
    i = left;
    j = right + 1;

    while(1){
        while(c[++i] <= key){
            if(i == right){
                break;
            }
        }
        while(key < c[--j]){
            if(j==left){
                break;
            }
        }
        if(i >= j ){
            break;
        }
        swap(c[i],c[j]);
        (*trocas)++;
    }
    swap(c[left],c[j]);
    (*trocas)++;

    return j;
}

int particionamento_lomuto(int c[], int left , int right , int* trocas ){
    int key = c[left];
    int index = left +1 ;
    
    for(int i = left+1 ; i <= right ; i++){
        if(c[i] < key){
            swap(c[i] , c[index]);
            (*trocas)++;
            index++;
        }
    }
    swap(c[left], c[index-1]);
    (*trocas)++;

    return (index-1);
}

void quick_sort_lomuto(int c[], int i , int f , int * trocas , int *chamadas){
    // versão - código de aula
    int p;
    (*chamadas)++;
    if(f>i){
        
        int m = mediana3(c,i,f);
        swap(c[i],c[m]);  
        (*trocas)++;

        p = particionamento_lomuto(c,i,f , trocas );
        quick_sort_lomuto(c,i,p-1 , trocas , chamadas);
        quick_sort_lomuto(c,p+1,f , trocas , chamadas);
    }

}

void quick_sort_hoare(int c[] , int i , int f , int * trocas , int *chamadas){
    // versão - código de aula
    int p;
    (*chamadas)++;
    if(f>i){
       
        int m = mediana3(c,i,f);
        swap(c[i],c[m]);
        (*trocas)++;  

        p = particionamento_hoare(c,i,f, trocas);
        quick_sort_hoare(c,i,p-1 , trocas, chamadas);
        quick_sort_hoare(c,p+1,f , trocas , chamadas);
    }
}
void quick_sort_random_lom(int c[], int i , int f , int * trocas , int *chamadas){
    // versão - código de aula
    int p;
    (*chamadas)++;
    if(f>i){
        
        int r = gerar_numero_aleatorio(i,f);
        
        swap(c[i],c[r]);  
        (*trocas)++;

        p = particionamento_lomuto(c,i,f , trocas );
        quick_sort_random_lom(c,i,p-1 , trocas , chamadas);
        quick_sort_random_lom(c,p+1,f , trocas , chamadas);
    }
}
void quick_sort_random_hoare(int c[] , int i , int f , int * trocas , int *chamadas){
    // versão - código de aula
    int p;
    (*chamadas)++;
    if(f>i){
    
        int r = gerar_numero_aleatorio(i,f);
        swap(c[i],c[r]); 
        (*trocas)++;  

        p = particionamento_hoare(c,i,f, trocas);
        quick_sort_random_hoare(c,i,p-1 , trocas, chamadas);
        quick_sort_random_hoare(c,p+1,f , trocas , chamadas);
    }
}

int main(){
    // exemplo simples de mediana
    int arr[20] = {34, 7, 23, 32, 5, 62, 32, 45, 67, 89, 12, 34, 56, 78, 90, 21, 43, 65, 87, 9};
    //print_array(arr,20);
    FILE * arq;
    ofstream output_file("output.txt" , ios::app); // escrita sempre ao final

    if(!(arq = fopen("entrada-quicksort.txt", "r"))){
        cout << "Erro ao abrir o arq" << endl;
    }
    else{
    // colocar ifs e ecolher como eu quero quicksort
   
        if(output_file.is_open()){
            int tam_arr;
            while(fscanf(arq ,"%d", &tam_arr) != EOF){
                int*arr = new int[tam_arr];
                for(int i = 0 ; i<tam_arr;i++){
                    fscanf(arq,"%d",&arr[i]);
                }

                int* arr1 = new int[tam_arr];
                int* arr2 = new int[tam_arr];
                int* arr3 = new int[tam_arr];
                int* arr4 = new int[tam_arr];
                copy(arr, arr + tam_arr, arr1);
                copy(arr, arr + tam_arr, arr2);
                copy(arr, arr + tam_arr, arr3);
                copy(arr, arr + tam_arr, arr4);

                int trocas1 = 0;
                int trocas2 = 0;
                int trocas3 = 0;
                int trocas4 = 0;

                int chamadas1 = 0;
                int chamadas2 = 0;
                int chamadas3 = 0;
                int chamadas4 = 0; 

                auto start1 = high_resolution_clock::now();
                quick_sort_lomuto(arr1,0,tam_arr-1, &trocas1 , &chamadas1);
                auto end1 = high_resolution_clock::now();
                auto tempo1 = duration_cast<microseconds>(end1 - start1);
                chamadas1 = chamadas1-1;

                auto start2 = high_resolution_clock::now();
                quick_sort_hoare(arr2,0,tam_arr-1, &trocas2 , &chamadas2);
                auto end2 = high_resolution_clock::now();
                auto tempo2 = duration_cast<microseconds>(end2 - start2);
                chamadas2 = chamadas2-1;

                auto start3 = high_resolution_clock::now();
                quick_sort_random_lom(arr3,0,tam_arr-1, &trocas3 , &chamadas3);
                auto end3 = high_resolution_clock::now();
                auto tempo3 = duration_cast<microseconds>(end3 - start3);
                chamadas3 = chamadas3 - 1;

                auto start4 = high_resolution_clock::now();
                quick_sort_random_hoare(arr4,0,tam_arr-1, &trocas4 , &chamadas4);
                auto end4 = high_resolution_clock::now();
                auto tempo4 = duration_cast<microseconds>(end4 - start4);
                chamadas4 = chamadas4-1;

                // tem que escrever apos chamar todas as funcoes
                output_file << tam_arr << ","<< "mediana3," << "lomuto," 
                << trocas1 <<","<< chamadas1 <<","<< tempo1.count() << endl;

                output_file << tam_arr << ","<< "mediana3," << "hoare," 
                << trocas2 <<","<< chamadas2 <<","<< tempo2.count() << endl;

                output_file << tam_arr << ","<< "aleatorio," << "lomuto," 
                << trocas3 <<","<< chamadas3 <<","<< tempo3.count() << endl;

                output_file << tam_arr << ","<< "aleatorio," << "hoare," 
                << trocas4 <<","<< chamadas4 <<","<< tempo4.count() << endl;

                delete[] arr;
                delete[] arr1;
                delete[] arr2;
                delete[] arr3;
                delete[] arr4;
            }
        }
    }
    output_file.close();
    fclose(arq);
    return 0;
}
/*  OQ FALTA FAZER
*   Lidar com o arq -> Ler e escrever
*   Randomizar
*   Debugar
*/