package stack;

public class linkedStack {
	private node headNode;	//시작 Node
	private node tailNode;  //마지막 Node
	private node tmpNode;   //마지막 바로 이전 Node
	
	linkedStack(){
		headNode=null;
	}
	
	public void pop(){
		if(tailNode==null)
		{
			System.out.println("stack empty");
			return;
		}else
		{			
			System.out.println(tailNode.data+"(출력)");
			tailNode=tmpNode;
		}
	}
	public void push(String data){
		if(headNode==null) {
			headNode=new node(data);
			tmpNode=headNode;
			tailNode=headNode;
			tmpNode.next=tailNode;
		}
		else { 
			tmpNode = tailNode;
			tailNode= new node(data);
			tmpNode.next=tailNode;
		}
		System.out.println(data+"(입력)");
		
	}
	
	public void peek()
	{
		if(tailNode==null)
		{
			System.out.println("stack empty");
		}
	}
	public void peekAll(){		//stack 내용 유지하면서 출력
		node tmp=headNode;
		while(tmp!=null)
		{
			System.out.println(tmp.data);
			tmp=tmp.next;
		}
	}
	public void peek2()  		//stack 내용 empty하고 출력
	{
		peekAll();
		empty();
	}
	public void empty()
	{
		headNode=null;
		tmpNode=null;
		tailNode=null;
	}
	class node
	{
		private node next;
		private String data;
		node(String data)
		{
			next=null;
			this.data=data;
		}
		
	}
	
	public static void main(String[] args) {
		linkedStack ls = new linkedStack();
		
		ls.push("사과");
		ls.push("감");
		ls.push("귤");
		ls.push("포도");
		System.out.println("--pop--");
		ls.pop();
		ls.pop();
		ls.pop();
		ls.pop();
		
		
	}

}
