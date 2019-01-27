package mooville.traveler

import scala.concurrent._
import scala.concurrent.ExecutionContext.Implicits.global

import com.softwaremill.sttp._
import com.softwaremill.sttp.akkahttp._
import com.softwaremill.sttp.json4s._

case class City(
    //id: Int,
    country: String,
    rawCity: String,
    city: String,
    region: String,
    population: Option[Int],
    latitude: Double,
    longitude: Double
)

object Traveler extends App {
    println("Are you ready to travel?")

    implicit val serialization = org.json4s.native.Serialization
    val city = Some("1")
    val request = sttp.get(uri"http://localhost:9200/traveler/cities/$city") //.response(asJson[City])
    implicit val backend = HttpURLConnectionBackend()
    val response = request.send()
    
    println(response.headers)
    println(response.body)
}
