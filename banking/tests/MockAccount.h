#pragma once
#include <gmock/gmock.h>

#include "../Account.h"
#include "../Account.cpp"

class MockAccount : public Account {
 public:
  MockAccount(int id, int balance) : Account(id, balance) {}

  MOCK_METHOD((int), GetBalance, (), (const, override));
  MOCK_METHOD((void), ChangeBalance, (int diff), (override));
  MOCK_METHOD((void), Lock, (), (override));
  MOCK_METHOD((void), Unlock, (), (override));
  MOCK_METHOD((int), id, (), (const));
};
