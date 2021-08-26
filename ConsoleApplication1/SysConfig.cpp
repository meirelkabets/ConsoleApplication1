//Author : Meir Elkabets

#include "SysConfig.h"
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <sstream>
#include <iostream>

using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////
CSysConfig::CSysConfig(void)
{
	memset(m_azFullPath, 0, sizeof(m_azFullPath));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CSysConfig::~CSysConfig(void)
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool CSysConfig::Initialize(const char * pSysIniFileName)
{	
	string              sections;
	string              keys;
	string              section;
	string              key;
	vector<string>      vKeysValue;
	vector<string>      vSections;
	vector<string>      vKeys;
	unsigned long       count(0);
	char                auSectionsList[1024] = { 0 };
	char                auKeysList[1024]     = { 0 };
	map<string, string> mpKeysNameToValue;
		
	if (_fullpath(m_azFullPath, pSysIniFileName, 256) == NULL)
		return false;

	count = GetPrivateProfileSectionNames(auSectionsList, sizeof(auSectionsList), m_azFullPath);
	
	ReplaceNullDelimiter(auSectionsList, ";", count);
	sections.assign(auSectionsList);
	Split(sections, ';', IN OUT vSections); //Prepare sections vector.
	
	//Loop all sections vector.
	for (size_t i = 0; i < vSections.size(); i++)
	{
		memset(auKeysList, 0, sizeof(auKeysList));
		count = GetPrivateProfileSection(vSections[i].c_str(), auKeysList, sizeof(auKeysList), m_azFullPath);
		ReplaceNullDelimiter(auKeysList, ";", count);
		keys.assign(auKeysList);

		Split(keys, ';', IN OUT vKeys);
		mpKeysNameToValue.clear();
		
		//Loop all keys in the specific section.
		for (size_t ikey = 0; ikey < vKeys.size(); ikey++)
		{
			Split(vKeys[ikey], '=', vKeysValue);
			if (vKeysValue.size() == 2)
			{
				mpKeysNameToValue.insert(KeyValue_Pair(vKeysValue[0], vKeysValue[1]));
			}
		}
		m_mpSectionsNameToKeys.insert(SectionKeys_Pair(vSections[i], mpKeysNameToValue));
	}		
	
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
const string CSysConfig::GetString(const string section, const string key, OUT bool& status)
{
	string rv("");
	status = false;

	try
	{
		map<string, string> keys = m_mpSectionsNameToKeys.at(section);
		rv =  keys.at(key);
		status = true;
	}
	catch (const std::exception&)
	{

	}

	return rv;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
int CSysConfig::GetInt(const std::string section, const std::string key, OUT bool& status)
{
	string  rvs = GetString(section, key, status);
	int     rv  = atoi(rvs.c_str());
	return rv;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long CSysConfig::GetULong(const std::string section, const std::string key, OUT bool& status)
{
	string        rvs = GetString(section, key, status);
	unsigned long rv  = atol(rvs.c_str());
	return rv;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
double CSysConfig::GetDouble(const std::string section, const std::string key, OUT bool& status)
{
	string rvs = GetString(section, key, status);
	double rv  = atof(rvs.c_str());
	return rv;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
size_t CSysConfig::Split(std::string delimitedString, 
	                     const char delimiter, 
	                     OUT std::vector<std::string>& outVector)
{
	string itemValue;
	istringstream stream(delimitedString);

	outVector.clear();

	while (getline(stream, itemValue, delimiter))
	{
		outVector.push_back(itemValue);
	}
	return outVector.size();
}
