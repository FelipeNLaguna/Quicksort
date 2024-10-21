#include<iostream>

using namespace std;

int mediana3 (int c[],int i , int f){
    int mediana = 0;
    int first , last , middle , indice_metade;
    
    indice_metade = (i+f)/2;
    first = c[i];
    last = c[f];
    middle = c[indice_metade];

    if(middle > first){
        if(middle < last){
            mediana = middle;
        }
        else{
            if(last > first){
                mediana = last;
            }
            else{
                mediana = first;
            }
        }
    }
    // middle menor que o first
    else{
        if(middle > last){
            mediana = middle;
        }
        else{
            if(last < first){
                mediana = last;
            }
            else{
                mediana = first;
            }
        }
    }

    return mediana;
}

void particionamento_hoare(){

}

void particionamento_lomuto(){

}

void quick_sort(int c[], int f , int i){
    // versão - código de aula
    int p;
    if(f>i){
        /* se for randomizado
        *  int r = random(i,f);
        * swap(c[i],c[r]); */

        /*  se for mediana de 3
        *   int m = mediana(c,i,f);
        *   swap(c[i],c[m]);   */

        // p = particionamento_algo
        quick_sort(c,i,p-1);
        quick_sort(c,p+1,f);
    }

}


int main(){
    int arr[3] = {3,1,2};
    int teste;
    teste = mediana3(arr,0,2);
    cout << teste << endl;
    return 0;
}