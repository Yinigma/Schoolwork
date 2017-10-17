import java.util.HashMap;
import java.util.Set;

public class TeachingAssistantStudent extends Student {

	private int hours; // total hours of TA
	protected HashMap<String, Integer> courseHour = new HashMap<String, Integer>();

	public TeachingAssistantStudent(String name, String address) {
		super(name, address);
		this.hours = 0;
	}

	// It adds a course into the HashMap with the key of course and hours as the
	// value. It also updates the instance variable hours when a course is added.
	// This method throws ArrayElementException when the course that is being
	// added to the HashMap already exists in it.
	public void addCourseHour(String course, int hours)
			throws ArrayElementException {
		if(courseHour.containsKey(course)){
			throw new ArrayElementException("Course already in list!");
		}
		else{
			this.hours+=hours;
			courseHour.put(course, hours);
		}

	}

	// This method first should print the courses along with the grades that the
	// TA is taking as a student and then print out the courses with the
	// corresponding hours which the TA is assisting in each line.
	// Use Iterator to iterate the HashMap.
	@Override
	public void printCourses() {
		super.printCourses();
		System.out.println("Courses Assisting\tHours");
		for(String s : courseHour.keySet()){
			System.out.println(s+"\t\t\t"+courseHour.get(s));
		}
	}

	public int getHours() {
		return hours;
	}

	public void setHours(int hours) {
		this.hours = hours;
	}

	@Override
	public String toString() {
		return super.toString() + " Also serving as Teaching Assistant.";
	}

}