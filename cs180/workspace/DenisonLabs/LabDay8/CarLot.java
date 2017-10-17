import java.util.ArrayList;

class CarLot {
	/**
	 * constructor
	 * 
	 * @param the
	 *            number of vehicles in the car lot
	 */
	
	private int numVehicles;
	private int capacity;
	private Car[] lotCars;
	
	public CarLot(int capacity) {
		if(capacity>=0){
			this.capacity = capacity;
		}
		else{
			this.capacity = 0;
		}
		lotCars = new Car[capacity];
	}

	/**
	 * @return the storage capacity of the car lot
	 */
	int capacity() {
		return this.capacity;
		
	}

	/**
	 * @return the number of vehicles in the car lot
	 */
	int numVehicles() {
		numVehicles = 0;
		for(Car c: lotCars){
			if(c!=null){
				numVehicles++;
			}
		}
		return numVehicles;
		
	}

	/**
	 * add a vehicle to the car lot
	 * 
	 * @param car
	 *            to be added
	 * @return true if there is space for the car, false otherwise
	 */
	boolean add(Car car) {
		if(car!=null&&lotCars.length>0){
			for(int i = 0; i<lotCars.length; i++){
				if(lotCars[i]==null){
					lotCars[i]=car;
					return true;
				}
			}
		}
		return false;
		
	}

	/**
	 * return the car at the specified location
	 * 
	 * @param location
	 *            from which to retrieve the car
	 * @return car at that location, or null if the location is empty
	 */
	Car get(int location) {
		if(location>=capacity||location<0||capacity==0){
			return null;
		}
		else{
			return lotCars[location];
		}
		
	}

	/**
	 * remove and return the car at the specified location
	 * 
	 * @param location
	 *            of the car to remove
	 * @return car removed from that location, or null if the location is empty
	 */
	Car remove(int location) {
		if(location>=capacity||location<0||capacity==0){
			return null;
		}
		else{
			Car toRemove = lotCars[location];
			lotCars[location]=null;
			this.compress();
			return toRemove;
		}
		
	}

	/**
	 * search for car that match the specified make
	 * 
	 * @param make
	 *            of the car to search for
	 * @return array of boolean values indicating which spaces contain vehicles
	 *         of the specified make.
	 * 
	 *         A value of true at index n indicates that the n-th space contains
	 *         a car of the specified make (match), whereas a value of false at
	 *         index n indicates that the n-th space contains a car of a
	 *         different make (mismatch).
	 */
	boolean[] searchByMake(String make) {
		boolean[] makeCzech = new boolean[lotCars.length];
		for(int i = 0; i<this.numVehicles(); i++){
			if(lotCars[i]!=null&&lotCars[i].getMake().equals(make)){
				makeCzech[i]=true;
			}
		}
		return makeCzech;
		
	}
	
	void compress(){
		Car[] compCars = new Car[lotCars.length];
		int j = 0;
		for(int i = 0; i<lotCars.length; i++){
			if(lotCars[i]!=null){
				compCars[j] = lotCars[i];
				j++;
			}
		}
		lotCars = compCars;
	}
}