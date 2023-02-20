CC = g+++

BuildF = obj/

default_flag: clean
	$(CC) main.cpp -fno-elide-constructors -o main

move_semantic_flag: clean
	$(CC) main.cpp -D MOVE_SEMANTIC -fno-elide-constructors -o main

wrong_copy_semantic_flag: clean
	$(CC) main.cpp -D WRONG_COPY_SEMANTIC -fno-elide-constructors -o main

wrong_move_semantic_flag: clean
	$(CC) main.cpp -D WRONG_MOVE_SEMANTIC -fno-elide-constructors -o main

swap_flag: clean
	$(CC) main.cpp -D SIMPLE_SWAP -D MOVE_SEMANTIC -fno-elide-constructors -o main

swap_move_flag: clean
	$(CC) main.cpp -D SWAP_MOVE -D MOVE_SEMANTIC -fno-elide-constructors -o main

beast_flag: clean
	$(CC) main.cpp -D BEAST -D MOVE_SEMANTIC -fno-elide-constructors -o main

beast_forward_flag: clean
	$(CC) main.cpp -D BEAST_FORWARD -D MOVE_SEMANTIC -fno-elide-constructors -o main

default: clean
	$(CC) main.cpp -o main

move_semantic: clean
	$(CC) main.cpp -D MOVE_SEMANTIC -o main

wrong_copy_semantic: clean
	$(CC) main.cpp -D WRONG_COPY_SEMANTIC -o main

wrong_move_semantic: clean 
	$(CC) main.cpp -D WRONG_MOVE_SEMANTIC -o main

swap: clean
	$(CC) main.cpp -D SIMPLE_SWAP -o main

swap_move: clean
	$(CC) main.cpp -D SWAP_MOVE -o main

beast: clean
	$(CC) main.cpp -D BEAST -o main

beast_forward: clean
	$(CC) main.cpp -D BEAST_FORWARD -o main

clean:
	rm -rf $(BuildF)/*.o