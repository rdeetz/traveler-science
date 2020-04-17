c = City.find(21)
h = {index: {_id: c.id}}
k = h.to_json
j = c.to_json(only: [:country, :raw_city, :city, :region, :population, :latitude, :longitude])

es.post do |req|
  req.url s
  req.headers['Content-Type'] = 'application/json'
  req.body = j
end

def post_bulk(cy)
  es = Faraday.new(:url => 'http://localhost:9200')
  es.post do |req|
    req.url "/traveler/cities/_bulk"
    req.headers['Content-Type'] = 'application/json'
    iy = {index: {_id: cy.id}}
    iyj = iy.to_json
    dyj = cy.to_json(only: [:country, :raw_city, :city, :region, :population, :latitude, :longitude])
    pbyj = iyj + "\n" + dyj + "\n"
    req.body = pbyj
  end
end

def post_bulks(cs)
  es = Faraday.new(:url => 'http://localhost:9200')
  es.post do |req|
    req.url "/traveler/cities/_bulk"
    req.headers['Content-Type'] = 'application/json'
    pbyj = ""
    for t in cs
      iy = {index: {_id: t.id}}
      iyj = iy.to_json
      dyj = t.to_json(only: [:country, :raw_city, :city, :region, :population, :latitude, :longitude])
      pbyj = pbyj + iyj + "\n" + dyj + "\n"
    end
    req.body = pbyj
  end
end

find in batches of 5000
build a post body for that 5000
fire it off
continue doing this for each batch until all records gone

def post_all_the_batches()
  es = Faraday.new(:url => 'http://localhost:9200')
  City.find_in_batches(batch_size: 10000) do | batch_of_cities |
    es.post do |req|
      req.url "/traveler/cities/_bulk"
      req.headers['Content-Type'] = 'application/json'
      pbyj = ""
      for t in batch_of_cities
        iy = {index: {_id: t.id}}
        iyj = iy.to_json
        dyj = t.to_json(only: [:country, :raw_city, :city, :region, :population, :latitude, :longitude])
        pbyj = pbyj + iyj + "\n" + dyj + "\n"
      end
      req.body = pbyj
    end
  end
end

{ "delete" : { "_index" : "traveler", "_type" : "cities", "_id" : "2" } }

def delete_all_the_batches()
  es = Faraday.new(:url => 'http://localhost:9200')
  City.find_in_batches(batch_size: 10000) do | batch_of_cities |
    es.post do |req|
      req.url "/traveler/cities/_bulk"
      req.headers['Content-Type'] = 'application/json'
      pbyj = ""
      for t in batch_of_cities
        iy = {delete: {_index: "traveler", _type: "cities", _id: t.id }}
        iyj = iy.to_json
        pbyj = pbyj + iyj + "\n"
      end
      req.body = pbyj
    end
  end
end


