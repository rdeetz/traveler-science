# Traveler Project

Data, tools, and applications for traveling the world.

## Requirements
* PostgreSQL v10
* Elasticsearch v6
* Ruby v2.7
* Python v3.7
* Scala v2.13
* clang v11
* GnuCOBOL v2

## Database
To create the database:
```
pg_ctl -D /usr/local/var/postgres start
psql -d postgres
createuser traveler
ALTER ROLE traveler WITH PASSWORD 'password’;
ALTER ROLE traveler CREATEDB CREATEROLE;
psql -d postgres -U traveler
CREATE DATABASE traveler;
psql -d traveler -U traveler
```
To load the data:
```
psql -d traveler -f ./schema/create-cities.sql
\copy city(country,raw_city,city,region,population,latitude,longitude) from '/path/to/data.csv' delimiter ',' CSV HEADER;
```

## Search Index
To run the search index:
```
elasticsearch
```
To populate the search index:
```
curl -XPOST http://localhost:9200/traveler/cities/_bulk --data-binary @/path/to/data.json -H 'Content-Type: application/json'
```
To query the search index:
```
curl -XGET http://localhost:9200/traveler/cities/_search
curl -XGET http://localhost:9200/traveler/cities/_search?q=raw_city:aixovall
```
