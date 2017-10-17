public class Triangle implements Polygon{

	double a1;
	double a2;
	double a3;
	double l1;
	double l2;
	double l3;
	
	public Triangle(int l1, int l2, int l3){
		this.l1 = l1;
		this.l2 = l2;
		this.l3 = l3;
		this.a1 = angleFromSides(this.l2,this.l3,this.l1);
		this.a2 = angleFromSides(this.l3,this.l1,this.l2);
		this.a3 = angleFromSides(this.l1,this.l2,this.l3);
	}
	
	public Triangle(int l1, int l2, double a3){
		this.l1 = l1;
		this.l2 = l2;
		this.a3 = a3;
		this.l3 = oppSide(this.a3,this.l1,this.l2);
		this.a1 = angleFromSides(this.l2,l3,this.l1);
		this.a2 = angleFromSides(l3,this.l1,this.l2);
		
	}
	
	public double perimeter(){
		return l1+l2+l3;
	}
	public double area(){
		return Math.abs(.5*l1*l2*Math.sin(l3));
	}
	public static double area(int a, int b, double c){
		return Math.abs(.5*a*b*Math.sin(c));
		
	}

	/**
	 * This functions computes the included angles of a triangle
	 * 
	 * @param adj1
	 *            one of the adjacent side
	 * @param adj2
	 *            the other adjacent side
	 * @param opp
	 *            the opposite side
	 */
	public static double angleFromSides(double adj1, double adj2, double opp) {
		double pythagoras = opp * opp - adj1 * adj1 - adj2 * adj2;
		if (pythagoras >= 0)
			return Math.acos(pythagoras / (2 * adj1 * adj2));
		else
			return Math.PI - Math.acos(-pythagoras / (2 * adj1 * adj2));
	}

	/**
	 * This functions computes the length of the opposite side
	 * 
	 * @param angle
	 *            the included angle
	 * @param adj1
	 *            one of the adjacent side
	 * @param adj2
	 *            the other adjacent side
	 */
	public static double oppSide(double angle, double adj1, double adj2) {
		return Math.sqrt(adj1 * adj1 - 2 * adj1 * adj2 * Math.cos(angle) + adj2
				* adj2);
	}
	
	public int getNumSides(){
		return 3;
	}

}
