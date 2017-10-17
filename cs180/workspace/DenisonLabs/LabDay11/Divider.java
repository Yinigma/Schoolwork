public class Divider implements Runnable{
	
	private int start;
	private int end;
	public static Counter counter = new Counter2();
	
	public Divider(int start,int end){
		this.start = start;
		this.end = end;
	}
	
	@Override
	public void run(){
		int place = start;
		while(place<=end){
			if(place%7==0){
				counter.inc();
			}
			place++;
		}
	}
}
