#pragma once
#include <vector>
#include <bits/streambuf_iterator.h>

template<typename T>
bool contains(std::vector<T> const& data, T const& item)
{
	return std::find(data.begin(), data.end(), item) != data.end();
}

template<typename T>
void add_to(std::vector<T> & data, T const& item)
{
	if (contains(data, item)) return;
	data.push_back(item);
}
