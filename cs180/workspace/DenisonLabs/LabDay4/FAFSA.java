import java.util.Scanner;


/**
 * 
 * @author Ben "Kenobi" Denison
 *
 *This is the workhorse of the program that calculates how much aid a student will receive. 
 *It does all the math and selection statements and the like. It's pretty funky fresh.
 *
 *PUID: 0028399054
 *email: bdenison@purdue.edu fobjamin13@gmail.com
 *
 */

public class FAFSA {
	boolean hasSSN;
	boolean accepted;
	boolean selecServ;
	boolean resStatus;
	boolean dependent;
	
	int age;
	int credHours;
	
	double EFC;
	double incomeParent;
	double incomeStudent;
	
	String classStanding;
	int undergrad;
	boolean eligible;
	
	public static final int GRAD = 0;
	public static final int UNDERGRAD = 1;
	public static final int INVALID = 2;
	
	
	public FAFSA(boolean accepted,boolean selecServ,boolean hasSSN,boolean resStatus,boolean dependent,
			int age,int credHours, double incomeStudent, double incomeParent, String classStanding){
		this.accepted = accepted;
		this.selecServ = selecServ;
		this.hasSSN = hasSSN;
		this.resStatus = resStatus;
		this.dependent = dependent;
		this.age = age;
		this.credHours = credHours;
		this.incomeParent = incomeParent;
		this.incomeStudent = incomeStudent;
		if(classStanding!=null){
			this.classStanding = classStanding;
		}
		else{
			this.classStanding = "";
		}
		
		this.selecServ = revSelecServ();
		this.classStanding = this.classStanding.toLowerCase();
		undergrad = undergrad();
		EFC = calcEFC();
		eligible = isFederalAidEligible();
	}
	
	//This sees if the schmuck in question is eligible for financial aid
	public boolean isFederalAidEligible(){
		if(accepted&&selecServ&&hasSSN&&resStatus){
			return true;
		}
		else{
			return false;
		}
	}
	
	//Returns the estimated family contribution
	public double calcEFC(){
		if(dependent){
			return incomeStudent+incomeParent;
		}
		else{
			return incomeStudent;
		}
	}
	
	
	public double calcFederalGrant(){
		if(eligible&&EFC<=50000.00&&undergrad==1){
			if(credHours<9){
				return 2500.00;
			}
			else{
				return 5775.00;
			}
		}
		else{
			return 0.00;
		}
	}
	
	
	public double calcStaffordLoan(){
		if(eligible){
			if(credHours<9){
				return 0;
			}
			else{
				if(dependent){
					if(undergrad==1){
						return 5000.00;
					}
					else if(undergrad==0){
						return 10000.00;
					}
					else{
						return 0.00;
					}
				}
				else{
					if(undergrad==1){
						return 10000.00;
					}
					else if(undergrad==0){
						return 20000.00;
					}
					else{
						return 0.00;
					}
				}
			}
		}
		else{
			return 0.00;
		}
	}
	
	
	public double calcWorkStudy(){
		if(eligible){
			if(EFC<=30000.00){
				return 1500.00;
			}
			else if(EFC>30000.00&&EFC<=40000.00){
				return 1000.00;
			}
			else if(EFC>40000.00&&EFC<=50000.00){
				return 500.00;
			}
			else{
				return 0.00;
			}
		}
		else{
			return 0.00;
		}
	}
	
	
	public double calcFederalAidAmount(){
		return calcFederalGrant()+calcStaffordLoan()+calcWorkStudy();
	}
	private boolean revSelecServ(){
		if(age>=18&&age<=25){
			return selecServ;
		}
		else{
			return true;
		}
	}
	private int undergrad(){
		if(classStanding.equals("undergrad")||classStanding.equals("undergraduate")){
			return UNDERGRAD;
		}
		else if(classStanding.equals("grad")||classStanding.equals("graduate")){
			return GRAD;
		}
		else{
			System.out.println("Invalid argument for class standing. Get on my level. Lern2tipe scrub.");
			return INVALID;
		}
	}
}
