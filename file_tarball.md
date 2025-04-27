## Advance Person Service API

This project provides a simple API for managing person information, including the ability to create, update, retrieve, and delete person records.

## API Endpoints & curl command
file
```console
# get file
curl -X GET http://localhost:1999/api/file -o data.json -v
```
tarball
```console
# get tarball
curl -X GET http://localhost:1999/api/tarball -o data.tar -v

# post tarball and extarct to tmp folder
curl -X POST http://localhost:1999/api/tarball -H "Content-Type: application/x-tar" --data-binary @data.tar -v

# delete tmp folder (rm -rf ../files/tmp/*)
curl -X DELETE http://localhost:1999/api/tarball -v
```
tarball gzip
```console
# get tarball
curl -X GET http://localhost:1999/api/tarball_gzip -o data.tar.gz -v

# post tarball and extarct to tmp folder
curl -X POST http://localhost:1999/api/tarball_gzip -H "Content-Type: application/x-tar" --data-binary @data.tar.gz -v

# delete tmp folder (rm -rf ../files/tmp/*)
curl -X DELETE http://localhost:1999/api/tarball_gzip -v
```