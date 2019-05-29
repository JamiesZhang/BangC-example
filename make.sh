cncc -c hw2Kernal.mlu -o hw2Kernal.o
g++ -c main.cpp
g++ -c hw2.cpp -I ~/Cambricon-Test/include
g++ hw2Kernal.o main.o hw2.o -o hw2_test -L ~/Cambricon-Test/lib -lcnrt
