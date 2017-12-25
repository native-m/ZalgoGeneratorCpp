#include "stdafx.h"
#include "ZalgoGen.h"

ZalgoGen::ZalgoGen()
{
	// Store all table length
	m_zalgoUpLen = sizeof(zalgoUp) / sizeof(wchar_t);
	m_zalgoDownLen = sizeof(zalgoDown) / sizeof(wchar_t);
	m_zalgoMidLen = sizeof(zalgoMid) / sizeof(wchar_t);
}

ZalgoGen::ZalgoGen(const std::wstring& string)
{
	m_str = string;
	// Store all table length
	m_zalgoUpLen = sizeof(zalgoUp) / sizeof(wchar_t);
	m_zalgoDownLen = sizeof(zalgoDown) / sizeof(wchar_t);
	m_zalgoMidLen = sizeof(zalgoMid) / sizeof(wchar_t);
}

ZalgoGen::~ZalgoGen()
{
}

// Set the string
void ZalgoGen::setString(const std::wstring & string)
{
	m_str = string;
}

// Set the seed for random number
void ZalgoGen::setRandomSeed(unsigned int seed)
{
	// Just make sure the seed is completely random!
	mrs.seed(seed);
	seed = seed ^ mrs() << 4;
	mrs.seed(seed);
	seed = seed ^ mrs() << 8;
	mrs.seed(seed);
}

// Get a random number
unsigned int ZalgoGen::getRandomNum(unsigned int max)
{
	setRandomSeed((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
	m_nextRand = mrs() % max;
	return m_nextRand;
}

// Get a randomized zalgo char from the char tables
wchar_t ZalgoGen::getZalgoChar(const wchar_t* arr, unsigned int n)
{
	setRandomSeed((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
	unsigned int index = (mrs() % n);
	return arr[index];
}

// Check if there is zalgo chars
bool ZalgoGen::isZalgoChar(wchar_t c)
{
	unsigned int i = 0;
	for (i = 0; i < m_zalgoUpLen; i++)
		if (c == zalgoUp[i])
			return true;
	for (i = 0; i < m_zalgoDownLen; i++)
		if (c == zalgoDown[i])
			return true;
	for (i = 0; i < m_zalgoMidLen; i++)
		if (c == zalgoMid[i])
			return true;
	return false;
}

// GENERATE THE ZALGO STRING
std::wstring ZalgoGen::generateString()
{
	// Prepare for string
	std::wstring ret = L"";
	// Get the string length from the original string
	int strLen = m_str.length();

	// For all original chars do
	for (int i = 0; i < strLen; i++)
	{
		// Check if there is zalgo chars
		if (isZalgoChar(m_str[i]))
			continue;

		// A variable to store the random number for each position
		unsigned int numUp;
		unsigned int numMid;
		unsigned int numDown;

		// Set the original string
		ret += m_str[i];

		// If there is a line feed or carriage return, we skip it
		if (m_str[i] == L'\r' || m_str[i] == L'\n')
			continue;

		// Apply the options
		if (m_optMini) // Mini or tiny chaos
		{
			numUp = getRandomNum(8);
			numMid = getRandomNum(2);
			numDown = getRandomNum(8);
		}
		else if (m_optNormal) // normal chaos
		{
			numUp = getRandomNum(16) / 2 + 1;
			numMid = getRandomNum(6) / 2;
			numDown = getRandomNum(16) / 2 + 1;
		}
		else if (m_optMaxi) // huge chaos
		{
			numUp = getRandomNum(64) / 4 + 3;
			numMid = getRandomNum(16) / 4 + 1;
			numDown = getRandomNum(64) / 4 + 3;
		}

		// Apply the chaos
		if (m_optUp)
			for (unsigned int j = 0; j < numUp; j++)
				ret += getZalgoChar(zalgoUp, m_zalgoUpLen);
		if (m_optMid)
			for (unsigned int j = 0; j < numMid; j++)
				ret += getZalgoChar(zalgoMid, m_zalgoMidLen);
		if (m_optDown)
			for (unsigned int j = 0; j < numDown; j++)
				ret += getZalgoChar(zalgoDown, m_zalgoDownLen);
	}

	return ret;
}

void ZalgoGen::setOptionIgnoreSpace(bool truth)
{
	m_optIgnoreSpace = truth;
}

void ZalgoGen::setOptionUp(bool truth)
{
	m_optUp = truth;
}

void ZalgoGen::setOptionMid(bool truth)
{
	m_optMid = truth;
}

void ZalgoGen::setOptionDown(bool truth)
{
	m_optDown = truth;
}

void ZalgoGen::setOptionMode(int mode)
{
	switch (mode)
	{
	case 0:
		m_optMini = true;
		m_optNormal = false;
		m_optMaxi = false;
		break;
	case 1:
		m_optMini = false;
		m_optNormal = true;
		m_optMaxi = false;
		break;
	case 2:
		m_optMini = false;
		m_optNormal = false;
		m_optMaxi = true;
		break;
	default:
		m_optMini = true;
		m_optNormal = false;
		m_optMaxi = false;
		break;
	}
}

void ZalgoGen::resetOptions()
{
	setOptionMode(0);
	setOptionUp(false);
	setOptionMid(true);
	setOptionDown(true);
}
