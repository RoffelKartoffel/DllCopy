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
[+] Parsing: C:\Users\test\Downloads\_bundle\YoloGen.exe
[+] Parsing: C:\Users\test\Downloads\_bundle\Qt5Core.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libstdc++-6.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\Qt5Gui.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libstdc++-6.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\Qt5Core.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libstdc++-6.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\Qt5Qml.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libstdc++-6.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\Qt5Core.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libstdc++-6.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\Qt5Network.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libstdc++-6.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
[+] Parsing: C:\Users\test\Downloads\_bundle\libwinpthread-1.dll

--- Dll Dependencies: ---

C:\Users\test\Downloads\_bundle\Qt5Core.dll
C:\Users\test\Downloads\_bundle\libgcc_s_dw2-1.dll
C:\Users\test\Downloads\_bundle\libwinpthread-1.dll
C:\Users\test\Downloads\_bundle\libstdc++-6.dll
C:\Users\test\Downloads\_bundle\Qt5Gui.dll
C:\Users\test\Downloads\_bundle\Qt5Qml.dll
C:\Users\test\Downloads\_bundle\Qt5Network.dll

--- ----------------- ---

Copying files...


--------------------------------
```
