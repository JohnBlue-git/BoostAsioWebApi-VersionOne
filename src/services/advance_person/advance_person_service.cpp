#include "advance_person_service.hpp"

std::vector<Person> AdvancePersonService::getPersons()
{
  std::vector<Person> ret;
  for(auto kv : this->persons) {
    ret.push_back(kv.second);  
  }
  return ret;
}

std::optional<Person> AdvancePersonService::getPersonById(unsigned int id)
{
  if (!this->persons.contains(id))
  {
    return std::nullopt;
  }
  return this->persons[id];
}

void AdvancePersonService::addPerson(const Person& person)
{
  this->persons[this->num_instances++] = person;
}

//bool AdvancePersonService::putPerson(unsigned int id, ...)

bool AdvancePersonService::patchPerson(unsigned int id,
                              std::optional<std::string> name,
                              std::optional<unsigned int> age)
{
  if (!this->persons.contains(id))
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

void AdvancePersonService::deletePersons()
{
  this->persons.clear();
}

bool AdvancePersonService::deletePersonById(unsigned int id)
{
  if (!this->persons.contains(id))
  {
    return false;
  }
  this->persons.erase(id);
  return true;
}