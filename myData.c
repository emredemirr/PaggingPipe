#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 

int main(int argc, char *argv[])
{
    char geciciKarakter; //Geçiçi karakterlerin tutulduğu değişken.
    char kayit[10000]; //Pipe ile gönderilen dosyayı kaydeden değişken.
    int sayac; // Dosyanın okunmasını sağlayan değişken.
    int fd[2]; // pipe oluştururken yazılması gereken satır, bu satır pipe'ın read ve write olarak 2 adet değeri olduğunu belirtir.
    pid_t pid; // prosses id değişkeni.
    FILE *pf = fopen(argv[1], "r"); // Dosya açma.

    if (argc == 2)
    {
        while( (geciciKarakter = fgetc(pf)) != EOF) // Dosyadan okuma.
        {
            printf("%c", geciciKarakter);
        }
    }
    else if(argc == 4)
    {
        sayac = 0;
        while( (geciciKarakter = fgetc(pf)) != EOF) // dosyadan okunan karakterler kayit dizisine aktarılıyor.
        {
            kayit[sayac] = geciciKarakter;
            sayac++;
        }
        
        pipe(fd); // Pipe oluşturuldu
        pid = fork(); // Fork kullanarak parent processten child process oluşturuyoruz
        if (pid>0) // Process id değeri 0 dan büyükse parent process çalışıyor demektir.
        {
            close(fd[0]);
            write(fd[1], kayit, strlen(kayit)+1); // kayit dizisinin içindekiler pipe'a yazılıyor
            close(fd[1]);
            wait(NULL); // child prosses'in işlemini bitirmesi bekleniyor
            printf("Parent process sonlandırıldı.\n");
        }
        else
        {
            close(fd[1]);
            char pipeReadEnd[20];
            sprintf(pipeReadEnd, "%d", fd[0]);
            argv[4] = pipeReadEnd;
            execv(argv[3] , argv); // myData yazi.txt = myMore şeklinde yazılacağından gelen 3. parametreyi execv komutu ile çalıştırıyoruz.
        }
    }
}
