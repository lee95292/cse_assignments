#include <iostream>
#include "GraphicEditor.h"
using namespace std;

int main() {
	cout << "그래픽 에디터입니다." << endl;
	GraphicEditor *editor = new GraphicEditor();
	delete editor;
}