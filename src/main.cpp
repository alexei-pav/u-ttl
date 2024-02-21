#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstring>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

using namespace std::chrono_literals;

int main(int argc, char *argv[]) 
{
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <baud_rate> <port_name>" << std::endl;
    return 1;
  }

  // Get baud rate and port from arguments
  int baud_rate = std::stoi(argv[1]);
  std::string port_name = argv[2];

  // Open serial port
  int fd = open(port_name.c_str(), O_RDWR | O_NOCTTY);
  if (fd < 0) {
    std::cerr << "Error opening port: " << port_name << std::endl;
    return 1;
  }


  // Set port configuration
  struct termios options;
  tcgetattr(fd, &options);
  cfsetispeed(&options, baud_rate);
  cfsetospeed(&options, baud_rate);
  options.c_cflag &= ~PARENB;                 // Disable parity
  options.c_cflag &= ~CSTOPB;                 // 1 stop bit
  options.c_cflag &= ~CRTSCTS;                // No hardware flow control
  options.c_cflag |= CS8;                     // 8 bits per character
  options.c_iflag &= ~(IXON | IXOFF | IXANY); // No software flow control
  options.c_lflag &= ~ICANON;                 // Non-canonical mode
  options.c_cc[VMIN] = 1;                     // Read one byte at a time
  options.c_cc[VTIME] = 0;;
  tcsetattr(fd, TCSANOW, &options);

  // Clear terminal
  std::cout << "\033[2J\033[1;1H";
  
  // Thread for receiving data
  std::thread receive_thread([&]() {
    while (true) {
      char buffer[128];
      ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
      if (bytes_read < 0) {
        std::cerr << "Error reading from port: " << strerror(errno) << std::endl;
        exit(-1);
      } 
      if (bytes_read > 0) {
        std::string data(buffer, bytes_read);
        std::cout << data << std::flush;
      }
    }
  });

  // Read input and send to port
  while (true) {
    std::string line;
    std::getline(std::cin, line);
    if (line == "exit()") {
      exit(0);
    } else if (line == "clear()"){
      std::cout << "\033[2J\033[1;1H";
    }
    ssize_t bytes_written = write(fd, line.c_str(), line.size());
    if (bytes_written < 0) {
      std::cerr << "Error writing to port: " << strerror(errno) << std::endl;
      exit(-1);
    }
  }

  // Wait for receive thread and close port
  receive_thread.join();
  close(fd);

  return 0;
}
