package berkesule;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class PersonTest {

    @Test
    void testPersonConstructorAndGetters() {

        String name = "Test Name";
        long expectedNationalId = 11111111111L;


        Person person = new Person(name, expectedNationalId);


        assertEquals(name, person.getName());
        assertEquals(expectedNationalId, person.getNational_id());
    }

    @Test
    void testToString() {
        String name = "Test Name";
        long expectedNationalId = 11111111111L;
        Person person = new Person(name, expectedNationalId);

        String result = person.toString();

        String expectedString = "Person{name='Test Name', national id=11111111111}";
        assertEquals(expectedString, result);
    }
}
