all: mvote.o hashtable.o linkedList.o pCodeLinkedList.o votedLinkedList.o
	g++ -o mvote mvote.o hashtable.o linkedList.o pCodeLinkedList.o votedLinkedList.o

hashtable.o: hashtable.cpp
	g++ -c hashtable.cpp

linkedList.o: linkedList.cpp
	g++ -c linkedList.cpp

pCodeLinkedList.o: pCodeLinkedList.cpp
	g++ -c pCodeLinkedList.cpp

votedLinkedList.o: votedLinkedList.cpp
	g++ -c votedLinkedList.cpp

clean:
	rm -f mvote mvote.o hashtable.o linkedList.o pCodeLinkedList.o votedLinkedList.o
