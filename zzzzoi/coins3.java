
public class coins3 {
	
	public static void main(String[] args){
		
		double[] a = new double[501];
		
		StdDraw.setXscale(-1, a.length);
		StdDraw.setYscale(-1.1, 1.1);
		StdDraw.setPenRadius(0.0001);
		
		a[0] = 0;
		
		if(Math.random()>0.5)
			a[1] = 1;
		else
			a[1] = - 1;
		
		StdDraw.line(0,0,1,a[1]);
		
		for(int i = 2; i<a.length; i++){
		
			if(Math.random()>0.5)
				a[i] = 1;
			else
				a[i] = - 1;
			
			StdDraw.line(i-1, (a[i-2]+a[i-1])/2,i, (a[i-1]+a[i])/2);
		
		}
		
		StdDraw.setPenColor(StdDraw.RED);
		
		if(Math.random()>0.5)
			a[1] = 1;
		else
			a[1] = - 1;
		
		StdDraw.line(0,0,1,a[1]);
		
		for(int i = 2; i<a.length; i++){
			
			if(Math.random()>0.5)
				a[i] = 1;
			else
				a[i] = - 1;
			
			StdDraw.line(i-1, (a[i-2]+a[i-1])/2,i, (a[i-1]+a[i])/2);
		
		}
		
		StdDraw.setPenColor(StdDraw.BLUE);
		
		if(Math.random()>0.5)
			a[1] = 1;
		else
			a[1] = - 1;
		
		StdDraw.line(0,0,1,a[1]);
		
		for(int i = 2; i<a.length; i++){
			
			if(Math.random()>0.5)
				a[i] = 1;
			else
				a[i] = - 1;
			
			StdDraw.line(i-1, (a[i-2]+a[i-1])/2,i, (a[i-1]+a[i])/2);
		
		}
		
	}

}
