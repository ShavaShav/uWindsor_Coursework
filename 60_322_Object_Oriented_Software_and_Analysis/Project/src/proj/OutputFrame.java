package proj;

import java.util.Observable;
import java.util.Observer;
import javax.swing.*;

public class OutputFrame extends JFrame implements Observer{
	private static final long serialVersionUID = 5349793525341716268L;
	final int WIDTH = 400, HEIGHT = 300;
	private JTextArea outputArea;
	public OutputFrame(){
		super("Rectangles");
		outputArea = new JTextArea(20, 30);
		add(outputArea);
		setSize(WIDTH, HEIGHT);
		setVisible(true);
	}
	public void displayResult(String s){
		//			System.out.println(s);
		outputArea.setText(s);
	}
	
	@Override
	public void update(Observable obs, Object obj) {
		if (obj instanceof ShapeList)
		{
			ShapeList myShapes = (ShapeList) obj;
			ShapeList.ShapeIterator shapeIt = myShapes.createIterator();
			String outputString1 = "";
			for (shapeIt.first(); !shapeIt.isDone(); shapeIt.next()){
				Shape shape = shapeIt.currentItem();
				if (shape instanceof Rectangle || shape instanceof Square)
					outputString1 += shape.toString();
			}
			displayResult(outputString1);
		}
		
	}
}


