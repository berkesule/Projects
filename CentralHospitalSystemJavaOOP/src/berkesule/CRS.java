package berkesule;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;

public class CRS{
    private HashMap<Long, Patient> patients; 
    private LinkedList<Rendezvous> rendezvous;
    private HashMap<Integer, Hospital> hospitals; 

    public CRS() {
        patients = new HashMap<>();
        rendezvous = new LinkedList<>();
        hospitals = new HashMap<>();
        
    }
    public synchronized boolean makeRandezvous(long patientID, int hospitalID, int sectionID , int diplomaID , Date desiredDate) {
    	
    	Patient patient = patients.get(patientID);
    	if (patient == null) throw new IDException("Patient with ID " + patientID + " not found.");
        Hospital hospital = hospitals.get(hospitalID);
        if (hospital == null) throw new IDException("Hospital with ID " + hospitalID + " not found.");

        Section section = hospital.getSection(sectionID);
        if (section == null) throw new IDException("Section with ID " + sectionID + " not found in hospital " + hospitalID);

        Doctor doctor = section.getDoctor(diplomaID);
        if (doctor == null) throw new IDException("Doctor with diploma ID " + diplomaID + " not found in section " + sectionID);

        Schedule schedule = doctor.getSchedule();
        if (schedule.addRendezvous(patient, desiredDate)) {
            Rendezvous r = new Rendezvous(patient, desiredDate,doctor);
            rendezvous.add(r);
            return true;
        }else {
        	return false;
		}
		

    	
    }
    
    public void saveTablesToDisk(String fullPath) {
        File hospitalFile = new File(fullPath + "hospital.ser");
        File patientsFile = new File(fullPath + "patients.ser");
        File rendezvousFile = new File(fullPath + "rendezvous.ser");

        try (ObjectOutputStream hospitalOos = new ObjectOutputStream(new FileOutputStream(hospitalFile))) {
            hospitalOos.writeObject(hospitals);  
            System.out.println("Hospitals saved successfully.");
        } catch (IOException e) {
            System.err.println("Error saving hospitals: " + e.getMessage());
        }

        try (ObjectOutputStream patientsOos = new ObjectOutputStream(new FileOutputStream(patientsFile))) {
            patientsOos.writeObject(patients);  
            System.out.println("Patients saved successfully.");
        } catch (IOException e) {
            System.err.println("Error saving patients: " + e.getMessage());
        }

        try (ObjectOutputStream rendezvousOos = new ObjectOutputStream(new FileOutputStream(rendezvousFile))) {
            rendezvousOos.writeObject(rendezvous);  
            System.out.println("Rendezvous saved successfully.");
        } catch (IOException e) {
            System.err.println("Error saving rendezvous: " + e.getMessage());
        }
    }


 
    public HashMap<Long, Patient> getPatients() {
		return patients;
	}
	public void setPatients(HashMap<Long, Patient> patients) {
		this.patients = patients;
	}
	public LinkedList<Rendezvous> getRendezvous() {
		return rendezvous;
	}
	public void setRendezvous(LinkedList<Rendezvous> rendezvous) {
		this.rendezvous = rendezvous;
	}
	public HashMap<Integer, Hospital> getHospitals() {
		return hospitals;
	}
	public void setHospitals(HashMap<Integer, Hospital> hospitals) {
		this.hospitals = hospitals;
	}
	public void printData() {
	    System.out.println("Hospitals: ");
	    for (Hospital hospital : hospitals.values()) {
	        System.out.println("  " + hospital.getName());
	        System.out.println("  " + hospital.getId());
	        System.out.println("    Sections: ");
	        for (Section section : hospital.getSections()) {
	            System.out.println("      " + section.getName());
	            System.out.println("      " + section.getId());
	            System.out.println("        Doctors: ");
	            for (Doctor doctor : section.getDoctors()) {
	                System.out.println("          " + doctor.toString());
	                System.out.println("Randevular:");
	                doctor.getSchedule().listRendezvous();
	            }
	        }
	    }

	    System.out.println("Patients: ");
	    for (Long patientID : patients.keySet()) {
	        Patient patient = patients.get(patientID);
	        System.out.println("  Patient ID: " + patientID + ", Details: " + patient); 
	    }

	    System.out.println("Rendezvous: ");
	    for (Rendezvous rendezvous : rendezvous) {
	        System.out.println("  " + rendezvous);  
	    }
	}


