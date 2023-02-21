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

default: clean
	$(CC) main.cpp -o main

clean:
	rm -rf $(BuildF)/*.o