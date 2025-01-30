package berkesule;

import static org.junit.jupiter.api.Assertions.*;

import java.io.File;
import java.util.Date;

import org.junit.jupiter.api.Test;

class CRSTest {

    @Test
    void testSaveAndLoadTables() {
        CRS crs = new CRS();
        String testPath = "C:\\\\Users\\\\Berke\\\\eclipse-workspace\\\\NYP\\\\src";
        new File(testPath).mkdir();

        Hospital hospital = new Hospital(1, "Test Hospital");
        Section section = new Section(101, "Test Section");
        Doctor doctor = new Doctor("Test Doctor", 11111111111L, 123, 5);
        section.addDoctor(doctor);
        hospital.addSection(section);
        crs.getHospitals().put(hospital.getId(), hospital);

        Patient patient = new Patient("Test Patient", 11111111111L);
        crs.getPatients().put(124L, patient);

        crs.saveTablesToDisk(testPath);

        CRS loadedCrs = new CRS();
        loadedCrs.loadTablesToDisk(testPath);

        assertEquals(1, loadedCrs.getHospitals().size());
        assertEquals(1, loadedCrs.getPatients().size());

        new File(testPath + "/hospital.ser").delete();
        new File(testPath + "/patients.ser").delete();
        new File(testPath + "/rendezvous.ser").delete();
        new File(testPath).delete();
    }

    @Test
    void testMakeRendezvous() {
        CRS crs = new CRS();

        Patient patient = new Patient("Test Patient", 11111111111L);
        crs.getPatients().put(123L, patient);

        Hospital hospital = new Hospital(1, "Test Hospital");
        Section section = new Section(101, "Test Section");
        Doctor doctor =  new Doctor("Test Doctor", 11111111111L, 123, 5);
        section.addDoctor(doctor);
        hospital.addSection(section);
        crs.getHospitals().put(hospital.getId(), hospital);

        Date desiredDate = new Date();
        boolean result = crs.makeRandezvous(123L, 1, 101, 123, desiredDate);

        
        assertTrue(result);
        assertEquals(1, crs.getRendezvous().size());
    }
    @Test
    void testMakeRendezvousWithInvalidIDs() {
        CRS crs = new CRS();

        Exception patientException = assertThrows(IDException.class, () -> {
            crs.makeRandezvous(99999L, 1, 101, 123, new Date());
        });
        assertEquals("Patient with ID 99999 not found.", patientException.getMessage(),
                "patient ID hatası");

        Patient patient = new Patient("Test Patient", 11111111111L);
        crs.getPatients().put(11111111111L, patient);

        Exception hospitalException = assertThrows(IDException.class, () -> {
            crs.makeRandezvous(11111111111L, 999, 101, 123, new Date());
        });
        assertEquals("Hospital with ID 999 not found.", hospitalException.getMessage(),
                "hospital ID hatası");

        Hospital hospital = new Hospital(1, "Test Hospital");
        crs.getHospitals().put(1, hospital);

        Exception sectionException = assertThrows(IDException.class, () -> {
            crs.makeRandezvous(11111111111L, 1, 999, 123, new Date());
        });
        assertEquals("Section with ID 999 not found in hospital 1", sectionException.getMessage(),
                "section ID Hatası");

        Section section = new Section(101, "Test Section");
        hospital.addSection(section);

        Exception doctorException = assertThrows(IDException.class, () -> {
            crs.makeRandezvous(11111111111L, 1, 101, 999, new Date());
        });
        assertEquals("Doctor with diploma ID 999 not found in section 101", doctorException.getMessage(),
                "doctor ID Hatası");
    }

   
}
