package berkesule;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class DoctorTest {

    @Test
    void testDoctorConstructor() {
        
        String name = "Test Doctor";
        long nationalId = 11111111111L;
        int diplomaId = 123;
        int maxPatientsPerDay = 10;

      
        Doctor doctor = new Doctor(name, nationalId, diplomaId, maxPatientsPerDay);

        
        assertEquals(name, doctor.getName());
        assertEquals(nationalId, doctor.getNational_id());
        assertEquals(diplomaId, doctor.getDiploma_id());
        assertEquals(maxPatientsPerDay, doctor.getSchedule().getMaxPatientPerDay());
    }

    @Test
    void testDoctorToString() {

        String name = "Doktor ismi";
        long nationalId = 11111111111L;
        int diplomaId = 123;
        int maxPatientsPerDay = 10;
        Doctor doctor = new Doctor(name, nationalId, diplomaId, maxPatientsPerDay);

      
        String toStringResult = doctor.toString();

        
        assertTrue(toStringResult.contains("name='Doktor ismi'"));
        assertTrue(toStringResult.contains("national_id=11111111111"));
        assertTrue(toStringResult.contains("diploma_id=123"));
        assertTrue(toStringResult.contains("max patient per day=10"));
    }
}
