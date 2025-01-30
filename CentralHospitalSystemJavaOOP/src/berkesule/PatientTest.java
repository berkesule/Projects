package berkesule;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class PatientTest {

    @Test
    void testPatientConstructorAndGetters() {
        String name = "Test Patient";
        long expectedNationalId = 11111111111L;

        Patient patient = new Patient(name, expectedNationalId);

        assertEquals(name, patient.getName());
        assertEquals(expectedNationalId, patient.getNational_id());
    }

    @Test
    void testToString() {
        String name = "Test Patient";
        long expectedNationalId = 11111111111L;
        Patient patient = new Patient(name, expectedNationalId);

        String result = patient.toString();

        String expectedString = "Person{name='Test Patient', national id=11111111111}";
        assertEquals(expectedString, result);
    }
}
