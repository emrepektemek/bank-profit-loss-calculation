hepsi: derle calistir

derle:
	gcc -I ./include/ -o ./lib/Metot.o -c ./src/Metot.c
	gcc -I ./include/ -o ./lib/Portfoy.o -c ./src/Portfoy.c
	gcc -I ./include/ -o ./lib/Hisse.o -c ./src/Hisse.c
	gcc -I ./include/ -o ./lib/Emir.o -c ./src/Emir.c
	gcc -I ./include/ -o ./lib/Banka.o -c ./src/Banka.c
	gcc -I ./include/ -o ./bin/Test ./lib/Metot.o  ./lib/Portfoy.o ./lib/Hisse.o ./lib/Banka.o ./lib/Emir.o ./src/Test.c
calistir:
	./bin/Test