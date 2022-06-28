/*
//예제8-1
 #include <iostream>
#include <string>
using namespace std;

class Point { 
	int x, y; 
public:
	void set(int x, int y) { this->x = x; this->y = y; }
	void showPoint() {
		cout << "(" << x << "," << y << ")" << endl;
	}
};

class ColorPoint : public Point { 
	string color;
public:
	void setColor(string color)  {	this->color = color; }
	void showColorPoint();
};

void ColorPoint::showColorPoint() {
	cout << color << ":";
	showPoint(); 
}

int main() {
	Point p; 
	ColorPoint cp;
	cp.set(3,4); 
	cp.setColor("Red");
	cp.showColorPoint(); 
}
//예제8-2
#include <iostream>
#include <string>
using namespace std;

class Point { 
protected:
	int x, y;
public:
	void set(int x, int y) { this->x = x; this->y = y; }
	void showPoint() {
		cout << "(" << x << "," << y << ")" << endl;
	}
};

class ColorPoint : public Point {
	string color;
public:
	void setColor(string color)  {	this->color = color; }
	void showColorPoint();
	bool equals(ColorPoint p);
};

void ColorPoint::showColorPoint() {
	cout << color << ":";
	showPoint(); 
}

bool ColorPoint::equals(ColorPoint p) {
	if(x == p.x && y == p.y && color == p.color)	
		return true;
	else 
		return false;
}

int main() {
	Point p;	
	p.set(2,3);										
	p.x = 5;										
	p.y = 5;										
	p.showPoint();

	ColorPoint cp; 
	cp.x = 10;										
	cp.y = 10;										
	cp.set(3,4);
	cp.setColor("Red");

	ColorPoint cp2;
	cp2.set(3,4);
	cp2.setColor("Red");
	cout << ((cp.equals(cp2))?"true":"false");	
}
//예제8-3
#include <iostream>
#include <string>
using namespace std;

class  TV {
	int size; 
public:
	TV() { size = 20; }
	TV(int size) { this->size = size; }
	int getSize() { return size; }
};

class  WideTV : public TV { 
	bool videoIn;
public:
	WideTV(int size, bool videoIn) : TV(size) 	{ 
			this->videoIn = videoIn;
	}
	bool getVideoIn() { return videoIn; }
};

class  SmartTV : public WideTV { 
	string ipAddr; 
public:
	 SmartTV(string ipAddr, int size) : WideTV(size, true) { 
		 this->ipAddr = ipAddr;
	}
	 string getIpAddr() { return ipAddr; }
};

int main() {
	SmartTV  htv("192.0.0.1", 32);
	cout << "size=" << htv.getSize() << endl;
	cout << "videoIn=" << boolalpha << htv.getVideoIn() << endl;
	cout << "IP=" << htv.getIpAddr() << endl;
}
//예제8-4
#include <iostream>
using namespace std;

class Base {
	int a;
protected:
	void setA(int a) { this->a = a; }
public:
	void showA() { cout << a; }
};

class Derived : private Base {
	int b;
protected:
	void setB(int b) { this->b = b; }
public:
	void showB() { cout << b; }
};

int main() {
	Derived x;
	x.a = 5; 		
	x.setA(10);		
	x.showA(); 		
	x.b = 10; 		
	x.setB(10);		
	x.showB(); 		
} 
//예제8-5
#include <iostream>
using namespace std;

class Base {
	int a;
protected:
	void setA(int a) { this->a = a; }
public:
	void showA() { cout << a; }
};

class Derived : protected Base {
	int b;
protected:
	void setB(int b) { this->b = b; }
public:
	void showB() { cout << b; }
};

int main() {
	Derived x;
	x.a = 5; 		
	x.setA(10); 	
	x.showA();		
	x.b = 10; 	
	x.setB(10); 	
	x.showB(); 		
}
//예제8-6
#include <iostream>
using namespace std;

class Base {
	int a;
protected:
	void setA(int a) { this->a = a; }
public:
	void showA() { cout << a; }
};

class Derived : private Base {
	int b;
protected:
	void setB(int b) { this->b = b; }
public:
	void showB() {
		setA(5);
		showA(); 	
		cout << b;
	}
};

class GrandDerived : private Derived {
	int c;
protected:
	void setAB(int x) {
		setA(x); 		
		showA(); 		 
		setB(x); 		
	}
};
//예제8-7
#include <iostream>
using namespace std;

class Adder {
protected:
	int add(int a, int b) { return a+b; }
};

class Subtractor {
protected:
	int minus(int a, int b)  { return a-b; }
}
class Calculator : public Adder, public Subtractor { 
public:
	int calc(char op, int a, int b);
};

int Calculator::calc(char op, int a, int b) {
	int res=0;
	switch(op) {
		case '+' : res = add(a, b); break;
		case '-' : res = minus(a, b); break;
	}
	return res;
}

int main() {
	Calculator handCalculator;
	cout << "2 + 4 = " << handCalculator.calc('+', 2, 4) << endl;
	cout << "100 - 8 = " << handCalculator.calc('-', 100, 8) << endl;
}
//연습1
#include <iostream>
#include <string>
using namespace std;

class Circle {
	int radius;
public:
	Circle(int radius=0) { this->radius = radius; }
	int getRadius() { return radius; }
	void setRadius(int radius) { this->radius = radius; }
	double getArea() { return 3.14*radius*radius; };
};

class NamedCircle : public Circle {
	string name;
public:
	NamedCircle(int radius, string name);
	void show();
};

NamedCircle::NamedCircle(int radius, string name)
	: Circle(radius) {
	this->name = name;
}

void NamedCircle::show() {
	cout << "반지름이 " << getRadius() << "인 " << name << endl;
}

int main() {
	NamedCircle waffle(3, "waffle"); 
	waffle.show();
}
//연습3
#include <iostream>
#include <string>
using namespace std;

class Point { 
	int x, y;
public:
	Point(int x, int y) {
		this->x = x; this->y = y;
	}
	int getX() { return x; }
	int getY() { return y; }
protected:
	void move(int x, int y) { this->x = x; this->y = y; }
};

class ColorPoint : public Point {
	string color;
public:
	ColorPoint(int x, int y, string color)
		: Point(x, y) {
		this->color = color;
	}

	void setPoint(int x, int y) {
		move(x, y);
	}

	void setColor(string color) {
		this->color = color;
	}

	void show() {
		cout << color << "색으로 " << '(' << getX() << ',' << getY() << ')' << "에 위치한 점입니다." << endl;
	}
};

int main() {
	ColorPoint cp(5, 5, "RED");
	cp.setPoint(10, 20);
	cp.setColor("BLUE");
	cp.show();
}
//연습5
#include <iostream>
using namespace std;

class BaseArray {
private:
	int capacity; 
	int *mem;
protected:
	BaseArray(int capacity=100) {
		this->capacity = capacity; mem = new int [capacity];
	}
	~BaseArray() { delete [] mem; }
	void put(int index, int val) { mem[index] = val; }
	int get(int index) { return mem[index]; }
	int getCapacity() { return capacity; }
};

class MyQueue : public BaseArray {
	int head, tail;
	int size; 
public:
	MyQueue(int capacity);
	void enqueue(int n);
	int dequeue();
	int capacity();
	int length();
};

MyQueue::MyQueue(int capacity) : BaseArray(capacity) {
	head = 0; // 삽입할 위치는 head
	tail = -1;  
	size = 0; 

void MyQueue::enqueue(int n) {
	if(size == capacity())
		return; // queue full error
	put(head, n);
	head++;
	head = head % capacity();
	size++;
}

int MyQueue::dequeue() {
	if(size == 0)
		return -1; // queue empty error
	size--;
	tail++;
	tail = tail % capacity();
	return get(tail);
}

int MyQueue::capacity() {
	return getCapacity();
}

int MyQueue::length() {
	return size;
}

int main() {
	MyQueue mQ(100);
	int n;
	cout << "큐에 삽입할 5개의 정수를 입력하라>> ";
	for(int i=0; i<5; i++) {
		cin >> n;
		mQ.enqueue(n); // 큐에 삽입
	}
	cout << "큐의 용량:" << mQ.capacity() << ", 큐의 크기:" << mQ.length() << endl; 
	cout << "큐의 원소를 순서대로 제거하여 출력한다>> ";
	while(mQ.length() != 0) {
		cout << mQ.dequeue() << ' '; 
	}
	cout << endl << "큐의 현재 크기 : " << mQ.length() << endl;
}
//연습7 
#include <iostream>
using namespace std;

class BaseMemory {
	char *mem;
	int size;
protected:
	BaseMemory(int size) {
		mem = new char [size];
		this->size = size;
	}
	void load(char *mem, int address, int size) {
		if(address+size > this->size)
			return; // out of memory range
		for(int i=0; i<size; i++) 
			this->mem[address + i] = mem[i];
	}
public:
	char read(int address) {
		return mem[address];
	} 
};

class ROM : public BaseMemory {
public:
	ROM(int size, char* initData, int initSize);
};

ROM::ROM(int size, char* initData, int initSize)
	: BaseMemory(size)
{
	load(initData, 0, initSize); 
}

class RAM : public BaseMemory {
public:
	RAM(int size);
	void write(int address, char data);
};

RAM::RAM(int size) : BaseMemory(size) { }

void RAM::write(int address, char data) {
	load(&data, address, 1);
}

int main() {
	char x[5]={'h', 'e', 'l', 'l', 'o'};
	ROM biosROM(1024*10, x, 5); 
	RAM mainMemory(1024*1024); 
	for(int i=0; i<5; i++) mainMemory.write(i, biosROM.read(i)); 
	for(int i=0; i<5; i++) cout << mainMemory.read(i);
}
*/
