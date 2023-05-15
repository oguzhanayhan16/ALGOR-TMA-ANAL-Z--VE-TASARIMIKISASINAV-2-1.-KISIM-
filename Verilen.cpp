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
    { 3,  5,  0,  2,  0,  4,  0, 21,  0, 11},          // Fonksiyonlar rastgele sayýlar oluþturur, sayýlarý sýralar, sayýlar üzerinde bir iþlem yapar, bir graf matrisi oluþturur
    { 0,  0,  2,  0,  7,  0,  6,  0,  0,  0},          // ve graf matrisi üzerinde bir iþlem yapar. Program ayrýca, her bir fonksiyonun çalýþma süresini hesaplar ve sonuçlarý ekrana basar.
    { 0,  2,  0,  7,  0,  6,  0,  0, 19,  0},           // Bu programýn çalýþma süresi O(size)+O(size^2)+O(size)+ O(size^2)+O(size^3)+O(size)+O(size^2)+O(size^2) = O(size^3)'tür.
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

void generate(int a[], int size) {                        			 //RASTGELE SAYILAR ÜRETÝR VE A DÝZÝSÝNE DOLDURUR.                
    for (int i = 0; i < size; i++) {                                 // Bu fonksiyonun zaman karmaþýklýðý : i=0 1 kez kontrol edilir , i < size deðeri size+1 , i++ deðeri size kez kontrol edilir.	
        a[i] = rand() % (2 * MAX_W) - MAX_W;        				// bu kýsýmda  size kez kontrol edilmektedir.
       											                    // Yani fonksiyon = 1+size+1+size+size = 3size+2 = o(size)'dir.
    }
}

void function1(int a[], int size) {                          // Bu void fonksiyonu büyükten küçüðe doðru sýralama yapýyor.
    for (int i = 0; i < size - 1; i++) {                     // Bu fonksiyonun zaman karmaþýklýðý : i=0 1 kez kontrol edilir , i < size deðeri size , i++ deðeri size-1 kez kontrol edilir.	   
        for (int j = 0; j < size - 1 - i; j++) {             // Bu fonksiyonun zaman karmaþýklýðý : j=0 1 kez kontrol edilir , j < size deðeri size , j++ deðeri size-1 kez kontrol edilir.	    
            if (a[j] > a[j + 1]) {                           //
                int tmp = a[j];                              //     Bu kýsým  fonksiyon for döngülerinden  size^2 dönüceði için  size^2 'dir
                a[j] = a[j + 1];                             //  Sonuç olarak bu fonksiyonun zaman karmaþýklýðý  (1+size-1+size)*(1+size-1+size)+size^2 = O(size^2)'dir.                 
                a[j + 1] = tmp;													
            }
        }
    }
}

int function2(int a[], int size) {            //max ardýþýk ort hesaplar. Toplam t'nin üstüne çýktýðýnda max toplam (t) güncellenir. Ayrýca max toplama ulaþan ardýþýk alt dizilerin sayýsýnýda sayar, bu sayý ort hesaplamak için kullanýlýr.  
    int t = 0, current_sum = 0, count=0;       
    for (int i = 0; i < size; i++) {             // Bu fonksiyonun zaman karmaþýklýðý : i=0 1 kez kontrol edilir , i < size+1 deðeri size+1 , i++ deðeri size kez kontrol edilir.	
        if (current_sum + a[i] > 0) {            // 
            current_sum = current_sum + a[i];    //      
        }                                        //      
        else {  								 //
            current_sum = 0;                     //       Bu kýsýmda 8size kez kontrol edilir.
        }        								//	
        if (current_sum > t) {                  //
            t = current_sum;                    //
            count++;                            //
        }
    }                 								
    return t/count;                            //              // Yani fonksiyon = 1+size+1+size+8size =10size+2  = O(size)'dir.
    }


