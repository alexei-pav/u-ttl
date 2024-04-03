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

int main(int argc, char *argv[]) {
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
  options.c_cflag |= PARENB;                  // Enable parity
  options.c_cflag &= ~INPCK;                  // Don't check parity
  options.c_cflag &= ~CSIZE;                  // 8 bits per character
  options.c_cflag |= CS8;                     // Set data bits
  options.c_cflag &= ~CRTSCTS;                // No hardware flow control
  options.c_iflag &= ~(IXON | IXOFF | IXANY); // No software flow control
  options.c_lflag &= ~ICANON;                 // Non-canonical mode
  options.c_cc[VMIN] = 1;                     // Read one byte at a time
  options.c_cc[VTIME] = 8;

  tcsetattr(fd, TCSANOW, &options);

  // Thread for receiving data
  std::thread receive_thread([&]() {
    bool isEndLine = false;
    while (true) {
      char* buffer = new char[128];
      ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
      if (bytes_read < 0) {
        std::cerr << "Error reading from port: " << strerror(errno) << std::endl;
        break;
      } else {
        std::string data(buffer, bytes_read);
        std::cout << data << std::flush;
      }
      if (isEndLine == true){
        std::cout << std::endl;
      }
      delete[] buffer;
    }
  });

  // Read input and send to port
  while (true) {
    std::string line;
    std::getline(std::cin, line);
    if (line == "exit") {
      break;
    }
    ssize_t bytes_written = write(fd, line.data(), line.size());
    if (bytes_written < 0) {
      std::cerr << "Error writing to port: " << strerror(errno) << std::endl;
      break;
    }
  }

  // Wait for receive thread and close port
  receive_thread.join();
  close(fd);

  return 0;
}
