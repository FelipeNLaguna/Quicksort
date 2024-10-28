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
        /* se for randomizado
        *  int r = random(i,f);
        * swap(c[i],c[r]); */

        
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
        /* se for randomizado
        *  int r = random(i,f);
        * swap(c[i],c[r]); */

        
        int m = mediana3(c,i,f);
        swap(c[i],c[m]);
        (*trocas)++;  

        p = particionamento_hoare(c,i,f, trocas);
        quick_sort_hoare(c,i,p-1 , trocas, chamadas);
        quick_sort_hoare(c,p+1,f , trocas , chamadas);
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
    int tam_arr;
    output_file.is_open();
    while(fscanf(arq ,"%d", &tam_arr) != EOF){
        int arr[tam_arr];
        for(int i = 0 ; i<tam_arr;i++){
            fscanf(arq,"%d",&arr[i]);
        }
        int trocas = 0;
        int chamadas = 0;
        auto start = high_resolution_clock::now();
        quick_sort_lomuto(arr,0,tam_arr-1, &trocas , &chamadas);
        auto end = high_resolution_clock::now();
        auto tempo = duration_cast<microseconds>(end - start);
        chamadas = chamadas-1;
        // tem que escrever apos chamar todas as funcoes
        output_file << tam_arr << " , "<< "mediana3 , " << " lomuto , " 
        << trocas <<" , "<< chamadas <<" , "<< tempo.count() << endl;
        /*
        print_array(arr,20);
        cout << trocas << endl;
        cout << chamadas << endl; 
        */
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