#include <iostream>
#include <memory>
#include <vector>

#include "command_handler.h"
#include "log_users.h"
using namespace std;

int main(int argc, const char* argv[]) {
  int N = 0;
  if (argc > 1) {
    N = stoi(argv[1]);
  }
  const std::shared_ptr<IObserver> ostream_logger =
      std::make_shared<OstreamLogger>(std::cout);
  const std::shared_ptr<IObserver> file_logger = std::make_shared<FileLogger>();
  CommandHandler ch(N);
  ch.AddObserver(file_logger).AddObserver(ostream_logger);
  ReadCommand(ch, std::cin);
  return 0;
}
