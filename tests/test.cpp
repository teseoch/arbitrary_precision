////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cassert>
////////////////////////////////////////////////////////////////////////////////

#include <arbitraryprecision/fprecision.h>

using namespace arbitrary_precision;

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	for (int n_digits = 10; n_digits <= 100; n_digits+=10)
	{
		float_precision num1(1., n_digits);
		float_precision num2(3., n_digits);

		auto res = num1 / num2 * float_precision(2., n_digits) - float_precision(2, n_digits) / float_precision(3., n_digits);
		const int prec = -log10(abs(res));
		std::cout << res << std::endl;
		std::cout << prec << std::endl;

		assert(res.precision() == n_digits);
		assert(prec == n_digits);
	}

	return EXIT_SUCCESS;
}
