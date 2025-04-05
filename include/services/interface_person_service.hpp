#pragma once

#include <vector>

#include "../../models/person/person.hpp"

class IPersonService {
public:
  virtual std::vector<Person> getPersons() = 0;
  virtual std::optional<Person> getPersonById(unsigned int id) = 0;
  virtual void addPerson(const Person &person) = 0;
  //virtual bool putPerson(unsigned int id, ...) = 0;
  virtual bool patchPerson(unsigned int id, std::optional<std::string> name, std::optional<unsigned int> age) = 0;
  virtual void deletePersons() = 0;
  virtual bool deletePersonById(unsigned int id) = 0;
};