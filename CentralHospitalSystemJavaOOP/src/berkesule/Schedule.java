package berkesule;

import java.io.Serializable;
import java.util.Calendar;
import java.util.Date;
import java.util.LinkedList;

public class Schedule implements Serializable {
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private LinkedList<Rendezvous> sessions;
    private int maxPatientPerDay;
    private Doctor doctor;

    public Schedule(int maxPatientPerDay) {
        this.maxPatientPerDay = maxPatientPerDay;
        this.sessions = new LinkedList<Rendezvous>();
    }
    
    public Doctor getDoctor() {
		return doctor;
	}

	public void setDoctor(Doctor doctor) {
		this.doctor = doctor;
	}

	public int getMaxPatientPerDay() {
		return maxPatientPerDay;
	}



	public synchronized boolean addRendezvous(Patient patient, Date desiredDate) {
        int count = 0;
        Calendar desiredCalendar = Calendar.getInstance();
        desiredCalendar.setTime(desiredDate);

        for (Rendezvous rendezvous : sessions) {
            Calendar sessionCalendar = Calendar.getInstance();
            sessionCalendar.setTime(rendezvous.getDateTime());

            if (desiredCalendar.get(Calendar.YEAR) == sessionCalendar.get(Calendar.YEAR) &&
                desiredCalendar.get(Calendar.DAY_OF_YEAR) == sessionCalendar.get(Calendar.DAY_OF_YEAR)) {
                count++;
            }
        }
        if (count < maxPatientPerDay) {
            sessions.add(new Rendezvous(patient, desiredDate,this.doctor));
            return true;
        } else {
            return false;
        }



        
    }
	
    public void listRendezvous() {
    	for (Rendezvous rendezvous : sessions) {
    		System.out.println(rendezvous.toString());
    	}
    }

}
