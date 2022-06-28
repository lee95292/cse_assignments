package queue;

public class ArrayQueue {
	private final static int QUEUE_SIZE =100;
	private String[] queue;
	private int front;
	private int reer;
	
	ArrayQueue()
	{
		queue=new String[QUEUE_SIZE];
		front=-1;
		reer=-1;
	}
	public void add(String data)
	{
		
		if(reer==QUEUE_SIZE-1){
			System.out.println("queue full");
			return;
		}
		
		if(front==-1)
		{
			front=0;
			reer=0;
			queue[front]=data;
		}
		else
		{
			reer++;
			queue[reer]=data;
		}
		System.out.println(data+"(입력)");
	}
	
	public void remove()
	{
		if(reer==-1||reer<front)
		{
			System.out.println("queue empty");
			return;
		}
		
		System.out.println(queue[front]+"출력");
		front++;
		
	}
	public void peek()
	{
		if(reer==-1||reer<front)
		{
			System.out.println("queue empty");
			return;
		}
		System.out.println(queue[reer]);
	}
	public void empty()
	{
		front=-1;
		reer=-1;
	}
	
	public static void main(String[] args) {
		ArrayQueue qrqe=new ArrayQueue();
		
		qrqe.add("사과");
		qrqe.add("감");
		qrqe.remove();
		qrqe.remove();
		qrqe.add("귤");
		qrqe.add("포도");
		qrqe.add("배");
				
	}

}
