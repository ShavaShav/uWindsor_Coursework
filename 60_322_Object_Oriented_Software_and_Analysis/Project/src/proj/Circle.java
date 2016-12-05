package proj;

import java.awt.Color;
import java.awt.Graphics;

/*
 * Written by Subir Bandyopadhyay Sept 1, 2012
 * Class Rectangle represents a rectangle. 
 * 
 * Properties and capabilities of class Circle include all of Shape's plus:
 * PI -  PI to 2 digits
 * diameter  - the diameter of the circle
 * 
 * computerCentreOfCircle - returns centre Coordinates of circle (private to circle)
 * 
 * Must implement onThePerimeter(), shapeIsSelected(), calculateArea(), showMe(), and toString() from Shape
 */
public class Circle extends Shape{
	public final double PI = 3.14;
	private int diameter;
	
	// Constructor creates a black circle with diameter 50 
	public Circle(Color currentColor){
		super(currentColor);
		diameter = 50;
	}
	
	public void changeDiameter(int newDiameter){
		diameter = newDiameter;
	}

	/*
	 * Method onThePerimeter checks if the user pressed the mouse button on the perimeter. 
	 * If so, it returns true; otherwise it return false.
	 */

	public boolean onThePerimeter(Coordinates mousePosition)
	{// the perimeter is selected if the distance from the point (x, y) to the center  is 
		// between radius - 5 and radius + 5
		int distanceFromCenter;
		Coordinates centreOfCircle;
		
		centreOfCircle = computeCenterOfCircle(referencePoint, diameter);
		distanceFromCenter = (int) distance(mousePosition, centreOfCircle);
		if ((distanceFromCenter >= diameter/2 - 5) && 
				(distanceFromCenter <= diameter/2 + 5)) {
			return true;
		} else{
			return false;
		}
	}

	/*
	 * Method shapeIsSelected(positionOfMouse) checks if the position of the mouse where the user
	 * pressed the left mouse button is within the shape (at least 5 pixels away from the perimeter.
	 * If so, the flag shapeSelected is set and the method returns true.
	 * Otherwise, the flag shapeSelected is reset and the method returns false.
	 */

	public boolean shapeIsSelected(Coordinates positionOfMouse){ 
		// Check if the user pressed the mouse button inside the shape
		double distance;

		Coordinates centreOfCircle;
		centreOfCircle = computeCenterOfCircle(referencePoint, diameter);
		distance = Shape.distance(positionOfMouse, centreOfCircle);
		if (distance < diameter/2 - 5){
			shapeSelected = true;
			lastMousePosition = positionOfMouse;
			return true; 
		} else {
			shapeSelected = false;
			return false;
		}
	}

	/*
	 * changeShape changes the diameter of the circle, if
	 * currentPhase is 3 .
	 * currentPhase = 0, means the user is moving the shape
	 *              = 1, a new shape is being created
	 *              = 2, the the color of the new shape is being modified,
	 *              = 3, the diameter of the circle is being modified,
	 */

	public void changeShape(int currentPhase, int size){
		int newReferencePointX, newReferencePointY;
		if (currentPhase == 3){
			newReferencePointX = referencePoint.getX() + (diameter - size)/2;
			newReferencePointY = referencePoint.getY() + (diameter - size)/2;
			referencePoint = new Coordinates(newReferencePointX, newReferencePointY);
			diameter = size; 
		} 

	}

	private Coordinates computeCenterOfCircle(Coordinates referencePoint, int diameter){
		int xValueOfCenter,yValueOfCenter;
		xValueOfCenter = referencePoint.getX() + diameter/2;;
		yValueOfCenter = referencePoint.getY() + diameter/2;
		return new Coordinates(xValueOfCenter, yValueOfCenter);
	}
	/*
	 * calculateArea() returns the area of the rectangle, fulfills Shape contract
	 */

	public double calculateArea(){ 
		return (PI * diameter * diameter/4);
	}

	/*
	 * showMe(g) displays the rectangle using the Graphic object g.
	 * It sets the color to be used, and draws the rectangle using the specified 
	 * reference point, the width and the height.
	 */

	public void showMe(Graphics g){
		g.setColor(colorShape);
		g.drawOval(referencePoint.getX(), // Draw a circle with the specified 
				// corner point and diameter
				referencePoint.getY(),   
				diameter,
				diameter);
	}

	/* 
	 * toString() returns the description of the circle - the color, 
	 * the reference point and the size.
	 */

	public String toString(){
		return ("Circle with reference point " + referencePoint + " having diameter " + diameter + "\n");
	}

}
