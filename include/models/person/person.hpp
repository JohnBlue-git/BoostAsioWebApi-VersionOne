#pragma once

#include <boost/asio.hpp>
#include <string>

class Person {
private:
  std::string name;
  unsigned int age;

public:
  Person() = default;
  Person(const Person& copy) = default;
  ~Person() {};
  Person& operator=(const Person& assign) = default;
  Person(Person&& other) = default;
  Person& operator=(Person&& other) = default;
public:
  Person(std::string name, unsigned int age):
    name(name),
    age(age)
    {};

public:
  std::string getName() const;
  unsigned int getAge() const;
  void setName(std::string);
  void setAge(unsigned int);
};
