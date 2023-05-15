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
void function1(int a[], int size);
int function2(int a[], int size);
void function3(int g[][G_SIZE], int d[][G_SIZE], int size);
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
    { 0,  2,  0,  7,  0,  6,  0,  0, 19,  0},           // Bu program�n �al��ma s�resi O(size)+O(size^2)+O(size)+ O(size^2)+O(size^3)+O(size)+O(size^2)+O(size^2) = O(size^3)'t�r.
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

    function1(a, A_SIZE);
    printf("\nFunction1 Sonuc:\n");
    print1(a, A_SIZE);

    t = function2(a, A_SIZE);
    printf("\nFunction2 Sonuc: %d\n", t);

    printf("\nG:\n");
    print2(g, G_SIZE);

    function3(g, d, G_SIZE);
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

void function1(int a[], int size) {                          // Bu void fonksiyonu b�y�kten k����e do�ru s�ralama yap�yor.
    for (int i = 0; i < size - 1; i++) {                     // Bu fonksiyonun zaman karma��kl��� : i=0 1 kez kontrol edilir , i < size de�eri size , i++ de�eri size-1 kez kontrol edilir.	   
        for (int j = 0; j < size - 1 - i; j++) {             // Bu fonksiyonun zaman karma��kl��� : j=0 1 kez kontrol edilir , j < size de�eri size , j++ de�eri size-1 kez kontrol edilir.	    
            if (a[j] > a[j + 1]) {                           //
                int tmp = a[j];                              //     Bu k�s�m  fonksiyon for d�ng�lerinden  size^2 d�n�ce�i i�in  size^2 'dir
                a[j] = a[j + 1];                             //  Sonu� olarak bu fonksiyonun zaman karma��kl���  (1+size-1+size)*(1+size-1+size)+size^2 = O(size^2)'dir.                 
                a[j + 1] = tmp;													
            }
        }
    }
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


void function3(int g[][G_SIZE], int d[][G_SIZE], int size) { // a��rl�kl� bir grafikteki t�m �iftler aras�ndaki en k�sa yollar� hesaplar. D, grafikteki kenarlar�n a��rl�klar� ile ba�lat�lan bir mesafe matrisi olu�turur ve  
    														  //kenar� olmayan d���mler aras�ndaki mesafeyi sonsuzlu�a (INF) ayarlar. Ard�ndan, t�m olas� ara d���mleri dikkate alarak mesafe matrisini g�ncellemek i�in ��l� i� i�e d�ng� yapar.	
	
	
	
	
	for (int i = 0; i < size; i++) {                          // Bu fonksiyonun zaman karma��kl��� : i=0 1 kez kontrol edilir , i < size+1 de�eri size , i++ de�eri size kez kontrol edilir.	           
        for (int j = 0; j < size; j++) { 					 // Bu fonksiyonun zaman karma��kl��� : j=0 1 kez kontrol edilir , j < size+1 de�eri size , j++ de�eri size kez kontrol edilir.		
            if (i == j) {                   //
                d[i][j] = 0; 				//
            }
            else if (g[i][j] != 0) {        //
			     d[i][j] = g[i][j];         //             						
                                            //      Bu k�s�m  fonksiyon for d�ng�lerinden  size^2 d�n�ce�i i�in  size^2 'dir
            }                               //
            else {							//			Sonu� olarak bu fonksiyonun zaman karma��kl���  (1+size+1+size)*(1+size+1+size)+6size^2 = O(size^2)'dir. 
                d[i][j] = INF;				//	
            }
        }
    }

    for (int k = 0; k < size; k++) {                 // Bu fonksiyonun zaman karma��kl��� : k=0 1 kez kontrol edilir , k < size+1 de�eri size , k++ de�eri size kez kontrol edilir.	       
        for (int i = 0; i < size; i++) {			//   Bu fonksiyonun zaman karma��kl��� : i=0 1 kez kontrol edilir , i < size+1 de�eri size , i++ de�eri size kez kontrol edilir.	    
            for (int j = 0; j < size; j++) {		 // Bu fonksiyonun zaman karma��kl��� : j=0 1 kez kontrol edilir , j < size+1 de�eri size , j++ de�eri size kez kontrol edilir.	    
                if (d[i][k] != INF && d[k][j] != INF && //   Bu k�s�m  fonksiyon for d�ng�lerinden  size^3 d�n�ce�i i�in  size^3 'dir
                    d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }          								// 	Sonu� olarak bu fonksiyonun zaman karma��kl���  (1+size+1+size)*(1+size+1+size)*(1+size+1+size)+2size^3 = O(size^3)'dir. 
        }
    }
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
