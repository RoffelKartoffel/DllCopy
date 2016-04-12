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
