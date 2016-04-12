# DllCopy

DllCopy enumerates the dlls required by an exe.
```
DllCopy C:\exmaple\test.exe
```
You can also instruct DllCopy to copy these dlls into the folder of the application.
```
DllCopy C:\exmaple\test.exe copy
```

Dlls from the system folder are ignored by default (although this could be changed in the source). Further more all files listed in **blacklist.txt** are ignored.
The application is licensed under the terms of the GPL in version 3. The dll enumeration is based on source code by Felix Opatz.

The folliwing listing shows an example output.
```
[+] Parsing: C:\Users\test\Downloads\_bundle\test.exe
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\Qt5Core.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libstdc++-6.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\Qt5Gui.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libstdc++-6.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\Qt5Core.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libstdc++-6.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\Qt5Qml.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libstdc++-6.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\Qt5Core.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libstdc++-6.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\Qt5Network.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll
[+] Parsing: C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
[+] Parsing: C:\Program Files\Dev-Cpp\MinGW64\bin\libgcc_s_dw2-1.dll
[+] Parsing: C:\Program Files\Dev-Cpp\MinGW64\bin\libstdc++-6.dll
[+] Parsing: C:\Program Files\Dev-Cpp\MinGW64\bin\libgcc_s_sjlj-1.dll

--- Dll Dependencies: ---

C:\Qt\5.6\mingw49_32\bin\Qt5Core.dll
C:\Qt\5.6\mingw49_32\bin\libgcc_s_dw2-1.dll
C:\Qt\5.6\mingw49_32\bin\libwinpthread-1.dll
C:\Qt\5.6\mingw49_32\bin\libstdc++-6.dll
C:\Qt\5.6\mingw49_32\bin\Qt5Gui.dll
C:\Qt\5.6\mingw49_32\bin\Qt5Qml.dll
C:\Qt\5.6\mingw49_32\bin\Qt5Network.dll
C:\Program Files\Dev-Cpp\MinGW64\bin\libgcc_s_sjlj-1.dll

--- ----------------- ---

Copying files...


--------------------------------
```
