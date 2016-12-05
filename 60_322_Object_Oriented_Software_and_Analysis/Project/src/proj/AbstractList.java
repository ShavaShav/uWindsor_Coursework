package proj;

public abstract class AbstractList<T> {
	public abstract AbstractIterator createIterator();
	public abstract void append(T v);
	public abstract class AbstractIterator implements MyIterator<T>{
	}
}
