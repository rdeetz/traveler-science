ThisBuild / organization := "mooville"

lazy val traveler = (project in file(".")).settings(
    name := "Traveler",
    libraryDependencies += "org.scalatest" %% "scalatest" % "3.0.5" % Test
)
