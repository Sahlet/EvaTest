#include "DiscountSplitter.h"

void splitByDiscount(std::list<records::CheckRow>& check)
{
	for (auto& row : check)
	{
		if (row.count == 0)
		{
			throw std::exception("the count is 0");
		}

		if (row.priceForOne == 0)
		{
			throw std::exception("the price is 0");
		}

		if (row.count * row.priceForOne < row.sumDiscount)
		{
			throw std::exception("discount is greater than price");
		}
	}


}