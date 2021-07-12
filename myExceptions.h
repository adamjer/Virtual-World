#pragma once
#include<string>


class Exception
{
public:
	Exception(std::string t)
	{
		this->text = t;
	}

	std::string text;
};


class RepeatException
{
public:
	RepeatException(std::string t)
	{
		this->text = t;
	}

	std::string text;
};