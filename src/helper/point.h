#pragma once


struct Point
{
	friend bool operator==(const Point& lhs, const Point& rhs)
	{
		return lhs.x == rhs.x
		       && lhs.y == rhs.y;
	}

	friend bool operator!=(const Point& lhs, const Point& rhs)
	{
		return !(lhs == rhs);
	}

	int x;
	int y;

	auto operator<(const Point& p) const
	{
		return
			x < p.x or (x == p.x and y < p.y);
	}
	auto operator+ (Point const& other) const
	{
		return Point(x + other.x, y + other.y);
	}
	auto operator- (Point const& other) const
	{
		return Point(x - other.x, y - other.y);
	}

	[[nodiscard]] bool in_range(int x_max, int y_max) const
	{
		return (0 <= x and x <= x_max) and (0 <= y and y <= y_max);
	}
};