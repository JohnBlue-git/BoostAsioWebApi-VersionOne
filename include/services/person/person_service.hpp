#pragma once

#include <vector>

#include "../../models/person/person.hpp"
#include "../interface_person_service.hpp"

class PersonService : public IPersonService {
private:
  std::vector<Person> persons;

public:
  std::vector<Person> getPersons() override;
  std::optional<Person> getPersonById(unsigned int id) override;
  void addPerson(const Person& person) override;
  //bool putPerson(unsigned int id, ...) override;
  bool patchPerson(unsigned int id, std::optional<std::string> name, std::optional<unsigned int> age) override;
  void deletePersons() override;
  bool deletePersonById(unsigned int id) override;
};