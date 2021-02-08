#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
 

int main(int argc, char *argv[])
{
    char geciciKarakter; //Geçiçi karakterlerin tutulduğu değişken.
    char alinanInput; //Kullanıcının bastığı tuşu tutan değişken.
    int sayac; //kaçıncı satırda olduğunu tuttuğumuz değişken
    int pipeReadEnd = atoi(argv[4]); //myData'da oluşturulan pipe'ın okunma değişkeni.
    int index = 0; //alınan stringin yazdırılan indis değerini tuttuğumuz değişken.
    char kayit[10000]; //Pipe ile gönderilen dosyayı kaydeden değişken.
    read(pipeReadEnd, kayit, 10000); //Pipe dan gelen veri kayit değişkenine aktarılır.
    close(pipeReadEnd); // pipe'ın okuması sona erer.

    while (1)// myData'dan gelen dosyanın içeriği okur ve 24 satırlık parçalara böler.
    {
        sayac = 0;
        while(sayac < 24)
        {
            printf("%c", kayit[index]);//Satır sayısı 24 olana kadar ekrana yazdırır.
            if (kayit[index] == '\n') // Satır karakterine gelince satır sayısını arttırır.
            {
                sayac++;
            }
            index++;   
            if (strlen(kayit) < index) 
                break;
        }
        if (strlen(kayit) < index)
            break;
        
        printf("\nTuşa basınız: ");
        scanf("%c", &alinanInput); // Kullanıcıdan input alınır.
        while((geciciKarakter = getchar()) != '\n' && geciciKarakter != EOF); //Hatalı input girişlerini engeller.
        printf("\n");
        
        if (alinanInput == ' ') 
            continue; // Space karakterine basıldıysa devam et.
        else if (alinanInput == 'q') 
            break; // q karakterine basıldıysa okuma işlemi sonlanır.
    }
    printf("\n\nChild procces sonlandırıldı.\n");
    return 0;
}