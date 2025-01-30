package berkesule;
import java.io.Serializable;
import java.util.Date;

public class Rendezvous  implements Serializable{
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Date dateTime;
    private Patient patient;
    private Doctor doctor;


    public Rendezvous(Patient patient, Date dateTime,Doctor doctor) {
        this.patient = patient;
        this.dateTime = dateTime;
        this.doctor = doctor;

    }



	public Doctor getDoctor() {
		return doctor;
	}



	public void setDoctor(Doctor doctor) {
		this.doctor = doctor;
	}



	public Date getDateTime() {
        return dateTime;
    }

    public Patient getPatient() {
        return patient;
    }
    @Override
    public String toString() {
        return "Rendezvous Patient: " + patient.toString() +"Rendezvous Doctor: "+ doctor.toString() +", DateTime: " + dateTime.toString() + "]";
    }

}
