#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>


using namespace std;


template<typename Iterator>
struct RangeIterator
{
	Iterator first, last;

	Iterator begin() { return first; }
	Iterator end() { return last; }
};

template<typename T>
RangeIterator<typename vector<T>::iterator>
	Head(vector<T>& vec, size_t i)
{
	return { vec.begin(), next(vec.begin(), min(i, vec.size())) };
}


template<typename T>
class Table
{
public:
	Table(size_t line, size_t column)
	{
		Resize(line, column);
	}

	vector<T>& operator[](size_t ind)
	{
		return table.at(ind);
	}
	
	const vector<T>& operator[](size_t ind) const
	{
		return table.at(ind);
	}

	void Resize(size_t line, size_t column)
	{
		if(line == 0 || column == 0)
		{
			table.clear();
			return;
		}
		table.resize(line);
		for (auto& l : table)
		{
			l.resize(column);
		}
	}

	pair<size_t, size_t> Size() const
	{
		return { table.size(), (table.empty()) ? 0 : table.at(0).size() };
	}
	
private:
	vector<vector<T>> table;
};

int main()
{
	Table<int> t(1, 1);
	cout << t.Size().first << ' ' << t.Size().second << endl;
	t[0][0] = 42;
	cout << t[0][0] << endl;
	t.Resize(3, 4);
	cout << t.Size().first << ' ' << t.Size().second << endl;

	Table <int> t1(0, 2);
	cout << t1.Size().first << ' ' << t1.Size().second << endl;

	cout << "GitTest!!!" << endl;
	
}

