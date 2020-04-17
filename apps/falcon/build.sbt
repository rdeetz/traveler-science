ThisBuild / organization := "mooville"

lazy val traveler = (project in file(".")).settings(
    name := "Traveler",
    libraryDependencies ++= List(
        "com.typesafe.akka" %% "akka-stream" % "2.5.19",
        "com.typesafe.slick" %% "slick" % "3.2.3",
        "com.softwaremill.sttp" %% "core" % "1.5.8",
        "com.softwaremill.sttp" %% "akka-http-backend" % "1.5.8",
        "com.softwaremill.sttp" %% "json4s" % "1.5.8",
        "org.json4s" %% "json4s-native" % "3.6.3",
        "org.scalatest" %% "scalatest" % "3.0.5" % Test
    )
)
