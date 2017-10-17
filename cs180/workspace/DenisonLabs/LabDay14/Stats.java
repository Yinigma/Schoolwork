import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import java.util.Iterator;
import java.util.Map.Entry;
public class Stats {
	
	public static HashMap<String,Integer> wins(){
		BufferedReader b;
		Integer i;
		HashMap<String, Integer> map = new HashMap<String, Integer>();
		try{
			//System.out.println(System.getProperty("user.dir"));
			b = new BufferedReader(new FileReader("input.txt"));
			String s;
			String[] tokens;
			while((s = b.readLine()) !=null){
				String[] winners;
				tokens = s.split("vs.");
				if(new Scanner(tokens[0]).nextInt()==1){
					tokens[0] = tokens[0].substring(2);
					winners = tokens[0].split(" ");
				}
				else{
					tokens[1] = tokens[1].substring(1);
					winners = tokens[1].split(" ");
				}
				for(String v: winners){
					
					i = map.get(v);
					if(i==null){
						map.put(v, 1);
					}
					else{
						map.put(v, ++i);
					}
				}
			}
		}
		catch(IOException e){
			System.out.println("file failed to load!");
		}
		return map;
	}
	public static String winner(){
		HashMap<String, Integer> map = wins();
		String winner = "";
		int biggest = 0;
		String s;
		Iterator<Entry<String, Integer>> iter  = map.entrySet().iterator();
		while(iter.hasNext()){
			//System.out.println(s);
			Entry<String, Integer> e = iter.next();
			s = e.getKey();
			if(map.get(s)>biggest){
				winner = s;
				biggest = map.get(s);
			}
			
		}
		return winner;
	}
	
	
}
