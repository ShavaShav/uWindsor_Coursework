package proj;

import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.util.Observable;

public class TesterFrame extends JFrame{
	private static final long serialVersionUID = 2961615847198922947L;
	public static final int WIDTH = 900, HEIGHT = 500; // the width and height of the frame
	/*
	 * showSquaresAndRectangles will display information about all the squares and rectangles
	 * showBigCircles displays information about circles whose area exceeds 5000.00
	 * showCompoundShapes is an extra frame that displays information on compound shapes
	 */
	OutputFrame showSquaresAndRectangles; 
	FrameShowingBigCircles aFrameToDisplayBigCircles;
	CompoundFrame showCompoundShapes;
	// Phasee II - Observable object to send shapes to output windows when shapes are updated.
	DelegatedObservable delObs;
	// Phase III - Using Iterator pattern to hide data structure of shape list
	ShapeList myShapes;
	ShapeList.ShapeIterator shapeIterator;
    /* 
     * myShapes is an list of all the shapes (circles, rectangles and squares) that we have
     * In this version we will handle only a maximum of 20 shapes.
     */
	Shape currentShape; // helper for appending and resizing shapes being created
	CompoundShape currentCompoundShape;	// helper for creating compound shapes
	int currentPhase;
	Color currentColor = Color.black;
	/*  
	 * currentPhase depicts the current situation as follows:
	 *   currentPhase = 0, means the user may move any of the shapes
	 *                = 1, a new compound shape is being defined that contains a number of other shapes 
	 *                     (circles, rectangles or other compound shapes- when you implement compound shapes). 
	 *                     Most of the code  for this phase is not included in this class definition. It is your 
	 *                     responsibility to develop that. The code supplied now simply allows the users to specify the 
	 *                     shapes (circles, rectangles for now) to be included in the compound shape.
	 */
	
	/* 
	 * The frame includes the following components:
	 * 		myPanel - the panel where all the shapes (circles, rectangles, squares and compound shapes) 
	 *                are displayed.
	 *      shapeButtonPanel -  contains the buttons to specify what type of new shape to create
	 *                (circles, rectangles, squares and compound shapes,
	 *      colorChooserPanel - contains the radiobuttons redButton, greenButton, blueButton
	 *      sizeSpecifier - a slider to specify the size of the shapes (width or height of rectangles, 
	 *                   size of square or the diameter of circles)  
	 *      messageArea - an area for messages to the user 
	 *      yesButton, noButton - buttons for interaction when defining a new shape (circles, rectangles, squares)  
	 *      	
	 */
	EditorPanel myPanel; 
	JPanel shapeButtonPanel, colorChooserPanel;
	JTextField messageArea;
	ButtonGroup radioButtonGroupForSelectingShape, radioButtonGroupForChoosingColor;
	JRadioButton redButton, greenButton, blueButton, blackButton;
	JTextField inputArea;
	
	// Inner class since TesterFrame is already inheriting JFrame
	public class DelegatedObservable extends Observable{
		// Must override Observable's protected methods to access them
		@ Override
		protected void setChanged(){
			super.setChanged();
		}
		@ Override
		protected void clearChanged(){
			super.clearChanged();
		}
	}
	
	/*
	 * redisplay has the following responsibilities:
	 * 		a) display in showSquaresAndRectangles details about rectangles and squares
	 *      b) display in showBigCircle details about circles that have an area > 5000
	 */
	
	public void redisplay(){
		myPanel.repaint();
		// notify observers of change so they can display info about myShapes
		delObs.setChanged();
		delObs.notifyObservers(myShapes);
	}
	
	/*
	 * paintComponent is called when repaint is invoked.
	 * paintComponents simply displays all shapes. Hint : use polymorphism to simplify the code 
	 * 
	 */

	private class EditorPanel extends JPanel{
		public void paintComponent(Graphics g){
			super.paintComponent(g);
			
			for (shapeIterator.first(); !shapeIterator.isDone(); shapeIterator.next()){// Show all the shapes in my_shapes. 
					shapeIterator.currentItem().showMe(g);
			}
		}
	}

