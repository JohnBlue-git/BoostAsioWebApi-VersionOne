#pragma once

#include <vector>

#include "../models/person.hpp"

class IPersonService {
public:
  virtual std::vector<Person> getPersons() = 0;
  virtual std::optional<Person> getPersonById(unsigned int id) = 0;
  virtual void addPerson(const Person &person) = 0;
  //virtual bool putPerson(unsigned int id, ...) = 0;
  virtual bool patchPerson(unsigned int id, std::optional<std::string> name, std::optional<unsigned int> age) = 0;
  virtual bool deletePersons() = 0;
  virtual bool deletePersonById(unsigned int id) = 0;
};

class PersonService : public IPersonService {
private:
  std::vector<Person> persons;

public:
  std::vector<Person> getPersons() override;
  std::optional<Person> getPersonById(unsigned int id) override;
  void addPerson(const Person& person) override;
  //bool putPerson(unsigned int id, ...) override;
  bool patchPerson(unsigned int id, std::optional<std::string> name, std::optional<unsigned int> age) override;
  bool deletePersons() override;
  bool deletePersonById(unsigned int id) override;
};