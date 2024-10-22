#include<iostream>
#include<random>

using namespace std;

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

int particionamento_hoare(int c[],int left,int right){
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
    }
    swap(c[left],c[j]);

    return j;
}

int particionamento_lomuto(int c[], int left , int right){
    int key = c[left];
    int index = left +1 ;
    
    for(int i = left+1 ; i <= right ; i++){
        if(c[i] < key){
            swap(c[i] , c[index]);
            index++;
        }
    }
    swap(c[left], c[index-1]);

    return (index-1);
}

void quick_sort_lomuto(int c[], int i , int f){
    // versão - código de aula
    int p;
    if(f>i){
        /* se for randomizado
        *  int r = random(i,f);
        * swap(c[i],c[r]); */

        
        int m = mediana3(c,i,f);
        swap(c[i],c[m]);  

        p = particionamento_lomuto(c,i,f);
        quick_sort_lomuto(c,i,p-1);
        quick_sort_lomuto(c,p+1,f);
    }

}

void quick_sort_hoare(int c[] , int i , int f){
    // versão - código de aula
    int p;
    if(f>i){
        /* se for randomizado
        *  int r = random(i,f);
        * swap(c[i],c[r]); */

        
        int m = mediana3(c,i,f);
        swap(c[i],c[m]);  

        p = particionamento_hoare(c,i,f);
        quick_sort_hoare(c,i,p-1);
        quick_sort_hoare(c,p+1,f);
    }
}


int main(){
    // exemplo simples de mediana
    int arr[20] = {34, 7, 23, 32, 5, 62, 32, 45, 67, 89, 12, 34, 56, 78, 90, 21, 43, 65, 87, 9};
    print_array(arr,20);
    quick_sort_hoare(arr,0,19);
    print_array(arr,20);
    return 0;
}
/*  OQ FALTA FAZER
*   Lidar com o arq -> Ler e escrever
*   saber a quant de trocas e de chamadas recursivas
*   Ver quanto tempo leva para rodar o processo
*   Randomizar
*/