package proj;

/* 
 *Class Coordinates correspond to the position of a point on a 
 * 2-dimensional plane. The properties are the x and y coordinates of the point.
 * It has the appropriate getter and setter methods, along with a toString method.
 */ 


public class Coordinates {
	private int xCoordinates, yCoordinates; 

	// Constructor
	public Coordinates(int x, int y){
		xCoordinates = x;
		yCoordinates = y;
	}

	public void setX(int x){
		xCoordinates = x;
	}

	public void setY(int y){
		yCoordinates = y;
	}

	public int getX(){ 
		return xCoordinates;
	}

	public int getY(){ 
		return yCoordinates;
	}
	
	public String toString(){
		return "(" + xCoordinates + ", " + yCoordinates + ")";
	}
}
