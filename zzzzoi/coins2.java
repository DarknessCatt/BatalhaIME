
public class coins2 {
	
	public static void main(String[] args){
		
		double[] a = new double[501];
		
		StdDraw.setXscale(-1, a.length);
		StdDraw.setYscale(-1.1, 1.1);
		StdDraw.setPenRadius(0.003);
		
		a[0] = 0;
		
		if(Math.random()>0.5)
			a[1] = 1;
		else
			a[1] = - 1;
		
		StdDraw.line(0,0,1,a[1]);
		
		for(int i = 2; i<a.length; i++){
		
			if(Math.random()>0.5)
				a[i] = a[i-1] + 1;
			else
				a[i] = a[i-1] - 1;
			
			StdDraw.line(i-1, a[i-1]/(i-1),i, a[i]/i);
		
		}
		
		StdDraw.setPenColor(StdDraw.RED);
		
		if(Math.random()>0.5)
			a[1] = 1;
		else
			a[1] = - 1;
		
		StdDraw.line(0,0,1,a[1]);
		
		for(int i = 2; i<a.length; i++){
			
			if(Math.random()>0.5)
				a[i] = a[i-1] + 1;
			else
				a[i] = a[i-1] - 1;
			
			StdDraw.line(i-1, a[i-1]/(i-1),i, a[i]/i);
		
		}
		
		StdDraw.setPenColor(StdDraw.BLUE);
		
		if(Math.random()>0.5)
			a[1] = 1;
		else
			a[1] = - 1;
		
		StdDraw.line(0,0,1,a[1]);
		
		for(int i = 2; i<a.length; i++){
			
			if(Math.random()>0.5)
				a[i] = a[i-1] + 1;
			else
				a[i] = a[i-1] - 1;
			
			StdDraw.line(i-1, a[i-1]/(i-1),i, a[i]/i);
		
		}
		
	}

}
