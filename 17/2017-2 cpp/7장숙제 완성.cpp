/*

//예제 1
#include <iostream>
using namespace std;

class Rect; 
bool equals(Rect r, Rect s); 

class Rect { // Rect 클래스 선언
	int width, height;
public:
	Rect(int width, int height)  { 	this->width = width; this->height = height;	}
	friend bool equals(Rect r, Rect s); 
};

bool equals(Rect r, Rect s) { 
	if(r.width == s.width && r.height == s.height) return true; 
	else return false;
}

int main() {
	Rect a(3,4), b(4,5);
	if(equals(a, b)) cout << "equal" << endl;
	else cout << "not equal" << endl;
}
//예제 2
#include <iostream>
using namespace std;

class Rect; 

class RectManager { 
public:
	bool equals(Rect r, Rect s);
};

class Rect { // Rect 클래스 선언
	int width, height;
public:
	Rect(int width, int height) { this->width = width; this->height = height; }
	friend bool RectManager::equals(Rect r, Rect s); 
};

bool RectManager::equals(Rect r, Rect s) {
	if(r.width == s.width && r.height == s.height) return true; 
	else return false;
}

int main() {
	Rect a(3,4), b(3,4);
	RectManager man;
	
	if(man.equals(a, b)) cout << "equal" << endl;
	else cout << "not equal" << endl;
}
//예제 3
#include <iostream>
using namespace std;

class Rect;

class RectManager { 
public:
	bool equals(Rect r, Rect s);
	void copy(Rect& dest, Rect& src);
};

class Rect { 
	int width, height;
public:
	Rect(int width, int height)  { this->width = width; this->height = height; }
	friend RectManager; 
};

bool RectManager::equals(Rect r, Rect s) { // r과 s가 같으면 true 리턴
	if(r.width == s.width && r.height == s.height) return true; 
	else return false;
}

void RectManager::copy(Rect& dest, Rect& src) {
	dest.width = src.width;  dest.height = src.height;
}

int main() {
	Rect a(3,4), b(5,6);
	RectManager man;
	
	man.copy(b, a); 
	if(man.equals(a, b)) cout << "equal" << endl;
	else cout << "not equal" << endl;
}
//예제 4
#include <iostream>
using namespace std;

class Power {
	int kick;
	int punch;
public:
	Power(int kick=0, int punch=0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	Power operator+ (Power op2);
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

Power Power::operator+(Power op2) { 
	Power tmp; // 임시 객체 생성
	tmp.kick = this->kick + op2.kick; 
	tmp.punch = this->punch + op2.punch; 
	return tmp; // 더한 결과 리턴
}

int main() {
	Power a(3,5), b(4,6), c;
	c = a + b; 
	a.show();
	b.show();
	c.show();
}
//예제 5
#include <iostream>
using namespace std;

class Power {
	int kick;
	int punch;
public:
	Power(int kick=0, int punch=0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	bool operator== (Power op2);  
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

bool Power::operator==(Power op2) {
	if(kick==op2.kick && punch==op2.punch) return true;
	else return false;
}

int main() {
	Power a(3,5), b(3,5); 
	a.show();
	b.show();
	if(a == b) cout << "두 파워가 같다." << endl;
	else cout << "두 파워가 같지 않다." << endl;
}
//예제 6
#include <iostream>
using namespace std;

class Power {
	int kick; 
	int punch; 
public:
	Power(int kick=0, int punch=0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	Power operator+= (Power op2); 
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

Power Power::operator+=(Power op2) {
	kick = kick + op2.kick; 
	punch = punch + op2.punch;
	return *this; 
}

int main() {
	Power a(3,5), b(4,6), c;
	a.show();
	b.show();
	c = a += b; 
	a.show();
	c.show();
}
//예제 7
#include <iostream>
using namespace std;

class Power {
	int kick; 
	int punch; 
public:
	Power(int kick=0, int punch=0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	Power operator+ (int op2); 
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

Power Power::operator+(int op2) {
	Power tmp; // 임시 객체 생성
	tmp.kick = kick + op2;
	tmp.punch = punch + op2; 
	return tmp; 
}

int main() {
	Power a(3,5), b;
	a.show();
	b.show();
	b = a + 2; 
	a.show();
	b.show();
}
//예제 8
#include <iostream>
using namespace std;

class Power {
	int kick;
	int punch; 
public:
	Power(int kick=0, int punch=0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	Power operator++ (); 
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

Power Power::operator++() {
	kick++;
	punch++;
	return *this; 
}

int main() {
	Power a(3,5), b;
	a.show();
	b.show();
	b = ++a; 
	a.show();
	b.show();
}
//예제 9
#include <iostream>
using namespace std;

class Power {
	int kick;
	int punch; 
public:
	Power(int kick=0, int punch=0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	bool operator! (); 
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

bool Power::operator!() {
	if(kick == 0 && punch == 0) return true;
	else return false;
}

int main() {
	Power a(0,0), b(5,5);
	if(!a) cout << "a의 파워가 0이다."  << endl; 
	else cout << "a의 파워가 0이 아니다." << endl;
	if(!b) cout << "b의 파워가 0이다." << endl;
	else cout << "b의 파워가 0이 아니다." << endl;
}
//예제 10 
#include <iostream>
using namespace std;

class Power {
	int kick; 
	int punch; 
public:
	Power(int kick=0, int punch=0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	Power operator++ (int x); 
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

Power Power::operator++(int x) {
	Power tmp = *this; 
	kick++;
	punch++;
	return tmp; 
}

int main() {
	Power a(3,5), b;
	a.show();
	b.show();
	b = a++; 
	a.show(); 
	b.show(); 
}

//예제 11
#include <iostream>
using namespace std;

class Power {
	int kick; 
	int punch; 
public:
	Power(int kick=0, int punch=0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	friend Power operator+(int op1, Power op2); 
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

Power operator+(int op1, Power op2) {
	Power tmp; // 임시 객체 생성
	tmp.kick = op1 + op2.kick;
	tmp.punch = op1 + op2.punch; 
	return tmp; // 임시 객체 리턴
}

int main() {
	Power a(3,5), b;
	a.show();
	b.show();
	b = 2 + a; 
	a.show();
	b.show();
}
//예제 12
#include <iostream>
using namespace std;

class Power {
	int kick;
	int punch;
public:
	Power(int kick=0, int punch=0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	friend Power operator+(Power op1, Power op2); 
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

Power operator+(Power op1, Power op2) {
	Power tmp; // 임시 객체 생성
	tmp.kick = op1.kick + op2.kick; 
	tmp.punch = op1.punch + op2.punch; 
	return tmp; // 임시 객체 리턴
}

int main() {
	Power a(3,5), b(4,6), c;
	c = a + b; // 파워 객체 더하기 연산
	a.show();
	b.show();
	c.show();
}
//예제 13 
#include <iostream>
using namespace std;

class Power {
	int kick; 
	int punch;
public:
	Power(int kick=0, int punch=0) { this->kick = kick; this->punch = punch; }
	void show();
	friend Power operator++(Power& op); 
	friend Power operator++(Power& op, int x); 
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

Power operator++(Power& op) { 
	op.kick++;
	op.punch++;
	return op; // 연산 결과 리턴
}

Power operator++(Power& op, int x) { 
	Power tmp = op; 
	op.kick++;
	op.punch++;
	return tmp; 
}

int main() {
	Power a(3,5), b;
	b = ++a;
	a.show(); 	b.show();

	b = a++; 
	a.show(); 	b.show();
}
/
//연습문제 1

#include<iostream>
using namespace std;

class Book{
	int page;
	int price;
	string title;
public:
	Book(string title,int price,int page)
	{this->title=title;this->page=page;this->price=price;}
	void operator +=(int price)
	{this->price+=price;}
	
	void operator -=(int price)
	{this->price-=price;}
	void show()
	{cout<<title<<' '<<price<<"원 "<<page<<" 페이지"<<endl; }
}; 

int main()
{
	Book a("청춘",20000,300),b("미래",30000,500);
	a+=500;a.show(); 
	b-=500;b.show();
}

//연습문제 2 


#include<iostream>
using namespace std;

class Book{
	int page;
	int price;
	string title;
public:
	Book(string title,int price,int page)
	{this->title=title;this->page=page;this->price=price;}
	
	bool operator ==(Book op2)
	{if(this->price==op2.price&&this->page==page&&this->title==title)return true;
		else return false;}
	
	void show()
	{cout<<title<<' '<<price<<"원 "<<page<<" 페이지"<<endl; }
}; 

int main()
{
	Book a("명훔 C++",30000,500),b("고품 C++",30000,500);
	if(a==30000)cout<<"정가 30000"<<endl;
	if(a=="명품 C++")cout<<"명품 C++ 입니다"<<endl;

}

//연습문제 5

#include<iostream>
using namespace std;    

class Matrix{
int a,b,c,d;
public:
	Matrix(int a=3,int b=5,int c=7,int d=9){
		this->a=a;this->b=b;this->c=c;this->d=d;
	}
	Matrix operator +(Matrix q)
	{
		Matrix tmp;
		
		tmp.a=this->a+q.a;
		tmp.b=this->b+q.b;
		tmp.c=this->c+q.c;
		tmp.d=this->d+q.d;

		return tmp;
	}
	
	void operator +=(Matrix q){
		a=a+q.a;b=b+q.b;
		c=c+q.c;d=d+q.d;
	}
	
	bool operator ==(Matrix q)
	{
		if(a==q.a&&b==q.b&&c==q.c&&d==q.d)return true;
		else return false;
	}
	void show()
	{
		cout<<"Martix= { "<<a<<' '<<b<<' '<<c<<' '<<d<<" }"<<endl;
	}
}; 

int main()
{
	Matrix a(1,2,3,4),b(2,3,4,5),c;
	
	c=a+b;
	a+=b;
	a.show();b.show();c.show();
	
	if(a==c)
	cout<<"a and c are smae"<<endl;
}

//연습문제 6

#include<iostream>
using namespace std;
#include <iostream>

using namespace std;

 

class Matrix {
    int duo[4];
public :
    Matrix(int a=0, int b=0, int c=0, int d=0) {
        duo[0] = a; duo[1] = b;
        duo[2] = c; duo[3] = d;
    }
    void operator >>(int n[]) {
        for(int i=0; i<4; i++)
            n[i] = duo[i];
	}
    void operator << (int n[]) {
        for(int i=0; i<4; i++)
            duo[i] = n[i];
    }
    void show() {
        cout << "Matrix = { ";
        for(int i=0; i<4; i++) {
                cout << duo[i] << ' ';
       }
        cout << '}' << endl;
    }
};

 
int main() {
    Matrix a(4,3,2,1), b;
    int x[4], y[4] = {1,2,3,4};
    a >> x;
    b << y;
    for(int i=0; i<4; i++) cout << x[i] << ' ';
    cout << endl;
   b.show();
}

//연습 7
#include<iostream>
using namespace std;

class Circle{
      int radius;
public:
      Circle(int radius = 0){ this->radius = radius; }
      void show(){ cout << "radius = " << radius << "인 원" << endl; }
      friend Circle operator++(Circle& c);  //전위 ++ 연산자
      friend Circle operator++(Circle& c, int x);  //후위 ++ 연산자
};

Circle operator++(Circle& c){
      c.radius++;
      return c;

Circle operator++(Circle& c, int x){
      Circle tmp = c;
      c.radius++;
      return tmp;
}
int main(){
      Circle a(5), b(4);
      ++a;
      b = a++;
      a.show();
      b.show();
}
*/
//연습문제 9
#include<iostream>
using namespace std;

class Statistics{
      int *num;
      int count;
public:
      Statistics(){ num = new int[10]; count = 0; }
      ~Statistics(){ delete[] num; }
      bool operator!();
      Statistics& operator<<(int n);
      void operator>>(int & n);
      void operator~();
};

bool Statistics::operator!(){
      if (num == NULL) return false;
      else return true;
}

Statistics& Statistics::operator<<(int n){
      num[count] = n;
      count++;
      return *this;
}

void Statistics::operator>>(int & n){
      int sum = 0;
      for (int i = 0; i < count; i++)
            sum += num[i];
      n = sum / count;
}
void Statistics::operator~(){
      for (int i = 0; i < count; i++)
            cout << num[i] << " ";
      cout << endl;
}
int main(){
      Statistics stat;
      if (!stat) cout << "현재 통계 데이터가 없습니다." << endl;
 
      int x[5];
      cout << "5 개의 정수를 입력하라>>";
      for (int i = 0; i < 5; i++) cin >> x[i];
      for (int i = 0; i < 5; i++) stat << x[i];
      stat << 100 << 200;
      ~stat;
 
      int avg;
      stat >> avg;
      cout << "avg = " << avg << endl;
}
 



