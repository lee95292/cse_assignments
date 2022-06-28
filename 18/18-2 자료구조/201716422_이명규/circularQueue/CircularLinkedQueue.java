package circularQueue;

public class CircularLinkedQueue {
	
	private node front;
	private node reer;
	private node tmpNode;
	CircularLinkedQueue() {
		front=null;
		reer=null;
	}
	
	public void add(String data)
	{
		if(front==null)
		{
			reer=new node(data);
			front=reer;
			reer.next=front;
		}else
		{
			tmpNode=reer;
			reer=new node(data);
			tmpNode.next=reer;
			reer.next=front;
		}
		System.out.println(data+"(입력)");
	}
	public void printQueue(int n)
	{
		int i;
		for(i=0;i<n;i++)
		{
			
		}
	}
	public void remove()
	{
		if(reer==null)
		{
			System.out.println("queue empty");
		}
		if(front==reer)
		{
			
		}
		else
		{
			System.out.println(front.data+"(출력)");
			front=front.next;
			reer.next=front;
		}
	}
	
	public void peek()
	{
		if(reer==null)
		{
			System.out.println("queue empty");
		}else
		{
			System.out.println(front.data);
		}
	}
	
	public void empty()
	{
		front=null;
		reer=null;
		tmpNode=null;
	}
	
	class node
	{
		private node next;
		private String data;
		node(String data)
		{
			this.data=data;
			this.next=null;
		}
	}
	public static void main(String[] args) {
		CircularLinkedQueue cilq = new CircularLinkedQueue();
		
		cilq.add("사과");
		cilq.add("감");
		cilq.remove();
		cilq.remove();
		cilq.add("귤");
		cilq.add("포도");
		cilq.add("배");

		
		
	}

}
