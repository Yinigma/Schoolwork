import java.util.Stack;


public class Evaluator{
	
	static Stack<Integer> stack = new Stack<Integer>();
	
	public static int evaluate(String s){
		String[] tokens = s.split(" ");
		Integer n1 = 0;
		Integer n2 = 0;
		for(int i = 0; i<tokens.length; i++){
			if(tokens[i].equals("+")){
				n2 = stack.pop();
				n1 = stack.pop();
				stack.push(n1+n2);
			}
			else if(tokens[i].equals("-")){
				n2 = stack.pop();
				n1 = stack.pop();
				stack.push(n1-n2);
			}
			else if(tokens[i].equals("*")){
				n2 = stack.pop();
				n1 = stack.pop();
				stack.push(n1*n2);
			}
			else if(tokens[i].equals("/")){
				n2 = stack.pop();
				n1 = stack.pop();
				stack.push(n1/n2);
			}
			else{
				stack.push(Integer.parseInt(tokens[i]));
			}
		}
		return stack.pop();
	}
}
