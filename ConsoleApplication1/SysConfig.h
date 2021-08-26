//Author : Meir Elkabets

#pragma once

#include <map>
#include <vector>

#ifndef OUT
#define OUT
#endif

typedef std::pair <std::string, std::string> KeyValue_Pair;
typedef std::pair <std::string, std::map<std::string, std::string>> SectionKeys_Pair;

class CSysConfig
{

public:
	 CSysConfig(void);
	~CSysConfig(void);

public:
	bool Initialize(const char *pSysIniFileName);

	const std::string GetString(const std::string section, const std::string key, OUT bool& status );
	int               GetInt   (const std::string section, const std::string key, OUT bool& status);
	unsigned long     GetULong (const std::string section, const std::string key, OUT bool& status);
	double            GetDouble(const std::string section, const std::string key, OUT bool& status);


private:
	//src is IN OUT input
	inline void ReplaceNullDelimiter(char *src, const char *newDelimiter, unsigned long srcLenght)
	{
		for (unsigned long  i = 0; i < srcLenght; i++)
		{
			if (src[i] == '\0')
				src[i] = ';';
		}
	}

	size_t Split(std::string delimitedString,  const char delimiter, OUT std::vector<std::string> &outVector);
	
private:
	char m_azFullPath[512];	
	std::map<std::string, std::map<std::string, std::string>> m_mpSectionsNameToKeys;	
};

