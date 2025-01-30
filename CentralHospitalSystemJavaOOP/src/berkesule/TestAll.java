package berkesule;

import org.junit.platform.suite.api.SelectClasses;
import org.junit.platform.suite.api.Suite;

@Suite
@SelectClasses({CRSTest.class,HospitalTest.class,PersonTest.class,RendezvousTest.class,ScheduleTest.class,SectionTest.class,PatientTest.class, DoctorTest.class})
public class TestAll {

}
