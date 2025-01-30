package berkesule;
import java.io.Serializable;
import java.util.LinkedList;

public class Section  implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private final int id;
	private String name;
	private LinkedList<Doctor> doctors;
	public Section(int id, String name) {
		this.doctors = new LinkedList<Doctor>();
		this.id = id;
		this.name = name;
	}
	
	public LinkedList<Doctor> getDoctors() {
		return doctors;
	}



	public int getId() {
		return id;
	}

	public void listDoctors() {
		if (doctors.isEmpty()) {
		    System.out.println("No doctors in this section.");
		}
		for(Doctor doctor : doctors) {
			System.out.println(doctor.toString());
		}
	}
	public Doctor getDoctor(int diploma_id) {
		for(Doctor doctor : doctors) {
			if(doctor.getDiploma_id() == diploma_id) {
				return doctor;
			}
		}
		return null;
	}

	public String getName() {
		return name;
	}


	public void addDoctor(Doctor doctor) throws DuplicateInfoException {
	    for (Doctor d : doctors) {
	        if (d.getDiploma_id() == doctor.getDiploma_id()) {
	            throw new DuplicateInfoException("Doctor with diploma ID " + doctor.getDiploma_id() + " already exists.");
	        }
	        if (d.getNational_id() == doctor.getNational_id()) {
	            throw new DuplicateInfoException("Doctor with diploma ID " + doctor.getNational_id() + " already exists.");
	        }
	    }
	    doctors.add(doctor);
	}

}
