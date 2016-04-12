#include <iostream>
#include <windows.h>
#include <unistd.h>
#include <map>

#include "opatz/ImportList.h"
#include "KnownDll.h"
#include "Folders.h"
#include "Blacklist.h"

using namespace std;


KnownDll kd;
Blacklist bl;


// https://msdn.microsoft.com/en-us/library/windows/desktop/ms682586%28v=vs.85%29.aspx




bool isExtension(string path, string ext)
{
	std::transform(path.begin(), path.end(), path.begin(), ::tolower);
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
	
	ext = "." + ext;
	int len = ext.size();
	if( path.size() < len)
		return false;
		
	for(int i=0; i<len; i++)
		if( path[path.size() -1 -i] != ext[ext.size() -1 -i] )
			return false;
	
	return true;
}

bool contains(vector<string>& v, string s)
{
	for(vector<string>::iterator i = v.begin(), ie = v.end(); i!=ie; i++ )
	{
		if( *i == s )
			return true;
	}
	return false;
}


void resolv(Folders f, vector<string>& dlls, map<string, int>& dllShortNames, std::string path, bool dll = true)
{
	cout << "[+] Parsing: " << path << endl;
	
	f.setAppDir(path);
	
	std::vector<std::string> imports;
	if( !ImportList::GetList(path.c_str(), imports, ImportList::LT_MODULES) )
	{
		cout << "Error on ImportList!" << endl;
		exit(-1);
	}
	
	for (int vecindex = 0; vecindex < imports.size(); vecindex++)
	{
		string dll = imports[vecindex];
		
		if( !isExtension(dll, "dll") ||
			kd.isKnownDll(dll) ||
			bl.isBlackListed(dll) )
		{
			continue;
		}
		
		bool skippedSystemDir;
		string shortName = dll;
		dll = f.getFullPath(dll, true, skippedSystemDir);
		if( !skippedSystemDir )
		{
			if( dllShortNames[shortName] == 0 )
			{
				dllShortNames[shortName]++;
				dlls.push_back(dll);
			}
			
	        //std::cout << dll << std::endl;
	        resolv(f, dlls, dllShortNames, dll);
	    }
    }
}




int main(int argc, char** argv) 
{
	vector<string> dlls;
	map<string, int> dllShortNames;
	
	
	string testedExe;
	if( argc >= 2 )
		testedExe = argv[1];
	Folders f;
	f.setAppDir(testedExe);
	
	resolv(f, dlls, dllShortNames, testedExe);
	
	cout << endl;
	cout << "--- Dll Dependencies: ---" << endl << endl;
	for(vector<string>::iterator i = dlls.begin(), ie = dlls.end(); i!=ie; i++ )
	{
		cout << *i << endl;
	}
	cout << endl;
	cout << "--- ----------------- ---" << endl << endl;;
	
	if( argc >= 3 && string(argv[2]) == "copy" )
	{
		cout << "Copying files..." << endl << endl;
		
		for(vector<string>::iterator i = dlls.begin(), ie = dlls.end(); i!=ie; i++ )
		{
			string cmd = "copy \"" + *i + "\" \"" + f.getAppDir() + "\" >NULL";
			//cout << cmd << endl;
			system(cmd.c_str());
		}
	}

	
	return 0;
}

