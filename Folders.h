#ifndef _FOLDERS_H_
#define _FOLDERS_H_

#include <stdio.h>
#include <windows.h>
#include <string>

using namespace std;


/*
If SafeDllSearchMode is enabled, the search order is as follows:

    The directory from which the application loaded.
    The system directory. Use the GetSystemDirectory function to get the path of this directory.
    The 16-bit system directory. There is no function that obtains the path of this directory, but it is searched.
    The Windows directory. Use the GetWindowsDirectory function to get the path of this directory.
    The current directory.
    The directories that are listed in the PATH environment variable. Note that this does not include the per-application path specified by the App Paths registry key. The App Paths key is not used when computing the DLL search path.

If SafeDllSearchMode is disabled, the search order is as follows:

    The directory from which the application loaded.
    The current directory.
    The system directory. Use the GetSystemDirectory function to get the path of this directory.
    The 16-bit system directory. There is no function that obtains the path of this directory, but it is searched.
    The Windows directory. Use the GetWindowsDirectory function to get the path of this directory.
    The directories that are listed in the PATH environment variable. Note that this does not include the per-application path specified by the App Paths registry key. The App Paths key is not used when computing the DLL search path.
*/


class Folders 
{
private:
	string systemDir;
	string windowsDir;
	string appDir;
	vector<string> envPath;
	int machine;
	
	inline bool fileExists (const std::string& name) {
	    return ( access( name.c_str(), F_OK ) != -1 );
	}
	
	const vector<string>& get_environment_PATH()
	{
	    static vector<string> result;
	    if( !result.empty() )
	        return result;
	
	
	    const std::string PATH = getenv( "PATH" );
	    const char delimiter = ';';
	
	    if( PATH.empty() )
	    {
	        cout << "PATH should not be empty" << endl;
			exit(-1); 
	    }
	
	    size_t previous = 0;
	    size_t index = PATH.find( delimiter );
	    while( index != string::npos )
	    {
	        result.push_back( PATH.substr(previous, index-previous));
	        previous=index+1;
	        index = PATH.find( delimiter, previous );
	    }
	    result.push_back( PATH.substr(previous) );
	
	    return result;
	}
	

	int getMachine(string path)
	{
		FILE *fp;
   		fp = fopen(path.c_str(),"r");
   		
   		IMAGE_DOS_HEADER DOSHeader;
   		int result = fread(&DOSHeader, 1, sizeof(IMAGE_DOS_HEADER), fp);
   		if( result != sizeof(IMAGE_DOS_HEADER) || DOSHeader.e_magic != 0x5a4d )
   		{
   			cout << "Error while parsing!" << endl;
			exit(-1);	
		}
		
		IMAGE_NT_HEADERS NTHeader;
		if( fseek(fp, DOSHeader.e_lfanew , SEEK_SET) != 0 )
  		{
   			cout << "Error while parsing!" << endl;
			exit(-1);	
		}
		result = fread(&NTHeader, 1, sizeof(IMAGE_NT_HEADERS), fp);
		if( result != sizeof(IMAGE_NT_HEADERS) || NTHeader.Signature != 0x4550)
		{
   			cout << "Error while parsing!" << endl;
			exit(-1);	
		}
		
		fclose(fp);
		
		// 0x014c => i386
		// 0x0200 => IA64
        // 0x8664 => AMD64
		return NTHeader.FileHeader.Machine;
	}
	
public:
	Folders()
	{
		char buffer[255];
		GetSystemDirectoryA(buffer, 255);
		systemDir = buffer;
		systemDir += "\\";
		
		GetWindowsDirectoryA(buffer, 255);
		windowsDir = buffer;
		windowsDir += "\\";
		
		envPath = get_environment_PATH();
	}
	
	string getSystemDir(){
		return systemDir;
	}
	
	string getWindowsDir(){
		return windowsDir;
	}
	
	string getAppDir(){
		return appDir;
	}
	
	void setAppDir(string name)
	{
		machine = getMachine(name);
		
		size_t found = name.find_last_of("\\");
		if( found != string::npos)
			name = name.substr(0, found);
		appDir = name + "\\";
	}
	
	string getFullPath(string path, bool skipSystemDir, bool& skippedSystemDir)
	{
		string test = getAppDir() + path;
		if( fileExists(test) && getMachine(test) == machine )
			return test;
			
		test = systemDir + path;
		if( fileExists(test) && getMachine(test) == machine )
		{
			if( skipSystemDir )
			{
				skippedSystemDir = true;
				return path;
			}
			else
				return test;
		}
			
		test = windowsDir + path;
		if( fileExists(test) && getMachine(test) == machine )
			return test;
			
		for(vector<string>::iterator i = envPath.begin(), ie = envPath.end(); i!=ie; i++ )
		{
			test = *i + "\\" + path;
			if( fileExists(test) && getMachine(test) == machine )
				return test;
		}
		
		return path;
	}
	
};




#endif
