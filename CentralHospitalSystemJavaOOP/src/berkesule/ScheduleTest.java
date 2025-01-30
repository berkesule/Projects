package berkesule;

import static org.junit.jupiter.api.Assertions.*;


import java.util.Date;

import org.junit.jupiter.api.Test;

class ScheduleTest {
    private Doctor doctor = new Doctor("Test Doctor", 11111111111L, 123, 1);
    private Patient patient = new Patient("Test Patinet",11111111111L);
    private Patient patient2 = new Patient("Test Patinet2",22222222222L);


    @Test
    void testAddRendezvousTrue() {
    	@SuppressWarnings("deprecation")
		Date desiredDate = new Date(2025 - 1900, 2 - 1, 13);

        boolean result = doctor.getSchedule().addRendezvous(patient, desiredDate);

        assertTrue(result, "Randevu Başarıyla Eklendi"
        		+ "");
    }

    
    @Test
    void testAddRendezvousFalse() {
    	@SuppressWarnings("deprecation")
		Date desiredDate2 = new Date(2025 - 1900, 2 - 1, 14);
  
        doctor.getSchedule().addRendezvous(patient, desiredDate2);

        boolean result = doctor.getSchedule().addRendezvous(patient2, desiredDate2);

        assertFalse(result, "Randevu eklenemedi MaxPatientsPerDay");
    }
}
