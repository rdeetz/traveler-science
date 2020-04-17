from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, Float, Date
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base

DATABASE_URI = 'postgres+psycopg2://traveler:traveler@localhost:5432/traveler'

Base = declarative_base()

class City(Base):
    __tablename__ = 'cities'
    id = Column(Integer, primary_key=True)
    country = Column(String)
    raw_city = Column(String)
    city = Column(String)
    region = Column(String)
    population = Column(Float)
    latitude = Column(Float)
    longitude = Column(Float)
    created_at = Column(Date)
    updated_at = Column(Date)

    def __repr__(self):
        return "{} in {} at {} lat, {} long".format(self.city, self.country, self.latitude, self.longitude)

    def print_all(self):
        print(self.id)
        print(self.country)
        print(self.raw_city)
        print(self.city)
        print(self.region)
        print(self.population)
        print(self.latitude)
        print(self.longitude)
        print(self.created_at)
        print(self.updated_at)

engine = create_engine(DATABASE_URI)
Session = sessionmaker(bind=engine)

s = Session()

c = s.query(City).first()
print(c)
c.print_all()

s.close()
