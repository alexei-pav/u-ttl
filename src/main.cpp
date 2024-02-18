#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstring>

// Function to enable/disable terminal input echoing
void echo(bool enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (enable)
        tty.c_lflag |= ECHO;
    else
        tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void set_interface_attribs(int fd, int speed) 
{
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

int main(void) 
{
    // Disable terminal input echoing
    echo(false);
    set_interface_attribs();

    // Print welcome message
    std::cout << "Welcome to My TUI Program!" << std::endl;
    std::cout << "Press 'q' to quit." << std::endl;

    // Loop to capture user input
    char ch;
    while (std::cin >> ch && ch != 'q') {
        // Clear screen and display user input
        std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear screen
        std::cout << "You pressed '" << ch << "'." << std::endl;
        std::cout << "Press 'q' to quit." << std::endl;
    }

    // Re-enable terminal input echoing
    echo(true);

    return 0;
}
