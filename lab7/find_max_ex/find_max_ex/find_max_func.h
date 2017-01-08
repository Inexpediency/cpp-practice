#pragma once

template < typename T, typename Less = std::less<T>>
bool FindMax(const std::vector<T> & arr, T & maxValue, const Less & less = Less())
{
	if (arr.empty())
	{
		return false;
	}
	maxValue = *arr.begin();
	for (const T & el : arr)
	{
		if (less(el, maxValue))
		{
			maxValue = el;
		}
	}
	return true;
}
