public class SorterFirstGeneration {
	private Triangle[] small;
	private Triangle[] medium;
	private Triangle[] large;

	private int nSmall;
	private int nMedium;
	private int nLarge;

	public SorterFirstGeneration() {
		this.small = new Triangle[5];
		this.medium = new Triangle[5];
		this.large = new Triangle[5];

		this.nSmall = 0;
		this.nMedium = 0;
		this.nLarge = 0;
	}

	/**
	 * Add the triangle in the good container and update the statistics.
	 */
	public void sort(Triangle p) {
		double a  = p.area();
		if(a<10){
			checkAndExpand();
			small[nSmall] = p;
			nSmall++;
		}
		else if(a>=10&&a<=50){
			checkAndExpand();
			medium[nMedium] = p;
			nMedium++;
		}
		else if(a>50){
			checkAndExpand();
			large[nLarge] = p;
			nLarge++;
		}
	}

	/**
	 * This function check the state of the three arrays. If one of them is
	 * full, it constructs a new array with one more element and transfers all
	 * the Triangles.
	 */
	public void checkAndExpand() {
		Triangle [] empty;
		int newSize;
		if(nSmall>=small.length){
			newSize = nSmall + 1;
			empty = new Triangle[newSize];
			for(int i = 0; i<small.length; i++){
				empty[i] = small[i];
			}
			small = empty;
		}
		if(nMedium>=medium.length){
			newSize = nMedium + 1;
			empty = new Triangle[newSize];
			for(int i = 0; i<medium.length; i++){
				empty[i] = medium[i];
			}
			medium = empty;
		}
		if(nLarge>=large.length){
			newSize = nLarge + 1;
			empty = new Triangle[newSize];
			for(int i = 0; i<large.length; i++){
				empty[i] = large[i];
			}
			large = empty;
		}
	}

	public void printStatistics() {
		System.out.printf("There are currently %d triangle in stock:\n",
				this.nSmall + this.nMedium + this.nLarge);
		System.out.printf(" - %d small\n", this.nSmall);
		System.out.printf(" - %d medium\n", this.nMedium);
		System.out.printf(" - %d large\n\n", this.nLarge);
	}
}