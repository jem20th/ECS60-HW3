# hching; Ching, Harrison

huffman: 		huffman.o
			g++ huffman.o -o huffman
		
huffman.o: 		huffman.cpp
			g++ -c huffman.cpp
			
clean:		
			rm -rf huffman.o huffman
