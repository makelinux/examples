#include <iostream>
#include <vector>
#include <string_view>
#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>

static_assert(__cplusplus >= 201707);


using namespace std;

/**
  https://en.cppreference.com/w/cpp/ranges
  https://en.cppreference.com/w/cpp/utility/source_location
  https://en.cppreference.com/w/cpp/language/coroutines
  */

int main()
{
	cout << __cplusplus << endl;
	assert(__cplusplus > 201703);
}
