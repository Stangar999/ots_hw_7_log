﻿#include <gtest/gtest.h>

#include <iostream>
#include <tuple>
#include <vector>

#include "command_handler.h"
#include "log_users.h"

using namespace std::literals;

TEST(CorrectLog, LogStaticFull) {
  std::ostringstream out;
  const std::shared_ptr<IObserver> ostream_logger = std::make_shared<OstreamLogger>(out);
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
  const std::shared_ptr<IObserver> ostream_logger = std::make_shared<OstreamLogger>(out);
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
  const std::shared_ptr<IObserver> ostream_logger = std::make_shared<OstreamLogger>(out);
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

// TEST(CorrectMatrix, CheckNMatrix) {
//   Matrix<int, -1, 3> matrix;
//   ASSERT_EQ(matrix.size(), 0);

//  auto a = matrix[0][0][0];
//  ASSERT_EQ(static_cast<int>(a), -1);
//  ASSERT_EQ(matrix.size(), 0);

//  matrix[100][100][100] = 314;
//  matrix[105][100][110] = 214;
//  matrix[108][100][110] = 114;
//  ASSERT_EQ(static_cast<int>(matrix[100][100][100]), 314);
//  ASSERT_EQ(matrix.size(), 3);

//  std::stringstream in;

//  for (auto c : matrix) {
//    auto [x, y, z, v] = c;
//    in << x << " " << y << " " << z << " " << v << std::endl;
//  }
//}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
