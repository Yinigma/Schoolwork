/**
 * @author Ben "Kenobi" Denison
 * 
 * This is the test class for the matrix class.
 * 
 * bdenison@purdue.edu
 * 
 */


import static org.junit.Assert.*;
import org.junit.*;

public class MatrixTest {
	
	public static final int[][] EMPTY = {{},{},{}};
	public static final int[][] NULLARRAY = null;
	public static final int[][] NULLROWS = {null,null,null,null};
	public static final int[][] SQUARE = {{0,0,0},{0,0,0},{0,0,0}};
	public static final int[][] NOTSQUARE = {{0,0},{0,0},{0,0}};
	public static final int[][] UNEVEN = {{0,0,0,0},{0,0},{0,0,0},{0}};
	Matrix m;
	
	@Before
	public void setup() throws Exception{
		 m = new Matrix();
	}
	@Test(timeout = 100)
	public void emptyMatrixTest(){
		boolean a = m.allValid(EMPTY);
		String m = "Check if it catches an empty array";
		assertFalse(m,a);
	}
	@Test(timeout = 100)
	public void nullColumnTest(){
		boolean a = m.allValid(NULLARRAY);
		String m = "Check if it catches a null array";
		assertFalse(m,a);
	}
	@Test(timeout = 100)
	public void nullRowTest(){
		boolean a = m.allValid(NULLROWS);
		String m = "Check if it catches a null array";
		assertFalse(m,a);
	}
	@Test(timeout = 100)
	public void testIdentity(){
		int[][] id = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
		boolean a = m.isIdentity(id);
		String m = "Checks if an identity matrix returns true";
		assertTrue(m,a);
	}
	@Test(timeout = 100)
	public void testNearIdentity(){
		int[][] idNear = {{1,0,0,5},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
		boolean a = m.isIdentity(idNear);
		String m = "Checks if an the isIdentity() method returns false for a matrix with a non-zero outside the diagonal";
		assertFalse(m,a);
	}
	@Test(timeout = 100)
	public void testZeroIdentity(){
		int[][] idOther = {{1,0,0,0},{0,64,0,0},{0,0,1,0},{0,0,0,1}};
		boolean a = m.isIdentity(idOther);
		String m = "Checks if an the isIdentity() method returns false for a matrix with a non-one number in the diagonal";
		assertFalse(m,a);
	}
	@Test(timeout = 100)
	public void testSquareMatrix(){
		boolean a = m.isSquare(SQUARE);
		String m = "isSquare(): checks if this method returns true given a square matrix";
		assertTrue(m,a);
	}
	@Test(timeout = 100)
	public void testNotSquareMatrix(){
		boolean a = m.isSquare(NOTSQUARE);
		String m = "isSquare(): checks if this method returns false given a non-square matrix";
		assertFalse(m,a);
	}
	@Test(timeout = 100)
	public void testUnevenMatrix(){
		boolean a = m.isSquare(UNEVEN);
		String m = "isSquare(): checks if this method returns false a int[][] with varying dimensions";
		assertFalse(m,a);
	}
	@Test(timeout = 100)
	public void testNearDiagonal(){
		int[][] diag = {{256,0,0,3},{0,64,0,12},{-5,8,16,0},{0,0,0,4}};
		boolean a = m.isDiagonal(diag);
		String m = "isDiagonal: checks if it'll return false for a non-diagonal matrix";
		assertFalse(m,a);
	}
	@Test(timeout = 100)
	public void testDiagonal(){
		int[][] diag = {{256,0,0,0},{0,64,0,0},{0,0,16,0},{0,0,0,4}};
		boolean a = m.isDiagonal(diag);
		String m = "isDiagonal: checks if it'll take a matrix which Identity() didn't";
		assertTrue(m,a);
	}
	@Test(timeout = 100)
	public void testUpperTri(){
		int[][] utri = {{3,6,8},{0,3,1},{0,0,5}};
		boolean a = m.isUpperTriangular(utri);
		String m = "isUpperTriangular(): tests if this method returns true on an upper triangular matrix";
		assertTrue(m,a);
	}
	@Test(timeout = 100)
	public void testUpperTriOB(){
		int[][] utriBad = {{3,6,8},{0,3,1},{3,0,5}};
		boolean a = m.isUpperTriangular(utriBad);
		String m = "isUpperTriangular(): tests if this method returns false on a matrix that has a non-zero in the lower triangle";
		assertFalse(m,a);
	}
	@Test(timeout = 100)
	public void testUpperTriZero(){
		int[][] utriBad = {{3,6,0},{0,3,1},{0,0,5}};
		boolean a = m.isUpperTriangular(utriBad);
		String m = "isUpperTriangular(): tests if this method returns false on a matrix that has a zero in the upper triangle";
		assertFalse(m,a);
	}
	@Test(timeout = 100)
	public void testSymmetric(){
		int[][] sym = {{1,5,6,12},
					   {5,1,17,9},
					   {6,17,1,4},
					   {12,9,4,1}};
		boolean a = m.isSymmetric(sym);
		String m = "isSymmetric(): tests if this method returns true on a symmetric matrix";
		assertTrue(m,a);
	}
	@Test(timeout = 100)
	public void testOffSymmetric(){
		int[][] sym = {{5,5,6,12},
					   {5,1,17,9},
					   {6,17,1,4},
					   {6,9,4,1}};
		boolean a = m.isSymmetric(sym);
		String m = "isSymmetric(): tests if this method returns false on a slightly off matrix";
		assertFalse(m,a);
	}
	@Test(timeout = 100)
	public void testTriDiag(){
		int[][] diag = {{5,5,0,0},
					    {5,1,17,0},
					    {0,13,1,4},
					    {0,0,4,1}};
		boolean a = m.isTriDiagonal(diag);
		String m = "isTriDiag(): tests if this method returns true on a tridiagonal matrix";
		assertTrue(m,a);
	}
	@Test(timeout = 100)
	public void testZeroTriDiag(){
		int[][] diag = {{5,5,0,0},
					    {5,1,0,0},
					    {0,13,1,4},
					    {0,0,4,1}};
		boolean a = m.isTriDiagonal(diag);
		String m = "isTriDiag(): tests if this method returns false on a matrix where there is a zero in the upper diagonal";
		assertFalse(m,a);
	}
	@Test(timeout = 100)
	public void testOBTriDiag(){
		int[][] diag = {{5,5,0,0},
					    {5,1,5,0},
					    {0,13,1,4},
					    {8,0,4,1}};
		boolean a = m.isTriDiagonal(diag);
		String m = "isTriDiag(): tests if this method returns false on a matrix there is a non-zero outside the diagonals";
		assertFalse(m,a);
	}
	
}
