## Person Service API

This project provides a simple API for managing person information, including the ability to create, update, retrieve, and delete person records.

## API Endpoints & curl command
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

