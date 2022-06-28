package circularQueue;

public class CircularArrayQueue {

	private final static int QUEUE_SIZE =100;
	
	public String queue[];
	private int front;
	private int rear;
	
	CircularArrayQueue()
	{
		queue=new String[QUEUE_SIZE];
		front=-1;
		rear=-1;
	}
	
	public void add(String data)
	{
		if(rear==-1)
		{
			rear=0;
			front=rear;
			queue[rear]=data;
		}
		else if(front==((rear+1)%QUEUE_SIZE))
		{
			//System.out.println("stack full");
		}
		else{
			queue[++rear]=data;
		}
		System.out.println(data+"(입력)");

	}
	
	public void remove()
	{
		if(rear<front||rear==-1)
		{
			System.out.println("queue empty");
			return;
		}
		System.out.println(queue[front]+"(출력)");
		front=(front+1)%QUEUE_SIZE;
	}
	
	public void peek()
	{
		if(front<rear||rear==-1)
		{
			System.out.println("queue empty");
		}else
		{
			System.out.println(queue[rear]);
		}
	}
	
	public void empty()
	{
		front=-1;
		rear=-1;
	}
	public static void main(String[] args) {
		CircularArrayQueue ciaq = new CircularArrayQueue();
		
		ciaq.add("사과");
		ciaq.add("감");
		ciaq.remove();
		ciaq.remove();
		ciaq.add("귤");
		ciaq.add("포도");
		ciaq.add("배");
	}

}
