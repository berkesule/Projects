package berkesule;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import java.util.Date;

class RendezvousTest {

    @Test
    void testConstructor() {
    	Patient patient = new Patient("Test Patinet",11111111111L);
        Doctor doctor = new Doctor("Test Doctor", 11111111111L, 123, 5);
        Date dateTime = new Date();

        Rendezvous rendezvous = new Rendezvous(patient, dateTime, doctor);

        assertNotNull(rendezvous);
        assertEquals(patient, rendezvous.getPatient());
        assertEquals(dateTime, rendezvous.getDateTime());
        assertEquals(doctor, rendezvous.getDoctor());
    }

    @Test
    void testGetterSetter() {
        Patient patient = new Patient("Test Patient",11111111111L);
        Doctor doctor = new Doctor("Test Doctor", 11111111111L, 123, 5); 
        Date dateTime = new Date();

        Rendezvous rendezvous = new Rendezvous(patient, dateTime, doctor);

        assertEquals(patient, rendezvous.getPatient());
        assertEquals(dateTime, rendezvous.getDateTime());
        assertEquals(doctor, rendezvous.getDoctor());
        
        
        Doctor newDoctor = new Doctor("Test Doctor new", 11111111112L, 124, 5); 
        

        rendezvous.setDoctor(newDoctor);
        

   
        assertEquals(newDoctor, rendezvous.getDoctor());


    }
}
