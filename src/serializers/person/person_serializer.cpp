#include "person_serializer.hpp"

#ifdef BOOST_JSON

boost::json::object PersonSerializer::toJson(const Person& person) {
  boost::json::object obj;
  obj["name"] = person.getName();
  obj["age"] = person.getAge();
  return obj;
}

std::vector<Person> PersonSerializer::fromJson(const boost::json::object& obj) {
  if (!obj.if_contains("name") || !obj.if_contains("age"))
  {
    return std::nullopt;
  }
  std::string name = obj.at("name").as_string().c_str();
  unsigned int age = obj.at("age").as_int64();
  Person person(name, age);
  return person;
}

#else

nlohmann::json PersonSerializer::toJson(const Person& person) {
  nlohmann::json obj;
  obj["name"] = person.getName();
  obj["age"] = person.getAge();
  return obj;
}

std::optional<Person> PersonSerializer::fromJson(const nlohmann::json& obj) {
  if (!obj.contains("name") || !obj.contains("age"))
  {
    return std::nullopt;
  }
  std::string name = obj["name"];
  unsigned int age = obj["age"];
  Person person(name, age);
  return person;
}

#endif