
public class Driver {
	public static void main(String[] args){
		Thread t1 = new Thread(new Divider(1,1000));
		Thread t2 = new Thread(new Divider(1001,2000));
		Thread t3 = new Thread(new Divider(2001,3000));
		t1.start();
		t2.start();
		t3.start();
		try{
			t1.join();
			t2.join();
			t3.join();
		}
		catch(InterruptedException e){
			System.out.println("You're tearing me apart, Lisa!");
		}
		System.out.println(Divider.counter.get());
	}
}
