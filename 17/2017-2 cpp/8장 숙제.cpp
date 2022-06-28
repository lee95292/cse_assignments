#include<iostream>
using namespace std;

class BaseMemory{
	char* mem;
protected:
	BaseMemory(int size){mem=new char[size];}
};

class ROM :private BaseMemory{
	void burn(){
		cout<<"burn this cd..."<<endl;}
	public:
		ROM(int size,int a[],int asize)
		{
			BaseMemory(size);
			for(int i=0;i<asize;i++)
				mem[i]=a[i];
		}
		void write(int i,char a)
		{
			mem[i]=a;
		}
		void read(int i)
		{
			cout<<mem[i];	
		}
};

class RAM : private BaseMemory{
	
	public:
		RAM(int siz)
		{
			BaseMemory(siz);
		}
		
		void write(int n,char a){
			mem[n]=a;
		}
		
		void read(int i)
		{
			cout<<mem[i];
		}
	
};

int main()
{
	BaseMemory a(10);
	char x[5]={'h','e','l','l','o'};
	ROM biosROM(1024*10,x,5);
	RAM mainMemory(1024*1024);
	
	for(int i=0;i<5;i++)mainMemory. 
}
