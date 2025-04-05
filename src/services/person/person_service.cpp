#include "person_service.hpp"

std::vector<Person> PersonService::getPersons()
{
  return this->persons;
}

std::optional<Person> PersonService::getPersonById(unsigned int id)
{
  if (id + 1 > this->persons.size())
  {
    return std::nullopt;
  }
  return this->persons[id];
}

void PersonService::addPerson(const Person& person)
{
  this->persons.push_back(person);
}

//bool PersonService::putPerson(const Person &person, ...)

bool PersonService::patchPerson(unsigned int id,
                              std::optional<std::string> name,
                              std::optional<unsigned int> age)
{
  if (id + 1 > this->persons.size())
  {
    return false;
  }
  auto& person = this->persons[id];
  if (name)
  {
    person.setName(name.value());
  }
  if (age)
  {
    person.setAge(age.value());
  }
  return true;
}

void PersonService::deletePersons()
{
  this->persons.clear();
}

bool PersonService::deletePersonById(unsigned int id)
{
  if (id + 1 > this->persons.size())
  {
    return false;
  }
  this->persons.erase(persons.begin() + id);
  return true;
}