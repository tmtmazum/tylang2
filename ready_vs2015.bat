rm -rf build
mkdir build
cd build
cmake -Werror=dev -Werror=deprecated -G "Visual Studio 14 2015 Win64" ../src/
