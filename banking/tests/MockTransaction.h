#pragma once
#include <gmock/gmock.h>

#include "../Transaction.h"
#include "../Transaction.cpp"

class MockTransaction : public Transaction {
 public:
  MOCK_METHOD((bool), Make, (Account& from, Account& to, int sum), ());
  MOCK_METHOD((int), fee, (), (const));
  MOCK_METHOD((void), set_fee, (int fee), ());
  MOCK_METHOD((void), Credit, (Account& account, int sum), ());
  MOCK_METHOD((void), Debit, (Account& account, int sum), ());
  MOCK_METHOD((void), SaveToDataBase, (Account& from, Account& to, int sum), (override));
};
