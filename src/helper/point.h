#pragma once
#include <functional>
#include <map>
#include <queue>

struct Point
{
	friend bool operator==(Point const& lhs, Point const& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	friend bool operator!=(Point const& lhs, Point const& rhs)
	{
		return !(lhs == rhs);
	}

	int x{};
	int y{};

	auto operator<(Point const& p) const
	{
		return x < p.x or (x == p.x and y < p.y);
	}
	auto operator+(Point const& other) const
	{
		return Point(x + other.x, y + other.y);
	}
	auto operator-(Point const& other) const
	{
		return Point(x - other.x, y - other.y);
	}

	[[nodiscard]] bool in_range(int x_max, int y_max) const
	{
		return (0 <= x and x <= x_max) and (0 <= y and y <= y_max);
	}

	int distance(Point const& other) const
	{
		return abs(x - other.x) + abs(y - other.y);
	}
};

namespace aoc::algorithm
{
template <typename T> class Graph
{
public:
	using AdjList    = std::map<Point, std::vector<Point>>;
	using Properties = std::map<Point, T>;
	using Path       = std::vector<Point>;

private:
	void
	    dfs(Path const&                             visited,
	        Point const&                            end,
	        std::function<void(Path const&)> const& end_call_back)
	{
		auto const curr = visited.back();
		if (curr == end)
		{
			end_call_back(visited);
			return;
		}

		for (auto const& next : _adjList.at(curr))
		{
			if (std::ranges::find(visited, next) != visited.end()) { continue; }
			auto next_visited = visited;
			next_visited.push_back(next);
			dfs(next_visited, end);
		}
	}

	void bfs(Point const s, Point const e)
	{
		std::map<Point, bool> visited =
		    _adjList | std::ranges::views::transform([](auto const& kv) {
			    return std::make_pair(kv.first, false);
		    }) |
		    std::ranges::to<std::map<Point, bool>>;

		bfs(s, e, visited);
	}

	void bfs(Point const& s, Point const& e, std::map<Point, bool>& visited)
	{
		std::queue<Point> q;

		visited[s] = true;
		q.push(s);

		while (!q.empty())
		{
			auto curr = q.front(); // Dequeue a vertex
			q.pop();

			for (auto x : _adjList.at(curr))
			{
				if (visited[x]) { continue; }
				visited[x] = true;
				q.push(x);
			}
		}
	}

	AdjList    _adjList;
	Properties _properties;
};

} // namespace aoc::algorithm