	private EditorPanel buildEditorPanel(){
		EditorPanel myPanel;
		myPanel = new EditorPanel();

		myPanel.addMouseListener(new MouseAdapter(){
			/* 
			 * mousePressed is important for selecting a shape for dragging it (currentPhase = 0) and for
			 *              selecting a perimeter of a shape to define a compound shape (currentPhase = 5).
			 * 
			 * mouseReleased is important to denote that the operation of dragging a shape is over.
			 * Hint : use polymorphism to simplify the code
			 */
			public void mouseReleased(MouseEvent e){
				for (shapeIterator.first(); !shapeIterator.isDone(); shapeIterator.next()){
					// when the mouse button is released reset the flags indicating that shape(s) or 
					// edge(s) has been selected and restore color since the drag operation or the modify 
					// operation is over.
						shapeIterator.currentItem().resetShapeSelected();
				}
			}

			public void mousePressed(MouseEvent e){
				int x_value, y_value;
				Coordinates currentMousePosition;
				x_value = e.getX(); // Find the coordinates of the position where the user pressed the mouse button
				y_value = e.getY();
				currentMousePosition = new Coordinates(x_value, y_value);
				if (currentPhase == 0){
					for (shapeIterator.first(); !shapeIterator.isDone(); shapeIterator.next()){
						/* 
						 * If a shape is selected by pressing mouse button inside the shape, 
						 * save the place where the user pressed mouse button sets the flag 
                         * denoting that the shape is selected.
						 */
							shapeIterator.currentItem().shapeIsSelected(currentMousePosition);
					}
				}
					/* 
					 * If we are defining compound shape i.e., currentPhase == 1, we select a
					 * shape by pressing the mouse button very close to the perimeter.
					 * The color of the shape is temporarily changed to yellow. 
					 * Hint : use polymorphism to simplify the code.
					 */
				else {
					for (shapeIterator.first(); !shapeIterator.isDone(); shapeIterator.next()){
						if (shapeIterator.currentItem().onThePerimeter(currentMousePosition)){
							Shape componentShape = shapeIterator.removeItem();	// remove from myShapes
							componentShape.changeColorTemporarily();			// change color to yellow temporarily
							currentCompoundShape.addShape(componentShape);		// add shape to compoundShape, which is part of myShapes
							break;
						} 
					}
				}		
				redisplay();
			}   	                      
		});

		myPanel.addMouseMotionListener(new MouseMotionAdapter(){
			public void mouseDragged(MouseEvent e){				
					/* 
					 * if the mouse is dragged when currentPhase is 0, the selected shapes move 
					 * with the mouse, using method moveShape.
					 * Hint : use polymorphism to simplify the code 
					 */
				for (shapeIterator.first(); !shapeIterator.isDone(); shapeIterator.next()){ 
					if (shapeIterator.currentItem().shapeIsSelected()){
						shapeIterator.currentItem().moveShape(new Coordinates(e.getX(), e.getY()));
					}
				}			
				redisplay();   
			} 
		});

		myPanel.setBackground(Color.WHITE);
		return myPanel;
	}

