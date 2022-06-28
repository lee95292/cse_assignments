package queue;

public class LinkedQueue {

	private node front;
	private node reer;
	private node tmpNode;
	LinkedQueue()
	{
		front=null;
		reer=null;
	}
	public void add(String data)
	{
		if(front==null)
		{
			front=new node(data);
			reer=front;
			front.next=reer;
		}
		else
		{		
			tmpNode=reer;
			reer=new node(data);
			tmpNode.next=reer;
		}
		System.out.println(reer.data+"(입력)");
	}
	public void remove()
	{
		if(front==null)
		{
			System.out.println("Queue empty.");
			return;
		}
		else
		{
			System.out.println(front.data+" removed");
			front=front.next;
		}
	}
	public void empty()
	{
		front=null;
		reer=null;
	}
	public void peek()
	{
		if(front==null)
		{
			System.out.println("queue empty");
			return;
		}
		else
		{
			System.out.println(reer.data);
		}
	}
	class node
	{
		node next;
		String data;
		node(String data)
		{
			this.data=data;
			next=null;
		}
	}
	public static void main(String[] args) {
		LinkedQueue liqu = new LinkedQueue();
		liqu.add("사과");
		liqu.add("감");
		liqu.remove();
		liqu.remove();
		liqu.add("귤");
		liqu.add("포도");
		liqu.add("배");
	}

}
