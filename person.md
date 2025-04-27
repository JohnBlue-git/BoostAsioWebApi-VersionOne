## Person Service API

This project provides a simple API for managing person information, including the ability to create, update, retrieve, and delete person records.

## API Endpoints & curl command
/api/person
```console
# create person
# POST /api/person
curl -X POST -H "Content-Type: application/json" -d '{"name": "John Doe", "age": 30}' http://localhost:1999/api/person -v

# patch person
# PATCH /api/person/{id}
curl -X PATCH -H "Content-Type: application/json" -d '{"name": "John Blue", "age": 18}' http://localhost:1999/api/person/0 -v

# get all
# GET /api/person
curl -X PATCH -H "Content-Type: application/json" -d '{"name": "John Blue", "age": 18}' http://localhost:1999/api/person -v

# get specific {id}
# GET /api/person/{id}
curl -X GET -H "Content-Type: application/json" http://localhost:1999/api/person/0 -v

# delete specific {id}
# DELETE /api/person/{id}
curl -X DELETE -H "Content-Type: application/json" http://localhost:1999/api/person/0 -v

# delete all
# DELETE /api/person
curl -X DELETE -H "Content-Type: application/json" http://localhost:1999/api/person -v
```
/api/advance_person
```console
# create person
# POST /api/advance_person
curl -X POST -H "Content-Type: application/json" -d '{"name": "John Doe", "age": 30}' http://localhost:1999/api/advance_person -v

# patch person
# PATCH /api/advance_person/{id}
curl -X PATCH -H "Content-Type: application/json" -d '{"name": "John Blue", "age": 18}' http://localhost:1999/api/advance_person/0 -v

# get all
# GET /api/advance_person
curl -X PATCH -H "Content-Type: application/json" -d '{"name": "John Blue", "age": 18}' http://localhost:1999/api/advance_person -v

# get specific {id}
# GET /api/advance_person/{id}
curl -X GET -H "Content-Type: application/json" http://localhost:1999/api/advance_person/0 -v

# delete specific {id}
# DELETE /api/advance_person/{id}
curl -X DELETE -H "Content-Type: application/json" http://localhost:1999/api/advance_person/0 -v

# delete all
# DELETE /api/advance_person
curl -X DELETE -H "Content-Type: application/json" http://localhost:1999/api/advance_person -v
```