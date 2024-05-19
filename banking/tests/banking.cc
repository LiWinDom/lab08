#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MockAccount.h"

TEST(Account, Mock) {
  MockAccount obj(1, 0);
  EXPECT_CALL(obj, GetBalance()).Times(1);
  EXPECT_CALL(obj, ChangeBalance(1)).Times(1);
  EXPECT_CALL(obj, Lock()).Times(1);
  EXPECT_CALL(obj, Unlock()).Times(1);
  EXPECT_CALL(obj, id()).Times(1);

  obj.GetBalance();
  obj.ChangeBalance(1);
  obj.Lock();
  obj.Unlock();
  obj.id();
}

TEST(Account, Init) {
  MockAccount obj(12, 34);
  EXPECT_EQ(obj.Account::id(), 12);
  EXPECT_EQ(obj.Account::GetBalance(), 34);
}

TEST(Account, GetBalance) {
  MockAccount obj(1, 1000);
  EXPECT_EQ(obj.Account::GetBalance(), 1000);
}

TEST(Account, ChangeBalance) {
  MockAccount obj(1, 1000);
  EXPECT_THROW(obj.Account::ChangeBalance(100), std::runtime_error);
  obj.Account::Lock();
  EXPECT_NO_THROW(obj.Account::ChangeBalance(100));
  EXPECT_EQ(obj.Account::GetBalance(), 1100);
}

TEST(Account, Lock) {
  MockAccount obj(1, 1000);
  EXPECT_NO_THROW(obj.Account::Lock());
  EXPECT_THROW(obj.Account::Lock(), std::runtime_error);
}

TEST(Account, Unlock) {
  MockAccount obj(1, 1000);
  EXPECT_NO_THROW(obj.Account::Unlock());
  obj.Account::Lock();
  EXPECT_NO_THROW(obj.Account::Unlock());
}


#include "MockTransaction.h"

TEST(Transaction, Mock) {
  MockTransaction obj;
  EXPECT_CALL(obj, Make(testing::_, testing::_, 1)).Times(1);
  EXPECT_CALL(obj, fee()).Times(1);
  EXPECT_CALL(obj, set_fee(1)).Times(1);
  EXPECT_CALL(obj, Credit(testing::_, 1)).Times(1);
  EXPECT_CALL(obj, Debit(testing::_, 1)).Times(1);
  EXPECT_CALL(obj, SaveToDataBase(testing::_, testing::_, 1)).Times(1);

  Account acc1(1, 2), acc2(2, 1);
  obj.Make(acc1, acc2, 1);
  obj.fee();
  obj.set_fee(1);
  obj.Credit(acc1, 1);
  obj.Debit(acc2, 1);
  obj.SaveToDataBase(acc1, acc2, 1);
}

TEST(Transaction, Init) {
  MockTransaction obj;
  EXPECT_EQ(obj.Transaction::fee(), 1);
}

TEST(Transaction, Make) {
  MockTransaction obj;
  MockAccount acc1(1, 0), acc2(2, 0);
  EXPECT_THROW(obj.Transaction::Make(acc1, acc1, 100), std::logic_error);

  EXPECT_THROW(obj.Transaction::Make(acc1, acc2, -100), std::invalid_argument);

  EXPECT_THROW(obj.Transaction::Make(acc1, acc2, 99), std::logic_error);

  obj.Transaction::set_fee(100);
  EXPECT_FALSE(obj.Transaction::Make(acc1, acc2, 100));
  obj.Transaction::set_fee(1);

  EXPECT_CALL(acc1, Lock()).Times(1);
  EXPECT_CALL(acc2, Lock()).Times(1);
  EXPECT_CALL(acc2, ChangeBalance(100)).Times(1);
  EXPECT_CALL(acc1, GetBalance()).Times(1).WillOnce(testing::Return(100));
  EXPECT_CALL(acc2, ChangeBalance(-100)).Times(1);
  EXPECT_CALL(acc1, Unlock()).Times(1);
  EXPECT_CALL(acc2, Unlock()).Times(1);
  EXPECT_FALSE(obj.Transaction::Make(acc1, acc2, 100));

  EXPECT_CALL(acc1, Lock()).Times(1);
  EXPECT_CALL(acc2, Lock()).Times(1);
  EXPECT_CALL(acc2, ChangeBalance(100)).Times(1);
  EXPECT_CALL(acc1, GetBalance()).Times(1).WillOnce(testing::Return(101));
  EXPECT_CALL(acc1, ChangeBalance(-101)).Times(1);
  EXPECT_CALL(obj, SaveToDataBase(testing::_, testing::_, 100)).Times(1);
  EXPECT_CALL(acc1, Unlock()).Times(1);
  EXPECT_CALL(acc2, Unlock()).Times(1);
  EXPECT_TRUE(obj.Transaction::Make(acc1, acc2, 100));
}

TEST(Transaction, SaveToDataBase) {
  MockTransaction obj;
  MockAccount acc1(1, 0), acc2(2, 0);
  EXPECT_CALL(obj, SaveToDataBase(testing::_, testing::_, 100)).Times(1);
  EXPECT_NO_THROW(obj.SaveToDataBase(acc1, acc2, 100));
}
