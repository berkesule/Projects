package berkesule;

import java.io.Serializable;
import java.util.LinkedList;

public class Hospital  implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private final int id;
	private String name;
	private LinkedList<Section> sections;
	public Hospital(int id, String name) {
		this.id = id;
		this.name = name;
		this.sections = new LinkedList<Section>();
		
	}
	
	public int getId() {
		return id;
	}
	
	public String getName() {
		return name;
	}


	public Section getSection(int id) {
		for(Section section : sections) {
			if(section.getId() == id) {
				return section;
			}
		}
		return null;
	}
	
	
	//overload
	@SuppressWarnings("unused")
	private Section getSection(String name) {
	    for (Section section : sections) {
	        if (section.getName().equalsIgnoreCase(name)) { 
	            return section;
	        }
	    }
	    return null;
	}
	
	
	public synchronized void addSection(Section section) throws DuplicateInfoException {
	    for (Section s : sections) {
	        if (section.getId() == s.getId()) {
	            throw new DuplicateInfoException("Section with ID " + s.getId() + " already exists.");
	        }
	    }
	    sections.add(section);		
	}

	public LinkedList<Section> getSections() {
		return sections;
	}

}
