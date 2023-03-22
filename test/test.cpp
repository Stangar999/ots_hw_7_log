#include <gtest/gtest.h>

#include <iostream>
#include <tuple>
#include <vector>

#include "command_handler.h"
#include "log_users.h"

using namespace std::literals;

TEST(CorrectLog, LogStaticFull) {
  std::ostringstream out;
  const std::shared_ptr<IObserver> ostream_logger =
      std::make_shared<OstreamLogger>(out);
  CommandHandler ch(3, {&ostream_logger});

  std::stringstream in;
  in << "c1" << '\n';
  in << "c2" << '\n';
  in << "c3" << '\n';

  ReadCommand(ch, in);

  std::ostringstream out_res;
  out_res.str("bulk: c1, c2, c3\n"s);

  ASSERT_EQ(out_res.str(), out.str());
}

TEST(CorrectLog, LogStaticEoF) {
  std::ostringstream out;
  const std::shared_ptr<IObserver> ostream_logger =
      std::make_shared<OstreamLogger>(out);
  CommandHandler ch(3, {&ostream_logger});

  std::stringstream in;
  in << "c1\nc2\n";

  ReadCommand(ch, in);

  std::ostringstream out_res;
  out_res.str("bulk: c1, c2\n"s);

  ASSERT_EQ(out_res.str(), out.str());
}

TEST(CorrectLog, LogDin) {
  std::ostringstream out;
  const std::shared_ptr<IObserver> ostream_logger =
      std::make_shared<OstreamLogger>(out);
  CommandHandler ch(3, {&ostream_logger});

  std::stringstream in;
  in << "c1" << '\n';
  in << "c2" << '\n';
  in << "{" << '\n';
  in << "c3" << '\n';
  in << "c4" << '\n';
  in << "}" << '\n';
  in << "{" << '\n';
  in << "c5" << '\n';
  in << "c6" << '\n';
  in << "{" << '\n';
  in << "c7" << '\n';
  in << "c8" << '\n';
  in << "}" << '\n';
  in << "c9" << '\n';
  in << "}" << '\n';
  in << "{" << '\n';
  in << "c10" << '\n';
  in << "c11" << '\n';
  ReadCommand(ch, in);

  std::ostringstream out_res;
  out_res.str("bulk: c1, c2\nbulk: c3, c4\nbulk: c5, c6, c7, c8, c9\n"s);

  ASSERT_EQ(out_res.str(), out.str());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
