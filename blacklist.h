#ifndef _BLACKLIST_H_
#define _BLACKLIST_H_

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Blacklist
{
private:
	vector<string> blacklist;
	
public:
	Blacklist()
	{
		TCHAR buffer[255];
		GetModuleFileName( NULL, buffer, 255 );
		string exe = buffer;
		
		size_t found = exe.find_last_of("\\");
		if( found != string::npos)
			exe = exe.substr(0, found);
		
		string list = exe + "\\blacklist.txt";
		
		ifstream is (list.c_str());
		if (is.is_open())
	    {
	    	string line;
		    while ( getline (is,line) )
		    {
		    	if( line.empty() )
		    		continue;
		    		
				std::transform(line.begin(), line.end(), line.begin(), ::tolower);
		        blacklist.push_back(line);
		    }
		    is.close();
	    }
	}
	
	
	bool isBlackListed(string name)
	{
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
		
		for(vector<string>::iterator i = blacklist.begin(), ie = blacklist.end(); i!=ie; i++ )
			if( *i == name )
				return true;
		
				
		return false;
	}
	
};



#endif
