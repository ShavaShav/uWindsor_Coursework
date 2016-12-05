package proj;

public class ShapeList extends AbstractList<Shape> {
	Shape[] list;
	int numShapes;
	
	public ShapeList(int numShapes)
	{
		list = new Shape[numShapes];
		this.numShapes = 0;	// initialize
	}
	
	public int size(){
		return numShapes;
	}
	
	@Override
	public ShapeList.ShapeIterator createIterator() {
		return new ShapeIterator();
	}

	@Override
	public void append(Shape v) {
		list[numShapes++] = v;	// places them in order they come in
	}
	
	public class ShapeIterator extends AbstractIterator implements MyIterator<Shape>{
		private int currentShape = 0;
		
		// first makes the first shape in the list the current item
		public void first()
		{
			currentShape = 0;
		}

		// next makes the next shape in the list the current item
		public void next()
		{
			currentShape++;
		}
		
		// isDone is true  when the current shape has gone past the last shape
		public boolean isDone()
		{
			return (currentShape >= numShapes);
		}
		
		// currentItem retrieves the value in current item
	    public Shape currentItem()
	    {
	    	return list[currentShape];
	    }
	    
	    // removeItem will remove current shape from list and return it -- must for compound shape
	    // currentItem will return the next shape in line after this call
	    public Shape removeItem()
	    {
	    	Shape toRemove = currentItem();	// store current shape
	    	int shapeToReturnTo = currentShape;
	    	numShapes--;	// decrement total
	    	while(!isDone())
	    		list[currentShape] = list[++currentShape]; // shift rest of shapes
	    	list[currentShape] = null;	// void out last shape as it will be duplicate of previous
	    	currentShape = shapeToReturnTo;	// reset iterator to place before shifting
	    	return toRemove;	// return the deleted shape
	    }
	}
}
