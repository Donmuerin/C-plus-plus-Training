
public class Calculator {
	//stage2
	private double memory1;
	private double memory2;
	private double memory3;
	private double current;
	
	public Calculator()
	{ 
		memory1 = 0;
		memory2 = 0;
		memory3 = 0;
		current = 0;
	}
	
	public double currval()
	{
		return current;
	}
	//stage 3
	public boolean isnum(String input) {
		  try {
		    Double.parseDouble(input);
		    return true;
		  }
		  catch (NumberFormatException e) {
		    //is not numeric
		    return false;
		  }
		}
		
	
	public double add(String val)
	{
		current += Double.parseDouble(val);
		return current;
	}
	//stage 4
	public double subtract(String val)
	{
		current -= Double.parseDouble(val);
		return current;
	}
	//stage 5
	public double multiply(String val)
	{
		current *= Double.parseDouble(val);
		return current;
	}
	//stage 6
	public double division(String val)
	{
		current /= Double.parseDouble(val);
		return current;
	}
	//stage 7
	public void reset()
	{
		current = 0;
	}
	
	public boolean tomemory (int position)
	{
		if(position < 1 || position > 3)
			return false;
		else{
			if(position == 1)
				memory1 = current;
			else if (position == 2)
				memory2 = current;
			else if (position == 3)
				memory3 = current;
			
			return true;
		}
	}
	
	public boolean frommemory(int position)
	{
		if (position < 1 || position > 3)
			return false;
		else{
			if (position == 1)
				current = memory1;
			else if (position == 2)
				current = memory2;
			else if (position == 3)
				current= memory3;
			
			return true;
		}
	}

	
}