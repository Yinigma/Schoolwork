    public class SystemSolve {
        private double[][] coefficientsMatrix;
        private double[] bVector;
        private double[] solutionVector;
        private int numEquations;
     
        /**
         * Solves a system of equations given as a lower-triangular matrix.
         */
        private void forwardSolve() {
        	
        }
     
        /**
         * Solves a system of equations given as an upper-triangular matrix.
         */
        private void backwardSolve() {
        	double[] res = new double[coefficientsMatrix.length];
        	double num;
            for(int i = coefficientsMatrix.length; i>0; i--){
            	num = 0;
            	for(int j = coefficientsMatrix[i].length-1; j>1; j--){
            		num += res[j]*coefficientsMatrix[i][j];
            	}
            	res[i] = (bVector[i] - num)/coefficientsMatrix[i][0];
            }
            solutionVector = res;
        }
     
        /**
         * Reads the file at the given filename to parse and store the coefficients 
         * matrix and the bVector. The file should be a text file starting with a 
         * single integer on the first line specifying the total number of equations. 
         * The following lines contain the equations, one per line as the coefficients 
         * and b-constant. 
         * Equations are of the form:
         * 
         * a_0*x_0 + a_1*x_1 + ... + a_n-1*x_n-1 = b_n-1
         * 
         * listed in the text file as the form:
         * 
         * a_0,a_1,...,a_n,b_n
         * 
         * The equations represent a system and is given as either an upper 
         * triangular system or a lower triangular system.
         * 
         * @param filename The name of the file containing the input text
         */
        public double[] parseAndSolve(String filename) {
            // TODO: implement this method
            return solutionVector;
        }
     
        /**
         * Prints the given coefficients matrix and solution vector as a system 
         * with matrix formatting as a lower triangular matrix.
         * 
         * @param matrix The coefficients matrix
         * @param vector The solution vector
         */
        void printLowerTriangularMatrix(double[][] matrix, double[] vector) {
            for (int i = 0; i < matrix.length; i++) {
                for (int j = 0; j < matrix[i].length; j++) {
                    System.out.printf("%.3f\t", matrix[i][j]);
                }
                for (int k = matrix.length - 1; k > i; k--) {
                    System.out.print("\t");
                }
                System.out.printf("| %.3f%n", vector[i]);
            }
            System.out.println();
        }
     
        /**
         * Prints the given coefficients matrix and solution vector as a system 
         * with matrix formatting as an upper triangular matrix.
         * 
         * @param matrix The coefficients matrix
         * @param vector The solution vector
         */
        void printUpperTriangularMatrix(double[][] matrix, double[] vector) {
    	for (int i = 0; i < matrix.length; i++) {
    	    for (int k = 0; k < i; k++) {
    		System.out.print("\t");
    	    }
    	    for (int j = 0; j < matrix[i].length; j++) {
    		System.out.printf("%.3f\t", matrix[i][j]);
    	    }
    	    System.out.printf("| %.3f%n", vector[i]);
    	}
    	System.out.println();
        }
     
        /**
         * Prints the given vector as a column vector.
         * 
         * @param vector The vector to print
         */
        void printVector(double[] vector) {
    	for (int i = 0; i < vector.length; i++) {
    	    System.out.printf("%3.3f%n", vector[i]);
    	}
    	System.out.println();
        }
    }


