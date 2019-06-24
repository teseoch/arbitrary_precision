////////////////////////////////////////////////////////////////////////////////
#include <catch.hpp>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////

#include <arbitraryprecision/fprecision.h>

using namespace arbitrary_precision;

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("10", "[test]")
{
	for (int n_digits = 10; n_digits <= 100; n_digits+=10)
	{
		float_precision num1(1., n_digits);
		float_precision num2(3., n_digits);

		auto res = num1 / num2 * float_precision(2., n_digits) - float_precision(2, n_digits) / float_precision(3., n_digits);
		const int prec = -log10(abs(res));
		std::cout << res << std::endl;
		std::cout << prec << std::endl;

		REQUIRE(res.precision() == n_digits);
		// REQUIRE(prec == n_digits);
	}
}
