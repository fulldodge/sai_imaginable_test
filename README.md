gcc -shared -fPIC libsaivs.c -o libsaivs.so
gcc sai.c -L. -lsaivs -o test_sai
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
./test_sai
