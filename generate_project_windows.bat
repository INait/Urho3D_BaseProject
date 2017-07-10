@rmdir /S /Q %~dp0\ProjectBuildWindows\bin
call Project\cmake_vs2015.bat ProjectBuildWindows -DURHO3D_HOME=%~dp0\UrhoBuildWindows -DURHO3D_OPENGL=ON -DURHO3D_SAMPLES=OFF -DURHO3D_C++11=ON -DURHO3D_LUA=OFF -DURHO3D_LIB_TYPE=STATIC -DURHO3D_STATIC_RUNTIME=OFF
copy Project\bin\server*.bat %~dp0\ProjectBuildWindows\bin