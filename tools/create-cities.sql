CREATE TABLE cities (
  id          serial not null,
  country     varchar(8),
  raw_city    varchar(128),
  city        varchar(128),
  region      varchar(8),
  population  real,
  latitude    real,
  longitude   real,
  created_at  timestamp default (now() at time zone 'utc'),
  updated_at  timestamp default (now() at time zone 'utc'),
  CONSTRAINT cities_primary_key  PRIMARY KEY (id)
);
