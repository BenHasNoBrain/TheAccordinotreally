import java.io.*;
import java.util.*;


public class bass_Converter	{
	static String[] keyTable = {"0", "F9", "0", "F5", "F3", "F1", "F2", "F12", "0", "F10", "F8", "F6", "F4", "TAB", "`", "0", "0", "LALT", "LSFT", "LCTRL", "q", "1", "0", "0", "0", "z", "s", "a", "w", "2", "0","0","c","x","d","e","4","3","0","0","' '","v","f","t","r","5","0","0","n","b","h","g","y","6","0","0","0","m","j","u","7","8","0",
	"0" , "','" ,  "k" ,  "i" ,  "o" ,  "'0'" ,  "9" ,  "0" ,
	"0" , "." , "/" ,  "l" , ";" ,  "p" , "-" ,  "0" ,
	"0" ,"0" ,"'" ,"0" ,"[" ,"=" ,"0" ,"0",
	"0" ,"CAPS" ,"0" ,"RHFT" ,"ENTER" ,"[", "]" ,"  0" ,"\\\\" ,"  0" ,"  0",
	"  0" ,"  0" ,"  0" ,"  0" ,"  0" ,"BCKSP" ,"  0",
	"n1" ,"  0" ,"n4" ,"n7" ,"  0" ,"  0" ,"  0",
	"n0" ,"n." ,"n2" ,"n5" ,"n6" ,"n8" ,"ESC" ,"NUMLCK",
	"F11" ,"n+" ,"n3" ,"n-" ,"n*" ,"n9" ,"SCRLL",
	   ""   ,
	      ""   ,""   ,""   ,""   ,
		 "F7"};

	static String[] keymap = {
	    "1", "2", "3", "4", "5", "6", "7", "8", "9","0", "-", "+",
	    "q","w","e","r","t","y","u","i","o","p","[", "]",
		"a","s","d" ,"f" ,"g" ,"h" ,"j" ,"k" ,"l" ,";", "'",
		"z", "x", "c", "v", "b", "n", "m", ",", ".", "/"
	};


	public static void main(String[] args)	{
		int[][] bassValues = {
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}	
		};

		String dd = "2 5 6 3 r 1 w 2 5 7 5";
		String[] aa = dd.split("\\s");

		for (int i = 0; i < aa.length; i++)	{
			//System.out.println(i + " = " + aa[i]);
		}

		try	{
			int getSize = keymap.length;
			int counter = 0;

			File inputter = new File("input.txt");
			Scanner theRead = new Scanner(inputter);
			while (theRead.hasNextLine())	{
				String[] data = theRead.nextLine().split("\\s");
				//System.out.println(Arrays.toString(data));

				Integer lastData = 0;

				if (!data[0].equals("//"))	{
					for (int i = 0; i < data.length; i++)	{
						for (int j = 0; j < keyTable.length; j++)	{
							if (keyTable[j].equals(keymap[counter]))	{
								bassValues[j][0] = Integer.parseInt(data[i]);
								lastData = Integer.parseInt(data[i]);
								j = 99;
								//System.out.println(keyTable[j]);
							}
						}
						if (counter < 44)	{counter++;}
						System.out.println(counter + ", " + keymap[counter - 1] + " | " + lastData);
					}
				}

			}
			theRead.close();




			FileWriter outputter = new FileWriter("output.txt", false);
			outputter.write("byte freeBassValues[132][3] = {");			
			for (int i = 0; i < bassValues.length; i++)	{
				String s = Arrays.toString(bassValues[i]);
				s = s.substring(1, s.length() - 1);
				outputter.write("{" + s);

				if (i < bassValues.length - 1)	{
					outputter.write("}, ");
				} else	{
					outputter.write("}");
				}
			}
			outputter.write("};");
			outputter.close();




		} catch (Exception e)	{
			System.out.println("Error: ");
			e.printStackTrace();
		}
	}
}
