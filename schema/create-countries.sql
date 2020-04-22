CREATE TABLE countries (
  id          serial not null,
  country     varchar(128),
  code        varchar(8),
  created_at  timestamp default (now() at time zone 'utc'),
  updated_at  timestamp default (now() at time zone 'utc'),
  CONSTRAINT countries_primary_key  PRIMARY KEY (id)
);
