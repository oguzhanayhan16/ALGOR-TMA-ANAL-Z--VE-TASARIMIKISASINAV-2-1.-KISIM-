#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define A_SIZE 20
#define G_SIZE 10
#define MAX_W 10

//Max deger icin sonsuz sayi
#define INF INT_MAX

void generate(int a[], int size);
void quick_sort(int arr[],int left,int right);
int function2(int a[], int size);

void function3(int g[][G_SIZE], int size, int src, int d[][G_SIZE]);
int minDistance(int d[][G_SIZE], bool visited[], int size, int src) ;
void print1(int a[], int size);
void print2(int g[][G_SIZE], int size);
void print3(int g[][G_SIZE], int size, int t);

int main() {
    int a[A_SIZE];
    int g[G_SIZE][G_SIZE] = {
    { 0, 10,  3,  0,  0,  5,  0, 17,  0, 22},
    {10,  0,  5,  0,  2,  0, 13,  0,  0,  0},
    { 3,  5,  0,  2,  0,  4,  0, 21,  0, 11},          // Fonksiyonlar rastgele say�lar olu�turur, say�lar� s�ralar, say�lar �zerinde bir i�lem yapar, bir graf matrisi olu�turur
    { 0,  0,  2,  0,  7,  0,  6,  0,  0,  0},          // ve graf matrisi �zerinde bir i�lem yapar. Program ayr�ca, her bir fonksiyonun �al��ma s�resini hesaplar ve sonu�lar� ekrana basar.
    { 0,  2,  0,  7,  0,  6,  0,  0, 19,  0},          // Bu program�n �al��ma s�resi O(size)+O(n logn)+O(size)+ O(size^2)+O(size^2)+O(size)+O(size)+O(size^2)+O(size^2) = O(size^2)'dir.
    { 5,  0,  4,  0,  6,  0,  9,  3,  0,  0},
    { 0, 13,  0,  6,  0,  9,  0,  4,  0,  0},
    {17,  0, 21,  0,  0,  3,  4,  0,  8,  0},
    { 0,  0,  0,  0, 19,  0,  0,  8,  0,  5},
    {22,  0, 11,  0,  0,  0,  0,  0,  5,  0}
    };
    int d[G_SIZE][G_SIZE];
    int t;

    // Rastgele sayi uretici icin seed
    srand(time(NULL));

    // Calisma suresinin hesaplanmasi
    clock_t start, end;
    double time;                  

    start = clock();

    generate(a, A_SIZE);
    printf("A:\n");
    print1(a, A_SIZE);

    quick_sort(a,0, A_SIZE-1);
    printf("\nFunction1 Sonuc:\n");
    print1(a, A_SIZE);

    t = function2(a, A_SIZE);
    printf("\nFunction2 Sonuc: %d\n", t);

    printf("\nG:\n");
    print2(g, G_SIZE);

 
    function3(g,G_SIZE,0,d);
    printf("\nFunction3 Sonuc:\n");
    print2(d, G_SIZE);

    printf("\n%d icin sonuc:\n", t);
    print3(d, G_SIZE, t);

    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nCalisma Suresi: %f sn\n", time);

    return 0;
}

void generate(int a[], int size) {                        			 //RASTGELE SAYILAR �RET�R VE A D�Z�S�NE DOLDURUR.                
    for (int i = 0; i < size; i++) {                                 // Bu fonksiyonun zaman karma��kl��� : i=0 1 kez kontrol edilir , i < size de�eri size+1 , i++ de�eri size kez kontrol edilir.	
        a[i] = rand() % (2 * MAX_W) - MAX_W;        				// bu k�s�mda  size kez kontrol edilmektedir.
       											                    // Yani fonksiyon = 1+size+1+size+size = 3size+2 = o(size)'dir.
    }
}

void quick_sort(int arr[], int left, int right) {
    int i = left, j = right;
    int tmp;									// burdaki s�ralama alogritmas� quick sort alogritmas� ile de�i�tirilerek daha h�zl� �al���lmas� ve en k�t� durumu O(n logn) yap�lm��t�r.
    int pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {											
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j)
        quick_sort(arr, left, j);
    if (i < right)
        quick_sort(arr, i, right);
}

int function2(int a[], int size) {            //max ard���k ort hesaplar. Toplam t'nin �st�ne ��kt���nda max toplam (t) g�ncellenir. Ayr�ca max toplama ula�an ard���k alt dizilerin say�s�n�da sayar, bu say� ort hesaplamak i�in kullan�l�r.  
    int t = 0, current_sum = 0, count=0;       
    for (int i = 0; i < size; i++) {             // Bu fonksiyonun zaman karma��kl��� : i=0 1 kez kontrol edilir , i < size+1 de�eri size+1 , i++ de�eri size kez kontrol edilir.	
        if (current_sum + a[i] > 0) {            // 
            current_sum = current_sum + a[i];    //      
        }                                        //      
        else {  								 //
            current_sum = 0;                     //       Bu k�s�mda 8size kez kontrol edilir.
        }        								//	
        if (current_sum > t) {                  //
            t = current_sum;                    //
            count++;                            //
        }
    }                 								
    return t/count;                            //              // Yani fonksiyon = 1+size+1+size+8size =10size+2  = O(size)'dir.
    }


