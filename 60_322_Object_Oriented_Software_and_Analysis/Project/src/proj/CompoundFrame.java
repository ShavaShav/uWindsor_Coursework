package proj;

import java.util.Observable;
import java.util.Observer;

import javax.swing.JFrame;
import javax.swing.JTextArea;

public class CompoundFrame extends JFrame implements Observer{
	private static final long serialVersionUID = 5349793525341716268L;
	final int WIDTH = 600, HEIGHT = 400;
	private JTextArea outputArea;
	public CompoundFrame(){
		super("Compound Shapes");
		outputArea = new JTextArea(20, 30);
		add(outputArea);
		setSize(WIDTH, HEIGHT);
		setVisible(true);
	}
	public void displayResult(String s){
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
				if (shape instanceof CompoundShape)
					outputString1 += shape.toString();
			}
			displayResult(outputString1);
		}
		
	}
}