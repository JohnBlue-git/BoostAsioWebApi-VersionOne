#include "person_service.hpp"

std::vector<Person> PersonService::getPersons() {
  return persons;
}

std::optional<Person> PersonService::getPersonById(unsigned int id) {
  for (auto& person : persons)
  {
    if (person.getId() == id)
    {
      return person;
    }
  }
  return std::nullopt;
}

void PersonService::addPerson(const Person &person) {
  persons.push_back(person);
}

//bool PersonService::putPerson(const Person &person, ...)

bool PersonService::patchPerson(unsigned int id,
                              std::optional<std::string> name,
                              std::optional<unsigned int> age)
{
  for (auto& person : persons)
  {
    if (person.getId() == id)
    {
      if (name)
      {
        person.setName(name);
      }
      if (age)
      {
        person.setAge(age);
      }
      return true;
    }
  }
  return false;
}

void PersonService::deletePersons() {
  persons.clear();
}

bool PersonService::deletePersonById(unsigned int id) {
  for (auto it = persons.begin(); it != persons.end();) {
    if (it->getId() == id) {
      it = persons.erase(it);
      return true;
    } else {
      ++it;
    }
  }
  return false;
}