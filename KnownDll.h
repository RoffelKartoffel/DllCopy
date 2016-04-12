#ifndef _KNOWN_DLL_
#define _KNOWN_DLL_

#include <windows.h>

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

class KnownDll 
{
private:
	vector<string> knownDlls;		
	
public:
	KnownDll()
	{
		HKEY hKey;
		if( RegOpenKeyExA( HKEY_LOCAL_MACHINE,
	        "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\KnownDLLs",
	        0,
	        KEY_READ,
        	&hKey) == ERROR_SUCCESS)
		{
			TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
		    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
		    DWORD    cchClassName = MAX_PATH;  // size of class string 
		    DWORD    cSubKeys=0;               // number of subkeys 
		    DWORD    cbMaxSubKey;              // longest subkey size 
		    DWORD    cchMaxClass;              // longest class string 
		    DWORD    cValues;              // number of values for key 
		    DWORD    cchMaxValue;          // longest value name 
		    DWORD    cbMaxValueData;       // longest value data 
		    DWORD    cbSecurityDescriptor; // size of security descriptor 
		    FILETIME ftLastWriteTime;      // last write time 
			
			// Get the class name and the value count. 
		    DWORD retCode = RegQueryInfoKeyA(
		        hKey,                    // key handle 
		        achClass,                // buffer for class name 
		        &cchClassName,           // size of class string 
		        NULL,                    // reserved 
		        &cSubKeys,               // number of subkeys 
		        &cbMaxSubKey,            // longest subkey size 
		        &cchMaxClass,            // longest class string 
		        &cValues,                // number of values for this key 
		        &cchMaxValue,            // longest value name 
		        &cbMaxValueData,         // longest value data 
		        &cbSecurityDescriptor,   // security descriptor 
		        &ftLastWriteTime);       // last write time 
			
					
			for (int i=0, retCode = ERROR_SUCCESS; i<cValues; i++) 
	        { 
		        TCHAR  achValue[MAX_VALUE_NAME]; 
				DWORD cchValue = MAX_VALUE_NAME; 
				BYTE Data[MAX_VALUE_NAME];
				DWORD cbData = MAX_VALUE_NAME;
	        
	            cchValue = MAX_VALUE_NAME; 
	            achValue[0] = '\0'; 
	            retCode = RegEnumValue(hKey, i, 
	                achValue, 
	                &cchValue, 
	                NULL, 
	                NULL,
	                Data,
	                &cbData);
	 
	            if (retCode == ERROR_SUCCESS ) 
	            { 	
	                string dll_name = (char*)Data;
	                std::transform(dll_name.begin(), dll_name.end(), dll_name.begin(), ::tolower);
	              	knownDlls.push_back(dll_name);
	            } 
	            
	        }
		}	
	}
	
	bool isKnownDll(string name)
	{
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
		
		if(std::find(knownDlls.begin(), knownDlls.end(), name) != knownDlls.end())
			return true;
		return false;
	}
};


#endif
