OBJS	= minisearch.o Map.o Heap.o Trie.o newlist.o Utils.o
SOURCE	= minisearch.cpp Map.cpp Heap.cpp Trie.cpp newlist.cpp Utils.cpp
HEADER	= Map.h Trie.h newlist.h List.h Heap.h Utils.h 
OUT	= minisearch
CC	= g++
FLAGS	= -g -c
#executable
$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@
#object files
minisearch.o: minisearch.cpp
	$(CC) $(FLAGS)	$?
Map.o: Map.cpp
	$(CC) $(FLAGS) $?
Trie.o: Trie.cpp
	$(CC) $(FLAGS) $?
Heap.o: Heap.cpp
	$(CC) $(FLAGS) $?
Utils.o: Utils.cpp
	$(CC) $(FLAGS) $?
newlist.o: newlist.cpp
	$(CC) $(FLAGS) $?

#default execution command
#with file Entertainment.txt and top K =5
run:
	./minisearch -i Entertainment.txt -K 5
#delete object files and exe
clean:
	rm -f *.o minisearch
#count lines
count:
	wc -l $(SOURCE) $(HEADER)
valgrind:
	valgrind --leak-check=yes --show-reachable=yes --track-fds=yes ./minisearch -i Entertainment.txt -K 5