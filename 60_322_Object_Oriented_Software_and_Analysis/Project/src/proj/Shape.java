package proj;

import java.awt.Color;
import java.awt.Graphics;
/*
* Properties of class Shape
* referencePoint - the left top corner of enclosing square
* lastMousePosition - the last position where the mouse was pressed, 
* 						useful when moving the rectangle
* colorShape - color of the Shape
* shapeSelected - a boolean variable which is true if the shape is 
* 					selected for moving 
* 
* capabilities of class Shape (See below for more details)
* changeColor - modify the color of the shape
* changeColorTemporarily - modify the color of the shape to yellow - useful when selecting a shape
* changeColorBack - revert back to original color
* changeShape - modify the width or the height of the shape
* moveShape - move the shape by dragging the mouse 
* resetShapeSelected - reset the shapeSelected flag
* savePositionWhereUserPressedMouse - useful when dragging a shape
* 
* capabilities of class Shape to be implemented in subclasses:
* shapeIsSelected - mark a shape as "selected" by pressing the mouse button inside the shape
* onThePerimeter - returns true if mouse is pressed very close to the circumference of the shape
* calculateArea - determine the area of the shape
* showMe - display the shape inside the frame
* toString - return a string describing the shape.
* 
*  distance - a static method that returns the distance between shapes
*/

public abstract class Shape {
	// Instance variables are protected to allow access from subclass
	protected Coordinates referencePoint; //reference point for a shape
	protected Coordinates lastMousePosition; // If a shape has 
	// been  selected, the position where the 
	// user has pressed the mouse to select the shape

	protected Color colorShape; // color of a shape
	protected Color originalColorShape;// Used to save the original color when the color changes temporarily

	protected boolean shapeSelected = false;
	protected boolean perimeterSelected = false;// Whether the shape has  been selected for 
	// moving by pressing mouse button inside the shape
	
	// Constructor
	public Shape(Color currentColor){
		referencePoint = new Coordinates(200, 200);  // new figure is at the center of frame
		colorShape = currentColor; 
	}
	
	// No-arg constructor - for use primarily by compoundShape
	public Shape(){}
	
	
	/* 
	 * changeColor(c) modifies the color of the shape to the new color c
	 */

	public void changeColor(Color c){
		colorShape = c ;
	}
	
	
	public void changeColorTemporarily(){	 
		originalColorShape = colorShape; 
		colorShape = Color.yellow ;
		perimeterSelected = true;
	}
	
	public void changeColorBack(){	 
		colorShape = originalColorShape; 
		perimeterSelected = false;
	}
	
	// ABSTRACT METHODS - to be implemented in subclasses

	/*
	 * Method onThePerimeter checks if the user pressed the mouse button on the perimeter. 
	 * If so, it returns true; otherwise it return false.
	 */

	public abstract boolean onThePerimeter(Coordinates mousePosition);

	/*
	 * Method shapeIsSelected(positionOfMouse) checks if the position of the mouse where the user
	 * pressed the left mouse button is within the shape (at least 5 pixels away from the perimeter.
	 * If so, the flag shapeSelected is set and the method returns true.
	 * Otherwise, the flag shapeSelected is reset and the method returns false.
	 */
	
	public abstract boolean shapeIsSelected(Coordinates positionOfMouse);

	/*
	 * calculateArea() returns the area of the shape
	 */
	
	public abstract double calculateArea();

	/*
	 * showMe(g) should display the shape using the Graphic object g.
	 * It sets the color to be used, and draws the shape using the specified 
	 * reference point, and subclass variables
	 */
	
	public abstract void showMe(Graphics g);
	
	/* 
	 * toString() should return the description of the shape - the color, 
	 * the reference point and the size.
	 */
	
	public abstract String toString();
	
	// Altered toString that adds padding to result of regular toString
	public String toString(int numSpaces){
		return generatePadding(numSpaces) + toString();
	}

	// Returns a string made up of "numSpaces" space characters for use by toString()
	protected String generatePadding(int numSpaces){
		String padding = "";
		for (int i = 0; i < numSpaces; i++){
			padding += ' ';
		}
		return padding;
	}
	
	/* 
	 * Method shapeIsSelected() returns true if the user previously selected the shape by 
	 * pressing the mouse button with the cursor inside the shape.
	 */

	public boolean shapeIsSelected(){
		return shapeSelected;
	}

	/*
	 * Method moveShape(currentPositionMouse) allows the user to drag the shape by dragging the mouse
	 * button. 
	 */

	public void moveShape(Coordinates currentPositionMouse){	     	
		if (shapeSelected) {		
			// If a shape is selected for a move operation, change the reference point 
			// as the mouse is being dragged.
			referencePoint.setX(referencePoint.getX() + 
					currentPositionMouse.getX() -
					lastMousePosition.getX());
			referencePoint.setY(referencePoint.getY() +
					currentPositionMouse.getY() -
					lastMousePosition.getY());
			lastMousePosition = currentPositionMouse;
		}
	}
	
	/* 
	 * resetShapeSelected() simply resets the value of shapeSelected to false.
	 */

	public void resetShapeSelected(){
		shapeSelected = false;
	}
	
	// setShapeSelected() sets the value of shapeSelected to true - needed for compound shape moving.
	public void setShapeSelected(){
		shapeSelected = true;
	}

	public void savePositionWhereUserPressedMouse(int x, int y){
		lastMousePosition = new Coordinates(x, y);
	}

	// returns the distance between two coordinates
	public static double distance(Coordinates point1, Coordinates point2){
		double dist; // dist is the distance from point1 to point2
		dist = Math.sqrt((double) ((point1.getX() - point2.getX())*
				(point1.getX() - point2.getX()) +
				(point1.getY() - point2.getY())*(point1.getY() - point2.getY())));
		return dist ;
	} 
	
}
