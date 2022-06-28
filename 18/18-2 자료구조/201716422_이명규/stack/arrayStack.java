package stack;

public class arrayStack {
	private final static int STACK_SIZE = 100;
	
	private String[] stack;
	private int top;
	
	arrayStack()
	{
		stack=new String[STACK_SIZE];
		top=-1;
	}
	public void push(String data)
	{
		if(top>STACK_SIZE-2)
			System.out.println("Stack full.");
		else
		{
			stack[++top]=data;
			System.out.println(data+"(입력)");
		}
	}
	public void  pop()
	{
		if(top>=0)
		{
			System.out.println(stack[top--]+"(출력)");
			
		}
		else
		{
			System.out.println("stack empty.");
		}
	}
	public void peek()
	{
		if(!(top==0))
			System.out.println(stack[top]);
	}
	public void peek1()
	{
		int i;
		for(i=0;i<=top;i++)
		{
			System.out.print(stack[i]+" ");
		}System.out.println("");
	}
	public void empty()
	{
		top=-1;
	}
	
	public void printEmpty()
	{
		peek1();
		empty();
	}
	public static void main(String[] args) {
		arrayStack arst=new arrayStack();
		arst.push("사과");
		arst.push("감");
		arst.push("귤");
		arst.push("포도");
		System.out.println("--pop--");
		arst.pop();
		arst.pop();
		arst.pop();
		arst.pop();
		System.out.println("Question 2.");
		arst.push("사과");
		arst.push("감");
		arst.push("귤");
		arst.push("포도");
		System.out.println("b) 출력 후 stack 내용 유지");
		arst.peek1();
		System.out.println("a) 출력 후 stack empty");
		arst.printEmpty();
		arst.pop();
		
		
	}

}
