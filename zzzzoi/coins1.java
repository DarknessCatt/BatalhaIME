

public class coins1 {
	
	public static void main(String[] args){
		
		double[] a = new double[501];
		
		StdDraw.setXscale(-1, a.length);
		StdDraw.setYscale(-70, 70);
		StdDraw.setPenRadius(0.003);
		
		a[0] = 0;
		
		StdDraw.point(0,0);
		
		for(int i = 1; i<a.length; i++){
		
			if(Math.random()>0.5)
				a[i] = a[i-1] + 1;
			else
				a[i] = a[i-1] - 1;
			
			StdDraw.line(i-1, a[i-1], i, a[i]);
		
		}
		
		StdDraw.setPenColor(StdDraw.RED);
		
		for(int i = 1; i<a.length; i++){
			
			if(Math.random()>0.5)
				a[i] = a[i-1] + 1;
			else
				a[i] = a[i-1] - 1;
			
			StdDraw.line(i-1, a[i-1], i, a[i]);
		
		}
		
		StdDraw.setPenColor(StdDraw.BLUE);
		
		for(int i = 1; i<a.length; i++){
			
			if(Math.random()>0.5)
				a[i] = a[i-1] + 1;
			else
				a[i] = a[i-1] - 1;
			
			StdDraw.line(i-1, a[i-1], i, a[i]);
		
		}
		
	}

}
