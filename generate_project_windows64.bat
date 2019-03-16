@rmdir /S /Q %~dp0\ProjectBuildWindows64\bin
cd Project
call "scripts\cmake_vs2017.bat" ..\ProjectBuildWindows64 -DURHO3D_HOME="%~dp0\UrhoBuildWindows64" -DURHO3D_OPENGL=ON -DURHO3D_SAMPLES=OFF -DURHO3D_C++11=ON -DURHO3D_64BIT=1 -DURHO3D_LIB_TYPE=STATIC -DURHO3D_STATIC_RUNTIME=OFF
cd ..\