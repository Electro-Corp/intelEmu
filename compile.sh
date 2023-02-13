gcc main.c -o 8086
cd exProg
nasm -f bin -o mov.bin mov.a
cd ..
./8086 exProg/mov.bin
