cur_path="$PWD"
Project/cmake_generic.sh ProjectBuildLinux64 -DURHO3D_HOME=$cur_path/UrhoBuildLinux64 -DCMAKE_BUILD_TYPE=Debug -DURHO3D_OPENGL=ON -DURHO3D_SAMPLES=OFF -DURHO3D_C++11=ON -DURHO3D_64BIT=1 -DURHO3D_LIB_TYPE=SHARED