#include <unistd.h>
#include <fcntl.h>
#include <string>

class SysFsFile {
protected:
  int fd;
  std::string lastValue;
public:
  bool isValid() const {
    return fd >= 0;
  }
  bool open(const std::string &name) {
    if (fd >= 0)
      ::close(fd);

    fd = ::open(name.c_str(), O_RDWR);

    return fd >= 0;
  }
  void close() {
    if (isValid())
      ::close(fd);
    fd = -1;
  }

  // Constructors and destructor
  SysFsFile() {
    fd = -1;
  }
  SysFsFile(const std::string &name) {
    fd = -1;
    open(name);
  }
  ~SysFsFile() {
    close();
  }

  // Set Value
  const std::string &operator= (const std::string &src) {
    if (isValid())
      ::write(fd, src.c_str(), src.length());

    return src;
  }

  // Read and save value
  const std::string &read() {
    lastValue = "";

    if (!isValid())
      return lastValue;

    char buff[256];
    int n = ::read(fd, buff, sizeof(buff));
    if (n < 0)
      return lastValue;

    lastValue = std::string(buff,n);

    return lastValue;
  }

  // Direct string conversion returns last value.
  operator std::string() const {
    return lastValue;
  }
};
