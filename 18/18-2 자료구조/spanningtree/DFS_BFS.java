package dfsbfs;

import java.util.LinkedList;

public class DFS_BFS {
	
	LinkedList<node> bfsq;
	public DFS_BFS() {
		bfsq= new LinkedList<node>();
	}
	public void doDFS(node n)
	{
		n.setVisited(true);		//visited = true
		System.out.println("Node "+n.getValue()+" is visited");
		for(int i=0;i<n.adjlist.size();i++)
		{
			node currNode=n.adjlist.get(i);
			if(currNode.isVisited()==false)
			{
				doDFS(currNode);
			}
		}
	}
	
	public void doBFS(node n)
	{
		n.setVisited(true);
		System.out.println("Node "+n.getValue()+" is visited");
		
		for(int i=0;i<n.adjlist.size();i++)
		{
			node currNode = n.adjlist.get(i);
			if(currNode.isVisited()==false)
				bfsq.add(currNode);
		}
		if(bfsq.peek()!=null&&bfsq.peek().isVisited()==false)
			doBFS(bfsq.poll());
		else
			return;
	}
	
	public static void main(String args[])
	{
		DFS_BFS d = new DFS_BFS();
		node[] nlist = new node[9];
		for(int i=1;i<=8;i++)
		{
			nlist[i] = new node("V"+i);
		}
		
		/*drawing adjacent list
			1 >> 2 , 3
			2 >> 1 , 4 , 5
			3 >> 1 , 6 , 7
			4 >> 2 , 8 
			5 >> 2 , 8
			6 >> 3 , 8
			7 >> 3 , 8
			8 >> 4 , 5 , 6 , 7
		*/
		
		nlist[1].setAdjList(nlist[2]);
		nlist[1].setAdjList(nlist[3]);
		nlist[2].setAdjList(nlist[1]);
		nlist[2].setAdjList(nlist[4]);
		nlist[2].setAdjList(nlist[5]);
		nlist[3].setAdjList(nlist[1]);
		nlist[3].setAdjList(nlist[6]);
		nlist[3].setAdjList(nlist[7]);
		nlist[4].setAdjList(nlist[2]);
		nlist[4].setAdjList(nlist[8]);
		nlist[5].setAdjList(nlist[2]);
		nlist[5].setAdjList(nlist[8]);
		nlist[6].setAdjList(nlist[3]);
		nlist[6].setAdjList(nlist[8]);
		nlist[7].setAdjList(nlist[3]);
		nlist[7].setAdjList(nlist[7]);
		nlist[8].setAdjList(nlist[4]);
		nlist[8].setAdjList(nlist[5]);
		nlist[8].setAdjList(nlist[6]);
		nlist[8].setAdjList(nlist[7]);
		
		System.out.println("DFS Spanning Tree");
		d.doDFS(nlist[1]);
		
		for(int i=1; i<9;i++)
		{
			nlist[i].setVisited(false);
		}
		System.out.println("\n\nBFS Spanning Tree");
		d.doBFS(nlist[1]);
		
		
	}
}
