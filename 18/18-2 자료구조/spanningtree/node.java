package dfsbfs;

import java.util.LinkedList;

class node {
	private String value;
	private boolean visited;
	LinkedList<node> adjlist;
	node(String str)
	{
		value = str;
		visited=false;
		adjlist = new LinkedList<node>();
	}
	
	public void visit()
	{
		this.visited=true;
	}
	
	public String getValue()
	{
		return value;
	}
	
	public LinkedList<node> getAdjList()
	{
		return adjlist;
	}
	public void setAdjList(node n)
	{
		adjlist.addLast(n);
	}
	
	public boolean isVisited()
	{
		return visited;
	}
	
	public void setVisited(boolean b)
	{
		this.visited=b;
	}
}
