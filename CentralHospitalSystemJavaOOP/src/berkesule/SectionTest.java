package berkesule;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class SectionTest {
    private Section section;
    private Doctor doctor1;
    private Doctor doctor2;

    @BeforeEach
    void setUp() {
        section = new Section(1, "Kardiyoloji");
        doctor1 = new Doctor("Test Doctor", 11111111111L, 123, 5);
        doctor2 = new Doctor("Test Doctor2", 11111111122L, 321, 4);
    }

    @Test
    void testAddDoctor() {
        try {
            section.addDoctor(doctor1);
            assertEquals(1, section.getDoctors().size(), "1 Doktor olmalı");
        } catch (DuplicateInfoException e) {
            fail("");
        }

        //diploma_id exception 123
        try {
            section.addDoctor(new Doctor("Test Doctor", 11111111112L, 123, 5));

        } catch (DuplicateInfoException e) {
            assertTrue(e.getMessage().contains("already exists"));
        }

        //national_id exception 11111111111L
        try {
            section.addDoctor(new Doctor("Test Doctor", 11111111111L, 124, 5));
        } catch (DuplicateInfoException e) {
            assertTrue(e.getMessage().contains("already exists"));
        }
    }

    @Test
    void testGetDoctor() {
        section.addDoctor(doctor1);
        section.addDoctor(doctor2);

        Doctor foundDoctor = section.getDoctor(123);
        assertNotNull(foundDoctor);
        assertEquals("Test Doctor", foundDoctor.getName());

        Doctor nonExistentDoctor = section.getDoctor(999999);
        assertNull(nonExistentDoctor);
    }
}