	@SuppressWarnings("unchecked")
	public void loadTablesToDisk(String fullPath) {
        File hospitalFile = new File(fullPath + "hospital.ser");
        File patientsFile = new File(fullPath + "patients.ser");
        File rendezvousFile = new File(fullPath + "rendezvous.ser");

        if (hospitalFile.exists()) {
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(hospitalFile))) {
                hospitals = (HashMap<Integer, Hospital>) ois.readObject(); 
                System.out.println("Hospitals loaded successfully.");
            } catch (IOException | ClassNotFoundException e) {
                System.err.println("Error loading hospitals: " + e.getMessage());
            }
        } else {
            try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(hospitalFile))) {
                oos.writeObject(new HashMap<Long, Hospital>());
                System.out.println("Hospital file not found. New file created.");
            } catch (IOException e) {
                System.err.println("Error creating hospital file: " + e.getMessage());
            }
        }


        if (patientsFile.exists()) {
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(patientsFile))) {
                HashMap<Long, Patient> patientsMap = (HashMap<Long, Patient>) ois.readObject();
                for (Long patientID : patientsMap.keySet()) {
                    patients.put(patientID, patientsMap.get(patientID));
                }
                System.out.println("Patients loaded successfully.");
            } catch (IOException | ClassNotFoundException e) {
                System.err.println("Error loading patients: " + e.getMessage());
            }
        } else {
            try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(patientsFile))) {
                oos.writeObject(new HashMap<Long, Patient>());
                System.out.println("Patients file not found. New file created.");
            } catch (IOException e) {
                System.err.println("Error creating patients file: " + e.getMessage());
            }
        }

        // Load rendezvous
        if (rendezvousFile.exists()) {
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(rendezvousFile))) {
                LinkedList<Rendezvous> rendezvousList = (LinkedList<Rendezvous>) ois.readObject();
                for (Rendezvous r : rendezvousList) {
                    rendezvous.add(r);
                }
                System.out.println("Rendezvous loaded successfully.");
            } catch (IOException | ClassNotFoundException e) {
                System.err.println("Error loading rendezvous: " + e.getMessage());
            }
        } else {
            try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(rendezvousFile))) {
                oos.writeObject(new LinkedList<Rendezvous>());
                System.out.println("Rendezvous file not found. New file created.");
            } catch (IOException e) {
                System.err.println("Error creating rendezvous file: " + e.getMessage());
            }
        }
    }
	public String getAllData() {
	    StringBuilder dataBuilder = new StringBuilder();
	    dataBuilder.append("Hastaneler:\n");
	    for (Hospital hospital : hospitals.values()) {
	        dataBuilder.append("  ID: ").append(hospital.getId())
	                   .append(", Adı: ").append(hospital.getName()).append("\n");

	        dataBuilder.append("    Bölümler:\n");
	        for (Section section : hospital.getSections()) {
	            dataBuilder.append("      ID: ").append(section.getId())
	                       .append(", Adı: ").append(section.getName()).append("\n");

	            dataBuilder.append("        Doktorlar:\n");
	            for (Doctor doctor : section.getDoctors()) {
	                dataBuilder.append("          Diploma ID: ").append(doctor.getDiploma_id())
	                           .append(", Adı: ").append(doctor.getName()).append("\n");
	            }
	        }
	    }
	    dataBuilder.append("\nHastalar:\n");
	    for (Long patientID : patients.keySet()) {
	        Patient patient = patients.get(patientID);
	        dataBuilder.append("  ID: ").append(patientID)
	                   .append(", Adı: ").append(patient.getName())
	                   .append(", TC kimlik no: ").append(patient.getNational_id());
	                   
	    }

	    dataBuilder.append("\nRandevular:\n");
	    for (Rendezvous rendezvous : rendezvous) {
	        dataBuilder.append("  Hasta: ").append(rendezvous.getPatient().getName())
	                   .append(", Tarih: ").append(rendezvous.getDateTime())
	                   .append(", Doktor: ").append(rendezvous.getDoctor().getName()).append("\n");
	    }

	    return dataBuilder.toString();
	}

}
