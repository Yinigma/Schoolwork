public class Student extends AcademicPerson {

	// Instance variables
	private int[] grades; // grade for the corresponding course
	private static final int MAX_COURSES = 30; // maximum number of courses
	int numCourses = 0;

	// Constructor
	public Student(String name, String address) {
		super(name, address);
		courses = new String[MAX_COURSES];
		grades = new int[MAX_COURSES];
	}

	// It adds a course and corresponding grade to the lists.
	// Student can take the same course couple of times. If a course that
	// already exists in the list is given as the input of the method you need
	// to compare the input grade with the one that is saved in the Grades list,
	// the higher grade needs to be saved in the Grades list.
	public void addCourseGrade(String course, int grade) {
		if(course==null){
			return;
		}
		for(int i = 0; i<MAX_COURSES; i++){
			if(courses[i]==null){
				courses[i] = course;
				grades[i] = grade;
				numCourses++;
				break;
			}
			else if(course.equals(courses[i])&&grade>grades[i]){
				grades[i] = grade;
			}
		}
	}

	// This method prints the student's average grade for all the courses.
	// This method throws IllegalDivisionByZero exception, when there is no
	// courses in the list.
	public void getAverageGrade() throws IllegalDivisionByZero {
		if(numCourses==0){
			throw new IllegalDivisionByZero("Division by zero!");
		}
		else{
			double arrSum = 0;
			for(int i:grades){
				arrSum+=i;
			}
			System.out.print("Average is: "+arrSum/numCourses+"\n");
		}
	}

	// It prints all the courses with the corresponding grades in each line.
	@Override
	public void printCourses() {
		if(courses.length==0||grades.length==0){
			return;
		}
		System.out.print("Course name\tCourse grade\n");
		for(int i = 0; i<MAX_COURSES; i++){
			if(courses[i]==null)
				break;
			else{
				System.out.print(courses[i]+"\t\t"+grades[i]+"\n");
			}
		}
	}

	public int[] getGrades() {
		return grades;
	}

	public void setGrades(int[] grades) {
		this.grades = grades;
	}

	@Override
	public String toString() {
		return "Student: " + super.toString();
	}
}