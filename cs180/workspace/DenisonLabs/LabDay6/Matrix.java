/**
 * @author Ben "Kenobi" Denison
 * 
 * This is the matrix class from lab 6. It has five methods for testing the the properties of matrices
 * 
 * bdenison@purdue.edu
 * 
 */

public class Matrix {
	
	//Czechs to see if a matrix is n x n
	public boolean isSquare(int[][] a){
		for(int[]b:a){
			if(b.length!=a.length){
				return false;
			}
		}
		return true;
	}
	
	//Czechs to make sure that no array is null or empty
	public boolean allValid(int[][] a){
		if(a==null||a.length==0){
			return false;
		}
		else{
			for(int[] b:a){
				if(b==null||b.length==0){
					return false;
				}
			}
			return true;
		}
	}
	//Czechs to see if a matrix is symmetric
	public boolean isSymmetric(int[][] mat){
		if(isSquare(mat)&&allValid(mat)){
			for(int i = 0; i<mat.length; i++){
				for(int j = 0; j<i; j++){
					if(mat[i][j]!=mat[j][i]){
						return false;
					}
				}
			}
			return true;
		}
		else{
			System.out.println("2");
			return false;
		}
	}
	//Czech if diagonal
	public boolean isDiagonal(int[][] mat){
		if(isSquare(mat)&&allValid(mat)){
			for(int i = 0; i<mat.length; i++){
				if(mat[i][i]!=0){
					for(int j = 0; j<mat[i].length; j++){
						if(i!=j&&mat[i][j]!=0){
							return false;
						}
					}
				}
				else{
					return false;
				}
			}
			return true;
		}
		else{
			return false;
		}
	}
	//Czech if identity
	public boolean isIdentity(int[][] mat){
		if(isSquare(mat)&&allValid(mat)){
			for(int i = 0; i<mat.length; i++){
				if(mat[i][i]==1){
					for(int j = 0; j<mat[i].length; j++){
						if(i!=j&&mat[i][j]!=0){
							return false;
						}
					}
				}
				else{
					return false;
				}
			}
			return true;
		}
		else{
			return false;
		}
	}
	//Czech if upper triangluar
	public boolean isUpperTriangular(int[][] mat){
		if(isSquare(mat)&&allValid(mat)){
			for(int i = 0; i<mat.length; i++){
				for(int j = 0; j<mat[i].length; j++){
					if(j<i-1&&mat[i][j]!=0){
						return false;
					}
					else if(j>=i&&mat[i][j]==0){
						return false;
					}
				}
			}
			return true;
		}
		else{
			return false;
		}
	}
	public boolean isTriDiagonal(int[][] mat){
		if(isSquare(mat)&&allValid(mat)){
			for(int i = 0; i<mat.length; i++){
				for(int j = 0; j<mat[i].length; j++){
					if(j==i||j==i+1||j==i-1){
						if(mat[i][j]==0){
							return false;
						}
					}
					else{
						if(mat[i][j]!=0){
							return false;
						}
					}
				}
			}
			return true;
		}
		else{
			return false;
		}
	}
}
