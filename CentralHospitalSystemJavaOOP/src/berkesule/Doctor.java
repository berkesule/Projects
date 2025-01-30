package berkesule;
public class Doctor extends Person {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private final int diploma_id;
	private Schedule schedule;
	public Doctor(String name, long national_id, int diploma_id, int maxPatientsPerDay) {
		super(name, national_id);
		this.schedule = new Schedule(maxPatientsPerDay);
		this.schedule.setDoctor(this);
		this.diploma_id = diploma_id;
	}
	
    public int getDiploma_id() {
		return diploma_id;
	}
    @Override
    public String toString() {
        return "Doctor{" +
               "name='" + this.getName() + '\'' +
               ", national_id=" + this.getNational_id() +
               ", diploma_id=" + diploma_id +
               ", max patient per day=" + schedule.getMaxPatientPerDay() +
               '}';
    }
	public Schedule getSchedule() {
		return this.schedule;
		
	}

}