void function3(int g[][G_SIZE], int size, int src, int d[][G_SIZE]) {// fonksiyon dijkstra algotitmas� ile de�i�tirilmi�tir.
    bool visited[size];
   	for (int i = 0; i < size; i++) {      	//    Bu fonksiyonun zaman karma��kl��� : i=0 1 kez kontrol edilir , i < size+1 de�eri size+1 , i++ de�eri size kez kontrol edilir.	                       
        for (int j = 0; j < size; j++) { 	//	   Bu fonksiyonun zaman karma��kl��� : j=0 1 kez kontrol edilir , j < size+1 de�eri size+1 , j++ de�eri size kez kontrol edilir.			
            if (i == j) {                   //     
                d[i][j] = 0; 				//
            }     							//   burdaki de�erler O(size^2) kadar kontrol edilir.
            else if (g[i][j] != 0) {        //  
			     d[i][j] = g[i][j];         //             						
                                            //    
            }                               //
            else {							//	 
                d[i][j] = INF;				//	 
            }
        }
    }
    d[src][src] = 0;
    for (int i = 0; i < size ; i++) {						// Bu fonksiyonun zaman karma��kl��� : i=0 1 kez kontrol edilir , i < size+1 de�eri size+1 , i++ de�eri size kez kontrol edilir.	  
        int u = minDistance(d, visited,size, i); 			//
        visited[u] = true;									//	burdaki de�erler size kadar kontrol edilir
        for (int v = 0; v < size; v++) {					//	 Bu fonksiyonun zaman karma��kl��� : v=0 1 kez kontrol edilir , v < size+1 de�eri size+1 , v++ de�eri size kez kontrol edilir.	  
            if (!visited[v] && g[u][v] && d[src][u] != INF && //
                d[src][u] + g[u][v] < d[src][v]) {			//  burdaki de�erler O(size^2) kadar kontrol edilir		
                d[src][v] = d[src][u] + g[u][v];			//
            }												// Burdaki fonksiyon de�i�tirilerek O(size^3) zaman karma��kl���na sahip fonksiyon O(size^2) yap�lm��t�r.
        }
    }
}

int minDistance(int d[][G_SIZE], bool visited[], int size, int src) {
    int min = INF, min_index;
    for (int i = 0; i < size; i++) {                    //Burdaki fonksiyon function3'e ba�l� bir fonksiyondur ve O(size) zaman karma��kl���na sahiptir.
        if (!visited[i] && d[src][i] <= min) {
            min = d[src][i];
            min_index = i; 				
        }
    }
    return min_index;
}
void print1(int a[], int size) {		// a dizisini yazd�r�r
    for (int i = 0; i < size; i++) {			//  Bu fonksiyonun zaman karma��kl��� : i=0 1 kez kontrol edilir , i < size+1 de�eri size , i++ de�eri size kez kontrol edilir.	
        printf("%d ", a[i]);           			// bu k�s�mda  size kez kontrol edilmektedir.
                                                  

        if ((i + 1) % 10 == 0) {				// bu k�s�mda  size kez kontrol edilmektedir.
            printf("\n");						// bu k�s�mda  size kez kontrol edilmektedir.	
        }										// Yani fonksiyon = 1+size+1+size+3size = 5size+2 = o(size)'dir.
    }												
}

void print2(int g[][G_SIZE], int size) { 		  //  g matrisinin elemanlar�n� yazd�r�r
    for (int i = 0; i < size; i++) {					//  Bu fonksiyonun zaman karma��kl��� : i=0 1 kez kontrol edilir , i < size+1 de�eri size , i++ de�eri size kez kontrol edilir.	
        for (int j = 0; j < size; j++) {			    // Bu fonksiyonun zaman karma��kl��� : j=0 1 kez kontrol edilir , j < size+1 de�eri size , j++ de�eri size kez kontrol edilir.	 
            if (g[i][j] == INF) {                       //
														// 
                printf("INF ");							//    
            }											// Bu k�s�m  fonksiyon for d�ng�lerinden  size^2 d�n�ce�i i�in  size^2 'dir
            else {										//			
                printf("%3d ", g[i][j]);				//
            }
        }
        printf("\n");									// Sonu� olarak bu fonksiyonun zaman karma��kl���  (1+size-1+size)*(1+size-1+size)+4size^2 = O(size^2)'dir.   
    }
}

void print3(int d[][G_SIZE], int size, int t) {		    // g matrisindeki �ift d���mleri ve mesafaleri t ye e�it olanlar� yazd�r�r.
    for (int i = 0; i < size; i++) { 						//  Bu fonksiyonun zaman karma��kl��� : i=0 1 kez kontrol edilir , i < size+1 de�eri size , i++ de�eri size kez kontrol edilir.	
        for (int j = 0; j < size; j++) {                    // Bu fonksiyonun zaman karma��kl��� : j=0 1 kez kontrol edilir , j < size+1 de�eri size , j++ de�eri size kez kontrol edilir.
            if (i != j && d[i][j] < t) {                                //
                printf("%c -> %c: %d\n", 'A' + i, 'A' + j, d[i][j]);    //  Bu k�s�m  fonksiyon for d�ng�lerinden  size^2 d�n�ce�i i�in  size^2 'dir.
            }                                    					// Sonu� olarak bu fonksiyonun zaman karma��kl���  (1+size-1+size)*(1+size-1+size)+2size^2 = O(size^2)'dir.  
        }
    }
}
