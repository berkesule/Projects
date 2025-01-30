package berkesule;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;



class HospitalTest {

    @Test
    void testAddSection() {
        Hospital hospital = new Hospital(1, "Meram Tıp");
        Section section = new Section(1, "Kardiyoloji");

        try {
            hospital.addSection(section);
            assertEquals(1, hospital.getSections().size());
            assertEquals("Kardiyoloji", hospital.getSections().get(0).getName());
        } catch (DuplicateInfoException e) {
        	fail("");
        }
    }

    @Test
    void testAddDuplicateSectionThrowsException() {
        Hospital hospital = new Hospital(2, "Meram Devlet");
        Section section1 = new Section(1, "Kardiyoloji");
        Section section2 = new Section(1, "Kardiyoloji");

        try {
            hospital.addSection(section1);
            assertThrows(DuplicateInfoException.class, () -> hospital.addSection(section2));
        } catch (DuplicateInfoException e) {
        	fail("");
        }
    }

    @Test
    
    void testGetSectionById() {
        Hospital hospital = new Hospital(3, "Selcuklu Tıp");
        Section section = new Section(1, "Kardiyoloji");

        try {
            hospital.addSection(section);
            Section s = hospital.getSection(1);
            assertNotNull(s);
            assertEquals("Kardiyoloji", s.getName());
        } catch (DuplicateInfoException e) {
            fail("");
        }
    }
}
