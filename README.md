# cpp-raylib-platformer
A cross-platform 2D platform-jumping game built with C++ and raylib.

Windows:

1. Installa Ninja tramite PowerShell

   `winget install Ninja-build.Ninja`

2. Installa VSCode e CMake-Tools

3. Aggiunge `.vscode/settings.json` (in caso non compila)

   ```json
   {
     "cmake.generator": "Ninja",
     "cmake.configureSettings": {
       "RAYLIB_DIR": "C:/raylib/w64devkit/x86_64-w64-mingw32"
     },
     "cmake.environment": {
       "PATH": "C:\\raylib\\w64devkit\\bin;${env:PATH}"
     }
   }
   ```

   
