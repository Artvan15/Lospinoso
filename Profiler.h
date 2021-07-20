#pragma once

#include <string>
#include <chrono>
#include <iostream>

using namespace std;


class LogDuration
{
public:
	explicit LogDuration(const string& m = "")
		: msg(m), start(chrono::steady_clock::now()) {}

	~LogDuration()
	{
		auto finish = chrono::steady_clock::now();
		auto dur = finish - start;
		cerr << chrono::duration_cast<chrono::microseconds>(dur).count()
			<< " mic" << endl;
	}
private:
	string msg;
	chrono::steady_clock::time_point start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
	LogDuration UNIQ_ID(__LINE__)(message); //UNIQ_ID is unique in this cpp file