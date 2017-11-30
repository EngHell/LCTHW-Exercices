make clean
make
echo "**********************"
echo "\n\nRunning And test\n"
./logfind max line
echo "**********************"
echo "\n\nRunning Or test\n"
./logfind max line -o
