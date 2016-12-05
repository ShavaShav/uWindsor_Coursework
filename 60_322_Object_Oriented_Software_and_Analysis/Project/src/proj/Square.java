package proj;

import java.awt.Color;
import java.awt.Graphics;

public class Square extends Shape {
	// Square is a rectangle by delegation
	private Rectangle thisSquare;
	private int size;
	
	public Square(Color currentColor) {
		super();
		thisSquare = new Rectangle(currentColor);
		size = 50;
		thisSquare.changeHeight(size);
		thisSquare.changeWidth(size);
	}
	
	// square uses rectangle methods for changing size
	// where height and width are same
	public void changeSize(int size)
	{
		thisSquare.changeHeight(size);
		thisSquare.changeWidth(size);
		this.size = size;
	}

	@Override
	public boolean onThePerimeter(Coordinates mousePosition) {
		// TODO Auto-generated method stub
		return thisSquare.onThePerimeter(mousePosition);
	}

	@Override
	public boolean shapeIsSelected(Coordinates positionOfMouse) {
		return thisSquare.shapeIsSelected(positionOfMouse);
	}

	@Override
	public double calculateArea() {
		return thisSquare.calculateArea();
	}

	@Override
	public void showMe(Graphics g) {        
		thisSquare.showMe(g);
	}

	@Override
	public String toString() {
		return ("Square with reference point " + thisSquare.referencePoint 
				+ " having size "+ size + "\n");
	}

	@Override
	public void changeColor(Color c){
		thisSquare.changeColor(c);
	}
	@Override    
	public void changeColorTemporarily(){	                                                                                  
		thisSquare.changeColorTemporarily();
	}
	@Override
	public void changeColorBack(){	 
		thisSquare.changeColorBack();
	}
	@Override
	public void moveShape(Coordinates currentPositionMouse) {
		thisSquare.moveShape(currentPositionMouse);
	}
	
	@Override	
	public void resetShapeSelected(){
		thisSquare.resetShapeSelected();
	}
	
	@Override
	public void setShapeSelected(){
		thisSquare.setShapeSelected();
	}
	
	@Override
	public void savePositionWhereUserPressedMouse(int x, int y){
		thisSquare.savePositionWhereUserPressedMouse(x, y);
	}
	@Override
	public boolean shapeIsSelected(){
		return thisSquare.shapeIsSelected();
	}
}
