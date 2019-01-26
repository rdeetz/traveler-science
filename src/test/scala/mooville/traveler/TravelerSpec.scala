import org.scalatest._

class TravelerSpec extends FunSuite with DiagrammedAssertions {
    test("Traveler should start with T") {
        assert("traveler".startsWith("t"))
    }
}
