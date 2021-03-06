#include <string>

class User {
  std::string name;
  int age;

public:
  User(const std::string &n, int a) : name(n), age(a) {}

  std::string GetName() const { return name; }
  int GetAge() const { return age; }
};

struct IDatabase {
  virtual ~IDatabase() {}

  virtual void SaveUser(const std::string &name, User *user) = 0;
  virtual User *LoadUser(const std::string &name) = 0;
};

class UserManager {
  IDatabase *database;

public:
  UserManager(IDatabase *p) : database(p) {}

  void Save(User *p) { database->SaveUser(p->GetName(), p); }

  User *Load(const std::string &name) {
    // return database->LoadUser(name);
    return nullptr;
  }

  bool IsExist(const std::string &name) { return Load(name) != nullptr; }
};

// 문제: 아직 데이터베이스의 구현이 제공되지 않습니다.
// Fake Object Pattern
//  의도: 아직 준비되지 않은 협력 객체로 인해서, 테스트되지 않은 요구사항이
//  존재합니다. 방법: 동일한 기능을 수행하는 가벼운 테스트 대역을 만들어서
//  테스트를 수행합니다.
//    1) 의존 객체가 존재하지 않을 때
//    2) 의존 객체가 너무 느려서 느린 테스트의 문제가 발생할 때
//    3) 의존 객체를 사용하기 어려울 때
//
// 문제점: 실제 객체의 동작과 거리가 있다면, 테스트 결과의 신뢰성에 문제가
// 발생합니다.
#include <gtest/gtest.h>
#include <map>

class FakeDatabase : public IDatabase {
  std::map<std::string, User *> data;

public:
  void SaveUser(const std::string &name, User *user) override {
    data[name] = user;
  }

  User *LoadUser(const std::string &name) override { return data[name]; }
};

bool operator==(const User &lhs, const User &rhs) {
  return lhs.GetName() == rhs.GetName() && lhs.GetAge() && rhs.GetAge();
}

std::ostream &operator<<(std::ostream &os, const User &user) {
  return os << "User{name=" << user.GetName() << ", age=" << user.GetAge()
            << "}";
}

TEST(UserManagerTest, SaveLoadTest) {
  FakeDatabase fake;
  UserManager manager(&fake);
  std::string testName = "test_name";
  int testAge = 42;
  User expected(testName, testAge);
  User expected2("Tom", 42);

  manager.Save(&expected);
  User *actual = manager.Load(testName);

  ASSERT_NE(actual, nullptr);
  EXPECT_EQ(*actual, expected);
  // 사용자 정의 클래스를 대상으로 단언문을 사용하기 위해서는
  // 연산자 재정의가 필요합니다.
  //  : EQ(==) / NE(!=) / LT(<) / GT(>) / LE(<=) / GE(>=)

  EXPECT_EQ(*actual, expected2);
}

//--------------------

#include <gmock/gmock.h>

// virtual void SaveUser(const std::string &name, User *user) = 0;
// virtual User *LoadUser(const std::string &name) = 0;

class MockDatabase : public IDatabase {
public:
  MOCK_METHOD(void, SaveUser, (const std::string &name, User *user),
              (override));
  MOCK_METHOD(User *, LoadUser, (const std::string &name), (override));
};

using testing::NiceMock;

TEST(UserManagerTest2, SaveLoadTest) {
  NiceMock<MockDatabase> fake;
  UserManager manager(&fake);

  std::map<std::string, User *> data;
  ON_CALL(fake, SaveUser)
      .WillByDefault(
          [&data](const std::string &name, User *user) { data[name] = user; });
  ON_CALL(fake, LoadUser).WillByDefault([&data](const std::string &name) {
    return data[name];
  });
  std::string testName = "test_name";
  int testAge = 42;
  User expected(testName, testAge);

  manager.Save(&expected);
  User *actual = manager.Load(testName);

  ASSERT_NE(actual, nullptr);
  EXPECT_EQ(*actual, expected);
}

static std::map<std::string, User *> data;
void SaveUserImpl(const std::string &name, User *user) { data[name] = user; }
User *LoadUserImpl(const std::string &name) { return data[name]; }

TEST(UserManagerTest2, SaveLoadTest2) {
  NiceMock<MockDatabase> fake;
  UserManager manager(&fake);
  ON_CALL(fake, SaveUser).WillByDefault(&SaveUserImpl);
  ON_CALL(fake, LoadUser).WillByDefault(&LoadUserImpl);
  std::string testName = "test_name";
  int testAge = 42;
  User expected(testName, testAge);

  manager.Save(&expected);
  User *actual = manager.Load(testName);

  ASSERT_NE(actual, nullptr);
  EXPECT_EQ(*actual, expected);
}

TEST(UserManagerTest2, SaveLoadTest3) {
  NiceMock<MockDatabase> mock;
  UserManager manager(&mock);
  std::string testName = "test_name";
  int testAge = 42;
  User expected(testName, testAge);

  EXPECT_CALL(mock, SaveUser).WillOnce(&SaveUserImpl);
  EXPECT_CALL(mock, LoadUser).WillOnce(&LoadUserImpl);
  manager.Save(&expected);
  User *actual = manager.Load(testName);

  ASSERT_NE(actual, nullptr);
  EXPECT_EQ(*actual, expected);
}