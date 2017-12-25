#pragma once

#include <string>
#include <cstdio>
#include <cwctype>
#include <random>
#include <chrono>
#include "ZalgoChar.h"

class ZalgoGen
{
private:
	// VARIABLES
	std::wstring m_str;
	unsigned int m_zalgoUpLen;
	unsigned int m_zalgoDownLen;
	unsigned int m_zalgoMidLen;
	unsigned int m_nextRand;

	// options
	bool m_optIgnoreSpace = false;
	bool m_optMini = true;
	bool m_optNormal = false;
	bool m_optMaxi = false;
	bool m_optUp = false;
	bool m_optMid = true;
	bool m_optDown = true;
	std::mt19937 mrs;

public:
	ZalgoGen();
	ZalgoGen(const std::wstring& string);
	~ZalgoGen();

	void setString(const std::wstring& string);
	void setRandomSeed(unsigned int seed);
	unsigned int getRandomNum(unsigned int max);
	wchar_t getZalgoChar(const wchar_t* arr, unsigned int n);
	bool isZalgoChar(wchar_t c);
	std::wstring generateString();

	void setOptionIgnoreSpace(bool truth);
	void setOptionUp(bool truth);
	void setOptionMid(bool truth);
	void setOptionDown(bool truth);
	void setOptionMode(int mode);
	void resetOptions();
};