void function3(int g[][G_SIZE], int d[][G_SIZE], int size) { // aðýrlýklý bir grafikteki tüm çiftler arasýndaki en kýsa yollarý hesaplar. D, grafikteki kenarlarýn aðýrlýklarý ile baþlatýlan bir mesafe matrisi oluþturur ve  
    														  //kenarý olmayan düðümler arasýndaki mesafeyi sonsuzluða (INF) ayarlar. Ardýndan, tüm olasý ara düðümleri dikkate alarak mesafe matrisini güncellemek için üçlü iç içe döngü yapar.	
	
	
	
	
	for (int i = 0; i < size; i++) {                          // Bu fonksiyonun zaman karmaþýklýðý : i=0 1 kez kontrol edilir , i < size+1 deðeri size , i++ deðeri size kez kontrol edilir.	           
        for (int j = 0; j < size; j++) { 					 // Bu fonksiyonun zaman karmaþýklýðý : j=0 1 kez kontrol edilir , j < size+1 deðeri size , j++ deðeri size kez kontrol edilir.		
            if (i == j) {                   //
                d[i][j] = 0; 				//
            }
            else if (g[i][j] != 0) {        //
			     d[i][j] = g[i][j];         //             						
                                            //      Bu kýsým  fonksiyon for döngülerinden  size^2 dönüceði için  size^2 'dir
            }                               //
            else {							//			Sonuç olarak bu fonksiyonun zaman karmaþýklýðý  (1+size+1+size)*(1+size+1+size)+6size^2 = O(size^2)'dir. 
                d[i][j] = INF;				//	
            }
        }
    }

    for (int k = 0; k < size; k++) {                 // Bu fonksiyonun zaman karmaþýklýðý : k=0 1 kez kontrol edilir , k < size+1 deðeri size , k++ deðeri size kez kontrol edilir.	       
        for (int i = 0; i < size; i++) {			//   Bu fonksiyonun zaman karmaþýklýðý : i=0 1 kez kontrol edilir , i < size+1 deðeri size , i++ deðeri size kez kontrol edilir.	    
            for (int j = 0; j < size; j++) {		 // Bu fonksiyonun zaman karmaþýklýðý : j=0 1 kez kontrol edilir , j < size+1 deðeri size , j++ deðeri size kez kontrol edilir.	    
                if (d[i][k] != INF && d[k][j] != INF && //   Bu kýsým  fonksiyon for döngülerinden  size^3 dönüceði için  size^3 'dir
                    d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }          								// 	Sonuç olarak bu fonksiyonun zaman karmaþýklýðý  (1+size+1+size)*(1+size+1+size)*(1+size+1+size)+2size^3 = O(size^3)'dir. 
        }
    }
}

void print1(int a[], int size) {		// a dizisini yazdýrýr
    for (int i = 0; i < size; i++) {			//  Bu fonksiyonun zaman karmaþýklýðý : i=0 1 kez kontrol edilir , i < size+1 deðeri size , i++ deðeri size kez kontrol edilir.	
        printf("%d ", a[i]);           			// bu kýsýmda  size kez kontrol edilmektedir.
                                                  

        if ((i + 1) % 10 == 0) {				// bu kýsýmda  size kez kontrol edilmektedir.
            printf("\n");						// bu kýsýmda  size kez kontrol edilmektedir.	
        }										// Yani fonksiyon = 1+size+1+size+3size = 5size+2 = o(size)'dir.
    }												
}

void print2(int g[][G_SIZE], int size) { 		  //  g matrisinin elemanlarýný yazdýrýr
    for (int i = 0; i < size; i++) {					//  Bu fonksiyonun zaman karmaþýklýðý : i=0 1 kez kontrol edilir , i < size+1 deðeri size , i++ deðeri size kez kontrol edilir.	
        for (int j = 0; j < size; j++) {			    // Bu fonksiyonun zaman karmaþýklýðý : j=0 1 kez kontrol edilir , j < size+1 deðeri size , j++ deðeri size kez kontrol edilir.	 
            if (g[i][j] == INF) {                       //
														// 
                printf("INF ");							//    
            }											// Bu kýsým  fonksiyon for döngülerinden  size^2 dönüceði için  size^2 'dir
            else {										//			
                printf("%3d ", g[i][j]);				//
            }
        }
        printf("\n");									// Sonuç olarak bu fonksiyonun zaman karmaþýklýðý  (1+size-1+size)*(1+size-1+size)+4size^2 = O(size^2)'dir.   
    }
}

void print3(int d[][G_SIZE], int size, int t) {		    // g matrisindeki çift düðümleri ve mesafaleri t ye eþit olanlarý yazdýrýr.
    for (int i = 0; i < size; i++) { 						//  Bu fonksiyonun zaman karmaþýklýðý : i=0 1 kez kontrol edilir , i < size+1 deðeri size , i++ deðeri size kez kontrol edilir.	
        for (int j = 0; j < size; j++) {                    // Bu fonksiyonun zaman karmaþýklýðý : j=0 1 kez kontrol edilir , j < size+1 deðeri size , j++ deðeri size kez kontrol edilir.
            if (i != j && d[i][j] < t) {                                //
                printf("%c -> %c: %d\n", 'A' + i, 'A' + j, d[i][j]);    //  Bu kýsým  fonksiyon for döngülerinden  size^2 dönüceði için  size^2 'dir.
            }                                    					// Sonuç olarak bu fonksiyonun zaman karmaþýklýðý  (1+size-1+size)*(1+size-1+size)+2size^2 = O(size^2)'dir.  
        }
    }
}
