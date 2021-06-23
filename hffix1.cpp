// hffix1.cpp : This file contains the 'main' function. Program execution begins
// and ends there.
//

#include "pch.h"
#include <iostream>

constexpr auto FIX40 = "FIX.4.0";
constexpr auto FIX41 = "FIX.4.1";
constexpr auto FIX42 = "FIX.4.2";
constexpr auto FIX43 = "FIX.4.3";
constexpr auto FIX44 = "FIX.4.4";
constexpr auto FIX50 = "FIX.5.0";
constexpr auto FIX501 = "FIX.5.0SP2";
constexpr auto FIX502 = "FIX.5.0SP2";
constexpr auto FIX11 = "FIXT.1.1";

using namespace std;

//
//void HffixLogon (UINT uintPrmFix) {
//
///*
//FIX.4.0
//FIX.4.1
//FIX.4.2
//FIX.4.3
//FIX.4.4
//FIX.5.0
//FIX.5.0SP1
//FIX.5.0SP2
//FIXT.1.1
//*/
//
//
//
//    int seq_send(1);  // Sending sequence number.
//
//    char buffer[1 << 13];
//
//    struct tm ltm;
//    __time64_t long_time;
//    _time64(&long_time);
//    _localtime64_s(&ltm, &long_time);
//
//    hffix::message_writer logon(buffer, buffer + sizeof(buffer));
//
//    switch (uintPrmFix) {
//        case 1:
//        case 2:
//        case 3:
//        case 4:
//            // Write BeginString and BodyLength.
//            logon.push_back_header(FIX40);
//            // Logon MsgType.
//            logon.push_back_string(hffix::tag::MsgType, "A");
//            logon.push_back_string(hffix::tag::SenderCompID, "AAAA");
//            logon.push_back_string(hffix::tag::TargetCompID, "BBBB");
//            logon.push_back_int(hffix::tag::MsgSeqNum, seq_send++);
//            // logon.push_back_timestamp(hffix::tag::SendingTime, tsend);
//            logon.push_back_timestamp(hffix::tag::SendingTime, (1900 + ltm.tm_year),
//                                      (1 + ltm.tm_mon), ltm.tm_mday, ltm.tm_hour,
//                                      ltm.tm_min, ltm.tm_sec);
//            // No encryption.
//            logon.push_back_int(hffix::tag::EncryptMethod, 0);
//            // 10 second heartbeat interval.
//            logon.push_back_int(hffix::tag::HeartBtInt, 10);
//            // write CheckSum.
//            logon.push_back_trailer();
//        break;
//        case 5:
//
//          break;
//
//    }
//
//
//
//}
//




int main(int argc, char** argv) {
  int seq_send(1);  // Sending sequence number.

  char buffer[1 << 13];

  struct tm ltm;
  __time64_t long_time;
  _time64(&long_time);
  _localtime64_s(&ltm, &long_time);

  // ptime tsend(date(2017, 8, 9), time_duration(12, 34, 56));

  // We'll put a FIX Logon message in the buffer.
  hffix::message_writer logon(buffer, buffer + sizeof(buffer));

  logon.push_back_header("FIX.4.4");  // Write BeginString and BodyLength.

  // Logon MsgType.
  logon.push_back_string(hffix::tag::MsgType, "A");

  logon.push_back_string(hffix::tag::SenderCompID, "AAAA");
  logon.push_back_string(hffix::tag::TargetCompID, "BBBB");
  logon.push_back_int(hffix::tag::MsgSeqNum, seq_send++);
  // logon.push_back_timestamp(hffix::tag::SendingTime, tsend);
  logon.push_back_timestamp(hffix::tag::SendingTime, (1900 + ltm.tm_year),
                            (1 + ltm.tm_mon), ltm.tm_mday, ltm.tm_hour,
                            ltm.tm_min, ltm.tm_sec);
  // No encryption.
  logon.push_back_int(hffix::tag::EncryptMethod, 0);
  // 10 second heartbeat interval.
  logon.push_back_int(hffix::tag::HeartBtInt, 10);

  logon.push_back_trailer();  // write CheckSum.

  // Now the Logon message is written to the buffer.

  // Add a FIX New Order - Single message to the buffer, after the Logon
  // message.
  hffix::message_writer new_order(logon.message_end(), buffer + sizeof(buffer));

  new_order.push_back_header("FIX.4.4");

  // New Order - Single
  new_order.push_back_string(hffix::tag::MsgType, "D");
  // Required Standard Header field.
  new_order.push_back_string(hffix::tag::SenderCompID, "AAAA");
  new_order.push_back_string(hffix::tag::TargetCompID, "BBBB");
  new_order.push_back_int(hffix::tag::MsgSeqNum, seq_send++);
  new_order.push_back_timestamp(hffix::tag::SendingTime, (1900 + ltm.tm_year),
                                (1 + ltm.tm_mon), ltm.tm_mday, ltm.tm_hour,
                                ltm.tm_min, ltm.tm_sec);
  new_order.push_back_string(hffix::tag::ClOrdID, "A1");
  // Automated execution.
  new_order.push_back_char(hffix::tag::HandlInst, '1');
  // Ticker symbol OIH.
  new_order.push_back_string(hffix::tag::Symbol, "OIH");
  // Buy side.
  new_order.push_back_char(hffix::tag::Side, '1');
  new_order.push_back_timestamp(hffix::tag::TransactTime, (1900 + ltm.tm_year),
                                (1 + ltm.tm_mon), ltm.tm_mday, ltm.tm_hour,
                                ltm.tm_min, ltm.tm_sec);
  // 100 shares.
  new_order.push_back_int(hffix::tag::OrderQty, 100);
  // Limit order.
  new_order.push_back_char(hffix::tag::OrdType, '2');
  // Limit price $500.01 = 50001*(10^-2). The push_back_decimal() method
  // takes a decimal floating point number of the form mantissa*(10^exponent).
  new_order.push_back_decimal(hffix::tag::Price, 50001, -2);
  // Good Till Cancel.
  new_order.push_back_char(hffix::tag::TimeInForce, '1');

  new_order.push_back_trailer();  // write CheckSum.

  // Now the New Order message is in the buffer after the Logon message.

  // Write both messages to stdout.
  std::cout.write(buffer, new_order.message_end() - buffer);

  return 0;
}
