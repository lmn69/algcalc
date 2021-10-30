// app.hpp - App
// -------------
// Main application module of the calculator.
// It displays the UI on a 2x16 LCD and can be controlled using the input() function.

#ifndef app_hpp
#define app_hpp

namespace App
{
	enum class InputType
	{
		left, right,
		d1, d2, d3, d4, d5, d6, d7, d8, d9,
		del, ret,
		add, sub, mul, div,
	};

	void init();
	void input(InputType inputtype);
}

#endif
