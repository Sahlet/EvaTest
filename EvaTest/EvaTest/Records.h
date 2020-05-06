#pragma once
#include <string>

namespace records
{
	struct CheckRow
	{
		std::wstring name;
		unsigned int priceForOne = 0;
		unsigned int count = 0;
		unsigned int sumDiscount = 0;
	};
} // namespace records