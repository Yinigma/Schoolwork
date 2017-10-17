class Car {

	/**
	 * @param color
	 *            of the car
	 * @param make
	 *            of the car
	 */
	
	private String color;
	private String make;
	
	public Car(String color, String make) {
		if(color!=null){
			this.color = color;
		}
		else{
			this.color = "ng";
		}
		if(make!=null){
			this.make = make;
		}
		else{
			this.make = "ng";
		}
	}

	/**
	 * @return the make of the vehicle
	 */
	String getMake() {
		return make;
	}

	/**
	 * @return the color of the vehicle
	 */
	String getColor() {
		return color;
	}
	boolean nullCar(){
		return color==null||make==null;
	}
}