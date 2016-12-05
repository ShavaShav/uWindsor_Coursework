package proj;

import java.awt.*;
import java.util.Observable;
import java.util.Observer;
import javax.swing.*;

	public class FrameShowingBigCircles extends JFrame implements Observer{
		private static final long serialVersionUID = 795097649096826160L;
		final static boolean DEBUG = true; // true for printouts
		ShapeList myShapes;
		ShapeList.ShapeIterator shapeIt;
		//Object myShapes[];
		int numberOfShapes;
		public  void showCircles(ShapeList shapes){
			myShapes = shapes;
			shapeIt = myShapes.createIterator();
			repaint();
		}
		public void paint(Graphics g){
			Circle currentCircle;
			super.paint(g);
			if (DEBUG) System.out.println("N = " + myShapes.size());
			for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
				if (shapeIt.currentItem() instanceof Circle){
					currentCircle = (Circle) shapeIt.currentItem();
					if (currentCircle.calculateArea() >= 5000.00){
						currentCircle.showMe(g);
					}			
				}
			}	
		}
		
		public FrameShowingBigCircles(){
			     super("Big Circles");
			     setSize(TesterFrame.WIDTH, TesterFrame.HEIGHT); 
			     setVisible(true);    
			   }
		
		@Override
		public void update(Observable obs, Object obj) {
			if (obj instanceof ShapeList)
			{
				ShapeList myShapes = (ShapeList) obj;
				showCircles(myShapes);
			}			
		}
	}
