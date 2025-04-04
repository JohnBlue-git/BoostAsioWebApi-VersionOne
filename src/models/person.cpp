#include "person.hpp"

unsigned int Person::num_instances = 0;

Person::Person(std::string name, unsigned int age) {
  this->name = name;
  this->age = age;
  this->id = num_instances;
  this->num_instances++;
}

unsigned int Person::getId() const { return this->id; }

std::string Person::getName() const { return this->name; }

unsigned int Person::getAge() const { return this->age; }

void setName(std::string name) { this->name = name; }

void setAge(unsigned int age) { this->age = age; }
