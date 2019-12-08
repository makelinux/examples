#include <iostream>
#include <cassert>

using namespace std;

int main()
{
	cout << __cplusplus << endl;
	assert(__cplusplus > 201703);
}
