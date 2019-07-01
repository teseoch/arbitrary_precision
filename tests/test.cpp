////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cassert>
////////////////////////////////////////////////////////////////////////////////

#include <arbitraryprecision/iprecision.h>
#include <arbitraryprecision/fprecision.h>
#include <arbitraryprecision/complexprecision.h>
#include <arbitraryprecision/intervalprecision.h>

using namespace arbitrary_precision;

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	for (int n_digits = 10; n_digits <= 100; n_digits += 10)
	{
		float_precision num1(1., n_digits);
		float_precision num2(3., n_digits);

		float_precision res(0, n_digits);

		res = num1 / num2 * float_precision(2., n_digits) - float_precision(2, n_digits) / float_precision(3., n_digits);
		const int prec = -log10(abs(res));
		std::cout << res << " " << res.precision() << std::endl;
		std::cout << prec << std::endl;

		assert(res.precision() == n_digits);
		assert(prec == n_digits);
	}

	{
		int_precision tmp;
	}

	{
		complex_precision<float_precision> tmp;
	}

	{
		interval<float_precision> tmp;
	}
	return EXIT_SUCCESS;
}
