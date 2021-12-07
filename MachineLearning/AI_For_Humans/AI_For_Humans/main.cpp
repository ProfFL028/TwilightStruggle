#include <iostream>

using namespace std;



int main(int argv, char** args) {
	
	
	long addr = 0x0000000000001;
	long * memoryPoint = &addr;
	// 006FFB6C
	cout << *memoryPoint << endl;

	/**
	while (true) {
		if (!memoryPoint) {
			cout << memoryPoint << endl;
			break;
		}
		else {
			memoryPoint = (long*)(++addr);
			cout << "checking: " << addr << endl;
		}
	}
	*/

	system("pause");
	return 0;
}