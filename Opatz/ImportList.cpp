/*
 * Copyright (c) 2008, Felix Opatz
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of  nor the names of its contributors may be used to
 *    endorse or promote products derived from this software without specific
 *    prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sstream>
#include <windows.h>
#include <winnt.h>

#include "ImportList.h"

namespace ImportList
{

const std::string ListDelimiter = ": ";

// Get a file mapping for a given file
bool GetFileMapping(std::string Path, tMapping &Mapping)
{
    // Open file
    Mapping.hFile =
        CreateFile(Path.c_str(),         // Filename
                   GENERIC_READ,         // Desired access
                   0,                    // Share mode
                   NULL,                 // Security attributes
                   OPEN_EXISTING,        // Creation disposition
                   0,                    // Flags and attributes
                   NULL);                // Template

    // Opening file successful?
    if (Mapping.hFile == INVALID_HANDLE_VALUE)
    {
        // No
        return false;
    }

    // Get file mapping
    Mapping.hMapping =
        CreateFileMapping(Mapping.hFile, // File handle
                          NULL,          // Security attributes
                          PAGE_READONLY, // Protection
                          0,             // Maximum size (high)
                          0,             // Maximum size (low)
                          NULL);         // Name of mapping

    // Mapping file successful?
    if (Mapping.hMapping == NULL)
    {
        // No, close file before leaving
        CloseHandle(Mapping.hFile);
        return false;
    }

    // Get pointer to view of mapping
    Mapping.pBaseAddr = (PBYTE)
        MapViewOfFile(Mapping.hMapping,  // Handle to mapping
                      FILE_MAP_READ,     // Desired access
                      0,                 // Offset (high)
                      0,                 // Offset (low)
                      0);                // Size of mapping

    // Getting view to mapping successful?
    if (Mapping.pBaseAddr == NULL)
    {
        // No, close mapping and file before leaving
        CloseHandle(Mapping.hMapping);
        CloseHandle(Mapping.hFile);
        return false;
    }

    // Creating file mapping was successful
    return true;
}

// Close an existing file mapping
void CloseFileMapping(tMapping &Mapping)
{
    UnmapViewOfFile(Mapping.pBaseAddr);
    CloseHandle(Mapping.hMapping);
    CloseHandle(Mapping.hFile);
}

// Get a list of imports needed by the file specified by Path
bool GetList(std::string Path, std::vector<std::string> &Imports, int ListType)
{
    tMapping Mapping;
    PIMAGE_DOS_HEADER pDosHeader;
    PIMAGE_NT_HEADERS pNtHeaders;
    DWORD ImportDataRva;
    PIMAGE_SECTION_HEADER pCurrentSection;
    unsigned int nSectionCounter;
    PIMAGE_IMPORT_DESCRIPTOR pImportDesc;
    DWORD dwSectionOffset;
    PIMAGE_THUNK_DATA32 pImageThunkData;
    PIMAGE_IMPORT_BY_NAME pImportByName;
    bool boFound = false;
    std::string DllName;
    std::string FunctionName;
    std::stringstream sstream;

    // Clear list
    Imports.clear();

    // Open the file and get the mapping
    if (!GetFileMapping(Path, Mapping))
        return false;

    // Get the DOS header
    pDosHeader = (PIMAGE_DOS_HEADER) Mapping.pBaseAddr;

    // Is it a DOS signature?
    if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        CloseFileMapping(Mapping);
        return false;
    }

    // Ok, get the NT headers next
    pNtHeaders = (PIMAGE_NT_HEADERS)(Mapping.pBaseAddr + pDosHeader->e_lfanew);

    // Is it a NT signature?
    if (pNtHeaders->Signature != IMAGE_NT_SIGNATURE)
    {
        CloseFileMapping(Mapping);
        return false;
    }

    // Get the Relative Virtual Address of the Import Entry of the Image Directory
    ImportDataRva = pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;

    // Get the pointer to the first Image Section
    pCurrentSection = (PIMAGE_SECTION_HEADER)IMAGE_FIRST_SECTION(pNtHeaders);

    // Walk through the sections until the Imports are found (or we are running out of sections)
    nSectionCounter = pNtHeaders->FileHeader.NumberOfSections;
    while ((boFound == false) && (nSectionCounter-- > 0))
    {
        if (   (pCurrentSection->VirtualAddress <= ImportDataRva)
            && (pCurrentSection->VirtualAddress + pCurrentSection->Misc.VirtualSize > ImportDataRva))
        {
            // Found the correct section
            boFound = true;
        }
        else
        {
            // Proceed to next section
            pCurrentSection++;
        }
    }

    // No Import section found?
    if (!boFound)
    {
        // Leave
        CloseFileMapping(Mapping);
        return false;
    }

    // Calculate section offset
    dwSectionOffset = pCurrentSection->VirtualAddress - pCurrentSection->PointerToRawData;

    // Get pointer to first Import Descriptor
    pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)(Mapping.pBaseAddr + ImportDataRva - dwSectionOffset);

    // Copy all Import names into result vector
    while (pImportDesc->Name != 0)
    {
        // Save current import name as std::string
        DllName = (const char*)(Mapping.pBaseAddr + pImportDesc->Name - dwSectionOffset);

        // If only list of modules is requested
        if (ListType == LT_MODULES)
        {
            // Insert current DLL name into vector
            Imports.push_back(DllName);
        }

        // If list of functions is requested
        if (ListType == LT_FUNCTIONS)
        {
            // Get pointer to first image thunk data
            pImageThunkData = (PIMAGE_THUNK_DATA32)(Mapping.pBaseAddr + pImportDesc->FirstThunk - dwSectionOffset);

            // While not at end of thunk data array
            while (*(DWORD*)pImageThunkData != 0)
            {
                // Check if function is imported by name or by ordinal number
                if (*(DWORD*)pImageThunkData & IMAGE_ORDINAL_FLAG)
                {
                    // Save ordinal number into std::stringstream
                    sstream << '#' << LOWORD(pImageThunkData->u1.Ordinal);
                    // Save content of std::stringstream into std::string
                    FunctionName = sstream.str();
                    // Reset std::stringstream for next turn
                    sstream.str("");
                }
                else
                {
                    // Get pointer to current import by name
                    pImportByName = (PIMAGE_IMPORT_BY_NAME)(Mapping.pBaseAddr + pImageThunkData->u1.Function - dwSectionOffset);
                    // Save current import function name as std::string
                    FunctionName = (const char*)pImportByName->Name;
                }

                // Insert current DLL + function name into vector
                Imports.push_back(DllName + ListDelimiter + FunctionName);

                // Proceed to next thunk
                pImageThunkData++;
            }
        }

        // Proceed to next descriptor
        pImportDesc++;
    }

    // Close the mapping and the file
    CloseFileMapping(Mapping);

    // Functions was successful
    return true;
}

}; //namespace ImportList
