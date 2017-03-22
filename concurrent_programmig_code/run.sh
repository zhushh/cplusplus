FLAGS="-std=c++0x -lpthread"
CC="g++"
program=$1

if [ -z $program ]; then
    echo "Please tell me the source file."
    echo "Usage: ./run.sh source.cpp"
    exit 0
fi

echo "Compile $program ..."
echo "Run command: $CC $program $FLAGS"
$($CC $program $FLAGS)

compile_code=$?
if [ $compile_code != 0 ]; then
    echo "Error! Error code = $compile_code"
    exit $compile_code
fi

echo "Finished!"

