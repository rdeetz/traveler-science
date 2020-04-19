CREATE TABLE airports (
  id          serial not null,
  airport     varchar(128),
  city        varchar(128),
  country     varchar(128),
  iata        varchar(8),
  icao        varchar(8),
  latitude    real,
  longitude   real,
  altitude    real,
  utc_offset  real,
  dst         varchar(8),
  time_zone   varchar(128),
  created_at  timestamp default (now() at time zone 'utc'),
  updated_at  timestamp default (now() at time zone 'utc'),
  CONSTRAINT airports_primary_key  PRIMARY KEY (id)
);