	private JPanel buildShapeChooserPanel(){
		JPanel buttonPanel;
		JButton squareButton, rectangleButton, circleButton, 
		        compoundFigureButton, shapeChangeButton;
        /*
         * Create each of the buttons squareButton, rectangleButton, circleButton, compoundFigureButton
         * and define the event handler for ActionEvent.
         */

		buttonPanel = new JPanel();
		compoundFigureButton = new JButton("COMPOUND");
		compoundFigureButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				if (currentPhase == 0){ // When button COMPOUND is pressed for the first time
					                    // currentPhase becomes 1 and the user can specify the shapes
					                    // (currently rectangle or circle) to be glued together
					currentPhase = 1;
					messageArea.setText("select figures to glue then press COMPOUND button again");
					currentCompoundShape = new CompoundShape();	// construct a new compound shape
					myShapes.append(currentCompoundShape);		// and add it to myShapes
					redisplay();
				} else{ // When button COMPOUND is pressed for the second time normal operation resumes again.
					    // This is currently done by setting currentPhase to 0. You have to include code to 
					    // create the compound shape.
					currentPhase = 0;
					messageArea.setText("");
					currentCompoundShape.changeColorBack();	// revert to original colors
					redisplay();
				}		
			}
		}
		);
		buttonPanel.add(compoundFigureButton);
		squareButton = new JButton("Create SQUARE");
		squareButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
			    messageArea.setText("Square size?");
			    currentShape = new Square(currentColor);
			    myShapes.append(currentShape);
				redisplay();
			}
		}
		);
		buttonPanel.add(squareButton);

		rectangleButton = new JButton("Create RECTANGLE");
		rectangleButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){	
				    messageArea.setText("Rectangle width?");
				    currentShape = new Rectangle(currentColor);
				    myShapes.append(currentShape);
					redisplay();
			}
		}
		);

		buttonPanel.add(rectangleButton);

		circleButton = new JButton("Create CIRCLE");
		circleButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
					currentShape = new Circle(currentColor);
					myShapes.append(currentShape);
					messageArea.setText("Circle Diameter?");
					redisplay();
			}
		}
		);
		buttonPanel.add(circleButton);
		messageArea = new JTextField(20);
		buttonPanel.add(messageArea);
		
		inputArea = new JTextField(3);
		inputArea.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				int width, height, size, diameter;
				if (messageArea.getText().equals("Rectangle width?")){
					if (!(inputArea.getText().equals(""))){
						width = Integer.parseInt(inputArea.getText());
						((Rectangle) currentShape).changeWidth(width);
					}
					messageArea.setText("Rectangle height?");
					inputArea.setText("");
					redisplay();
				} else if (messageArea.getText().equals("Rectangle height?")){
					if (!(inputArea.getText().equals(""))){
						height = Integer.parseInt(inputArea.getText());
						((Rectangle) currentShape).changeHeight(height);
					}
					messageArea.setText("");
					inputArea.setText("");
					redisplay();
				} else if (messageArea.getText().equals("Square size?")){
					if (!(inputArea.getText().equals(""))){
						size = Integer.parseInt(inputArea.getText());
						((Square) currentShape).changeSize(size);
					}
					messageArea.setText("");
					inputArea.setText("");
					redisplay(); 
				} else if (messageArea.getText().equals("Circle Diameter?")){
					if (!(inputArea.getText().equals(""))){
						diameter = Integer.parseInt(inputArea.getText());
						((Circle) currentShape).changeDiameter(diameter);
					}
					messageArea.setText("");
					inputArea.setText("");
					redisplay();
				}	
			} 
		}
		);
		buttonPanel.add(inputArea);
		return buttonPanel;
	} 


	/*
	 * buildColorChooserPanel included 3 radio buttons so that users can select red, blue or green
	 * in addition to the original black color for the newly created shape. The user can select 
	 * one of these buttons to change the color for the newly created shape.
	 * We have used a  straight-forward anonymous handler for events in each radio button.
	 */

	private JPanel buildColorChooserPanel(){
		JPanel radioButtonPanel;
		

		radioButtonPanel = new JPanel();
		blackButton = new JRadioButton("BLACK");
		blackButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				currentColor = Color.black;
			}
		}
		);
		redButton = new JRadioButton("RED");
		redButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				currentColor = Color.red;
			}
		}
		);

		greenButton = new JRadioButton("GREEN");
		greenButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				currentColor = Color.green;
			}
		}
		);

		blueButton = new JRadioButton("BLUE");
		blueButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				currentColor = Color.blue;
			}
		}
		);

		radioButtonGroupForChoosingColor = new ButtonGroup();

		radioButtonGroupForChoosingColor.add(blueButton);
		radioButtonGroupForChoosingColor.add(greenButton);
		radioButtonGroupForChoosingColor.add(redButton);
		radioButtonPanel.add(blackButton);
		radioButtonPanel.add(blueButton);
		radioButtonPanel.add(greenButton);
		radioButtonPanel.add(redButton);
		return radioButtonPanel;
	}

	public TesterFrame(){	
		showSquaresAndRectangles = new OutputFrame();
		aFrameToDisplayBigCircles = new FrameShowingBigCircles();
		showCompoundShapes = new CompoundFrame();
		
		delObs = new DelegatedObservable();
		delObs.addObserver(aFrameToDisplayBigCircles);
		delObs.addObserver(showSquaresAndRectangles);
		delObs.addObserver(showCompoundShapes);
		
		myShapes = new ShapeList(20);
		shapeIterator = myShapes.createIterator();
		
		currentPhase = 0;
		myPanel = buildEditorPanel();
		shapeButtonPanel = buildShapeChooserPanel();
		colorChooserPanel = buildColorChooserPanel();

		add(colorChooserPanel, BorderLayout.NORTH);
		add(shapeButtonPanel, BorderLayout.SOUTH);
		add(myPanel, BorderLayout.CENTER);
		setSize(WIDTH, HEIGHT);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}

	public static void main(String a[]){
		TesterFrame aFrame = new TesterFrame();
	}
}