package proj;

import java.awt.*;
/*
 * Written by Subir Bandyopadhyay Sept 1, 2012
 * Class Rectangle represents a rectangle. 
 * 
 * 
 * Properties of class Rectangle include all of Shape's plus:
 * size  - the height and the width of the rectangle
 * 
 * 	Must implement onThePerimeter(), shapeIsSelected(), calculateArea(), and showMe() from Shape
 */


public class Rectangle extends Shape{
	private int height, width;  // height and width of rectangle

	// Constructor creates a black rectangle with size 50 X 50 with upper left point at (200, 200)
	public Rectangle(Color currentColour){

		super(currentColour);
		height = 50;
		width = 50;
	}
	/*
	 * Method onThePerimeter checks if the user pressed the mouse button on the perimeter. 
	 * If so, it returns true; otherwise it return false.
	 */

	public boolean onThePerimeter(Coordinates mousePosition){
		int xWhereMousePressed, yWhereMousePressed;

		xWhereMousePressed = mousePosition.getX();
		yWhereMousePressed = mousePosition.getY();

		/*
		 * If the position where the user pressed the mouse button is within 5 pixels of 
		 * any side of the rectangle, the method will return true;
		 * Otherwise, it will return false.
		 */
		if (((xWhereMousePressed >= referencePoint.getX() - 5) &&
				(xWhereMousePressed <= (referencePoint.getX() + width + 5)) &&
				(yWhereMousePressed >= referencePoint.getY() - 5) &&
				(yWhereMousePressed <= (referencePoint.getY() + 5)))) return true;// top edge is edge # 0

				if (((xWhereMousePressed >= referencePoint.getX() - 5) &&
						(xWhereMousePressed <= (referencePoint.getX() + 5)) &&
						(yWhereMousePressed >= referencePoint.getY() - 5) &&
						(yWhereMousePressed <= (referencePoint.getY() + height + 5)))) return true;// left edge is edge # 1

				if (((xWhereMousePressed >= referencePoint.getX() - 5) &&
						(xWhereMousePressed <= (referencePoint.getX() + width + 5)) &&
						(yWhereMousePressed >= referencePoint.getY() + height - 5) &&
						(yWhereMousePressed <= (referencePoint.getY()+ height + 5)))) return true;//bottom edge-edge # 2

				if (((xWhereMousePressed >= referencePoint.getX() + width - 5) &&
						(xWhereMousePressed <= (referencePoint.getX() + width + 5)) &&
						(yWhereMousePressed >= referencePoint.getY() - 5) &&
						(yWhereMousePressed <= (referencePoint.getY() + height + 5)))) return true;// right edge-edge # 3

				return false;
	}

	public void changeWidth(int newWidth){
			width = newWidth;
	}
	public void changeHeight(int newHeight){
			height = newHeight;
	}
	
	/*
	 * Method shapeIsSelected(positionOfMouse) checks if the position of the mouse where the user
	 * pressed the left mouse button is within the shape (at least 5 pixels away from the perimeter.
	 * If so, the flag shapeSelected is set and the method returns true.
	 * Otherwise, the flag shapeSelected is reset and the method returns false.
	 */

	public boolean shapeIsSelected(Coordinates positionOfMouse){ 
		// Check if the user pressed the mouse button inside the shape
		int x, y;
		x = positionOfMouse.getX();
		y = positionOfMouse.getY();
		if ((x >= referencePoint.getX() + 5) &&
				(x <= referencePoint.getX() + width - 5) &&
				(y >= referencePoint.getY() + 5) &&
				(y <= referencePoint.getY() + height - 5)) {
			shapeSelected = true;
			lastMousePosition = positionOfMouse;
			return true;
		}else {
			shapeSelected = false;
			return false;
		}
	} 
	
	/*
	 * calculateArea() returns the area of the rectangle
	 */

	public double calculateArea(){ 
		return (width * height);
	}
	
	/*
	 * showMe(g) displays the rectangle using the Graphic object g.
	 * It sets the color to be used, and draws the rectangle using the specified 
	 * reference point, the width and the height.
	 */

	public void showMe(Graphics g){
		g.setColor(colorShape);
		g.drawRect(referencePoint.getX(), // Draw a rectangle with the specified 
				// corner point
				referencePoint.getY(),  // width and height
				width,
				height);
	}
	
	/* 
	 * toString() returns the description of the rectangle - the color, 
	 * the reference point and the size.
	 */

	public String toString(){
		return ("Rectangle with reference point " + referencePoint + " having width "
				+ width + " and height " + height + "\n");
	}
}


