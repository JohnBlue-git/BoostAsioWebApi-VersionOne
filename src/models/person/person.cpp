#include "person.hpp"

std::string Person::getName() const { return this->name; }

unsigned int Person::getAge() const { return this->age; }

void Person::setName(std::string name) { this->name = name; }

void Person::setAge(unsigned int age) { this->age = age; }
