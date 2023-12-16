#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

void set_interface_attribs(int fd, int speed) {
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0) {
        perror("Error from tcgetattr");
        exit(EXIT_FAILURE);
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag |= (CLOCAL | CREAD); /* ignore modem controls, enable reading */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;      /* 8-bit characters */
    tty.c_cflag &= ~PARENB;  /* no parity bit */
    tty.c_cflag &= ~CSTOPB;  /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS; /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error from tcsetattr");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    //Очищаем терминал
    printf("\033[2J");
    // Скрыть курсор
    printf("\033[?25l");

    pid_t child_pid;

    // Создание нового процесса
    child_pid = fork();

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <baud_rate> <tty_port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int baud_rate = atoi(argv[1]);
    char *tty_port = argv[2];

    int fd = open(tty_port, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        perror("Error opening serial port");
        exit(EXIT_FAILURE);
    }

    set_interface_attribs(fd, baud_rate);

    while (1) {
        char buffer[256];
        char message[256];
        uint8_t enter_cursor = 0;
        uint8_t num_char = 0;
    
    
        if (child_pid == -1) {
            fprintf(stderr, "Error forking process\n");
        return 1;
        }

        if (child_pid == 0) {
            printf("Enter text to send (Ctrl+C to exit): ");
            char buffer[256];
            fgets(buffer, sizeof(buffer), stdin);

            write(fd, buffer, strlen(buffer));

        } else {
            // Код, выполняемый в родительском процессе
            size_t n = read(fd, buffer, sizeof(buffer));
            usleep(1000);
            if (n > 0) {
                //printf("Received: %.*s", (char)n, buffer);
                //printf("\n");
                //usleep(100000);
            }
        }

        usleep(100000); // Пауза 100 миллисекунд
    }
    //Делаем курсор видимым
    printf("\033[?25h");
    close(fd);
    return 0;
}
