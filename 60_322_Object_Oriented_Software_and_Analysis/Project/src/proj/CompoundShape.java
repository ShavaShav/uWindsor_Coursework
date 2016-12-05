package proj;

import java.awt.Color;
import java.awt.Graphics;

/* 
 * Compound shape has no properties of it's own, and all shape
 * methods will be delegated to it's component shapes.
 */
public class CompoundShape extends Shape {
	ShapeList componentShapes;
	ShapeList.ShapeIterator shapeIt;
	
	public CompoundShape(){
		super();
		componentShapes = new ShapeList(100);
		shapeIt = componentShapes.createIterator();
	}
	
	// addShape() adds a shape to the list of component shapes
	public void addShape(Shape shape){
		componentShapes.append(shape);
	}
	
	/*
	 *  IMPLEMENTING ABSTRACT METHODS
	 */
	 
	 // Method onThePerimeter checks if the user pressed the mouse button on the perimeter 
	 // of one of the component shapes. If so, it returns true; otherwise it return false.
	@Override
	public boolean onThePerimeter(Coordinates mousePosition) {
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
			if (shapeIt.currentItem().onThePerimeter(mousePosition)){
				return true;	// mouse is on the perimeter of a component shape				
			}
		}
		
		return false;	// mouse not on any perimeter 
	}

	/*
	 * Method shapeIsSelected(positionOfMouse) checks if the position of the mouse where the user
	 * pressed the left mouse button is within ANY SHAPE (at least 5 pixels away from the perimeter.
	 * If so, the flag shapeSelected is set FOR ALL SHAPES and the method returns true.
	 * Otherwise, the flag shapeSelected is reset FOR ALL SHAPES and the method returns false.
	 */
	@Override
	public boolean shapeIsSelected(Coordinates positionOfMouse) {
		boolean insideShape = false;
		// check if any of component shapes are selected
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
			if (shapeIt.currentItem().shapeIsSelected(positionOfMouse)){
				insideShape = true;
				break;
			}
		}
		
		if(insideShape){ // set all shapeSelected flags for component shapes
			setShapeSelected();
		} else { // reset all shapeSelected flags for components
			resetShapeSelected();
		}
		
		// save last mouse position for each component shape
		savePositionWhereUserPressedMouse(positionOfMouse.getX(), positionOfMouse.getY()); 
		
		return insideShape;
	}

	// calculateArea() returns the total area covered by a compound shape
	@Override
	public double calculateArea() {
		double area = 0.0;
		// total area of all component shapes
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
			area += shapeIt.currentItem().calculateArea();
		}
		return area;
	}

	/*
	 * showMe(g) should display the compound shape using the Graphic object g.
	 * It invokes the showMe method for each component shape
	 */
	@Override
	public void showMe(Graphics g) {
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
			shapeIt.currentItem().showMe(g);
		}
	}

	// toString() should return the description of each component shape 
	// - the color, the reference point and the size.
	@Override
	public String toString(){
		return toString(0);	// delegate to padded toString with no padding
	}
	
	// will recursively format the toString of the component shapes
	// each level adds 4 spaces to start of string for visually showing hierarchy
	public String toString(int numSpaces){
		String desc = generatePadding(numSpaces) + 
				"Compound shape with a total area of " + calculateArea() + ":\n";
		
		// will display regular shapes first so they appear before compounds
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next())
			if (!(shapeIt.currentItem() instanceof CompoundShape))
				desc += shapeIt.currentItem().toString(numSpaces + 4);
		
		// now will display the compound shape children
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next())
			if (shapeIt.currentItem() instanceof CompoundShape)
				desc += shapeIt.currentItem().toString(numSpaces + 4);
		
		return desc;
	}

	/*
	 *  THESE METHODS ARE OVERRIDES, so that shape methods
	 *  are simply delegated to children instead of the compound shape
	 */
	
	@ Override
	public void changeColor(Color c){
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
			shapeIt.currentItem().changeColor(c);
		}
	}
	
	@ Override
	public void changeColorTemporarily(){	 
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
			shapeIt.currentItem().changeColorTemporarily();
		}
	}
	
	@Override
	public void changeColorBack(){	 
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
			shapeIt.currentItem().changeColorBack();
		}
	}
	
	// Method shapeIsSelected() returns true if the user previously selected the shape by 
	// pressing the mouse button with the cursor inside of one of the component shapes
	@Override
	public boolean shapeIsSelected(){
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
			if (shapeIt.currentItem().shapeIsSelected()){
				return true;
			}
		}
		return false;
	}
	
	// Method moveShape(currentPositionMouse) allows the user to drag the shapes by dragging the mouse
	// button. 
	@Override
	public void moveShape(Coordinates currentPositionMouse){
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
			shapeIt.currentItem().moveShape(currentPositionMouse);
		}
	}
	
	/* 
	 * set and resetShapeSelected() simply reset the value of shapeSelected of components to true and false respectively
	 */

	@Override
	public void resetShapeSelected(){
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
			shapeIt.currentItem().resetShapeSelected();
		}
	}
	
	@Override
	public void setShapeSelected(){
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
			shapeIt.currentItem().setShapeSelected();
		}
	}

	// save mouse position for all of component shapes -- critical for moving shape
	@Override
	public void savePositionWhereUserPressedMouse(int x, int y){
		for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
			shapeIt.currentItem().savePositionWhereUserPressedMouse(x, y);
		}
	}
}
