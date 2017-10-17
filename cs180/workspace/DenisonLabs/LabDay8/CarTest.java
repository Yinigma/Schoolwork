import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;


public class CarTest {
	
	CarLot carLot;
	CarLot flawLot;
	CarLot zeroLot;
	
	@Before
	public void setup() throws Exception{
		carLot = new CarLot(10);
		carLot.add(new Car("red", "ford"));
        carLot.add(new Car("blue", "gm"));
        carLot.add(new Car("yellow", "ford"));
        carLot.add(new Car("red", "chevy"));
        carLot.add(new Car("blue", "ford"));   
        carLot.add(new Car("orange", "gm"));
        carLot.add(new Car("purple", "honda"));
        flawLot = new CarLot(6);
        flawLot.add(new Car("red", "ford"));
        flawLot.add(new Car(null, "gm"));
        flawLot.add(new Car(null, null));
        flawLot.add(new Car("purple", null));
        zeroLot = new CarLot(0);
	}
	
	//Just in case you're an especially shitty car dealer
	@Test
	public void testNegativeLot() {
		int i = zeroLot.numVehicles();
		String m = "numVehicles(): ensures that numVehicles will return zero if the capacity is zero";
		assertEquals(m,i,0);
	}
	@Test
	public void testZeroLotNumVehicles() {
		int i = zeroLot.numVehicles();
		String m = "numVehicles(): ensures that numVehicles will return zero if the capacity is zero";
		assertEquals(m,i,0);
	}
	@Test
	public void testZeroLotAdd() {
		boolean b = zeroLot.add(new Car(null,null));
		String m = "add(): ensures that this method returns false instead of crashing when capacity is zero";
		assertFalse(m,b);
	}
	@Test
	public void testZeroLotGet() {
		Car c = zeroLot.get(0);
		String m = "get(): ensures that this method returns null instead of crashing when capacity is zero and requested index is zero";
		assertEquals(m,c,null);
	}
	@Test
	public void testZeroLotRemove() {
		Car c = zeroLot.remove(0);
		String m = "remove(): ensures that this method returns null instead of crashing when capacity is zero and requested index is zero";
		assertEquals(m,c,null);
	}
	@Test
	public void testGetMakeNull(){
		Car c = new Car("red",null);
		String a  = c.getMake();
		String m = "getMake(): ensures that a car's constructor will replace a null argument with \'ng\' for \'not given\' and that the getMake() method will return such.";
		assertEquals(m,a,"ng");
	}
	@Test
	public void testGetColorNull(){
		Car c = new Car(null,"ford");
		String a  = c.getColor();
		String m = "getMake(): ensures that a car's constructor will replace a null argument with \'ng\' for \'not given\' and that the getColor() method will return such.";
		assertEquals(m,a,"ng");
	}
	@Test
	public void testNumVehicles(){
		int a  = carLot.numVehicles();
		String m = "numVehicles(): tests to see if this method returns the corrrect number of vehicles";
		assertEquals(m,a,7);
	}
	@Test
	public void testNumVehiclesAfterRemove(){
		carLot.remove(2);
		int a  = carLot.numVehicles();
		String m = "numVehicles(): tests to see if this method returns the corrrect number of vehicles after running the remove() method";
		assertEquals(m,a,6);
	}
	@Test
	public void testNumVehiclesAfterAdd(){
		carLot.add(new Car("Taco","Ford"));
		int a  = carLot.numVehicles();
		String m = "numVehicles(): tests to see if this method returns the corrrect number of vehicles after running the add() method";
		assertEquals(m,a,8);
	}
	@Test
	public void testAdd(){
		carLot.add(new Car("black","Tesla"));
		String m = "add(): tests if the car at the end of the array is the car added by the add method";
		String a = carLot.get(7).getColor()+" "+carLot.get(7).getMake();
		assertEquals(m,a,"black Tesla");
	}
	@Test
	public void testRemove(){
		Car b = carLot.get(0);
		Car c = carLot.remove(0);
		boolean a = b.equals(c);
		String m = "remove(): tests to see if the remove method returns the correct car and that the car is removed from the array.";
		String act = a+" "+carLot.numVehicles();
		assertEquals(m,act,"true 6");
	}
	@Test
	public void testGet(){
		String m = "get(): tests to see if the get() method will return the correct car";
		Car c = carLot.get(4);
		boolean a = c.getMake().equals("ford")&&c.getColor().equals("blue");
		assertTrue(m,a);
	}

}
