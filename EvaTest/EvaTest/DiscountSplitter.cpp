#include "DiscountSplitter.h"

namespace {
	template<class T>
	T min(const T& l, const T& r)
	{
		return l < r ? l : r;
	}

	std::list<records::CheckRow> split(const records::CheckRow& row)
	{
		if ((row.sumDiscount % row.count) == 0)
		{
			return { row };
		}

		records::CheckRow part1 = row;
		records::CheckRow part2 = row;

		part2.count = 0;
		part2.sumDiscount = 0;

		do {
			part1.count--;
			part2.count++;
			auto rest = row.sumDiscount % part1.count;
			part1.sumDiscount = min(row.sumDiscount - rest, part1.count * row.priceForOne);
			part2.sumDiscount = row.sumDiscount - part1.sumDiscount;
		} while (part2.sumDiscount > (part2.count * row.priceForOne));

		auto res = split(part2);

		res.emplace_front(std::move(part1));

		return std::move(res);
	}
} // namespace

std::list<records::CheckRow> splitByDiscount(const std::list<records::CheckRow>& check)
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

	std::list<records::CheckRow> res;

	for (auto& row : check)
	{
		auto splittedRow = split(row);
		res.insert(res.end(), splittedRow.begin(), splittedRow.end());
	}

	return std::move(res);
}