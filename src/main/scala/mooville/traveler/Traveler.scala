package mooville.traveler

import scala.concurrent._
import scala.concurrent.ExecutionContext.Implicits.global

import com.softwaremill.sttp._
import com.softwaremill.sttp.akkahttp._
import com.softwaremill.sttp.json4s._

case class HttpBinResponse(origin: String, headers: Map[String, String])

object Traveler extends App {
    println("Are you ready to travel?")

    // val city = Some("1")
    // val request = sttp.get(uri"http://localhost:9200/traveler/cities/$city")
    // implicit val backend = HttpURLConnectionBackend()
    // val response = request.send()
    // println(response.body)
    // println(response.headers)

    // implicit val serialization = org.json4s.native.Serialization
    // val request = sttp.get(uri"https://httpbin.org/get").response(asJson[HttpBinResponse])
    // implicit val backend = AkkaHttpBackend()
    // val response: Future[Response[HttpBinResponse]] = request.send()

    // for (r <- response) {
    //     println(r.code)
    //     println(r.body)
    //     backend.close()
    // }
}
