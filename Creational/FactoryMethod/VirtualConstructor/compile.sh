#create object file for main class
g++ -I FactoryMethod -I FactoryUser -c main.cpp -o bin/main.o
#
#create Factory User object
g++ -I FactoryMethod -I FactoryUser -c FactoryUser/FactoryUser.cpp -o bin/FactoryUser.o
#
#create Factory object
g++ -I FactoryMethod -c FactoryMethod/FactoryMethod.cpp -o bin/FactoryMethod.o
#
#Link the binaries
g++ ./bin/FactoryMethod.o ./bin/FactoryUser.o ./bin/main.o -o bin/main
#
#display the binaries
ls -ltr bin