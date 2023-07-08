CC = g++

BuildF = build/
LIBRARIES = -I"$(CURDIR)/../../src/SuperType/" -I"$(CURDIR)/../../src/test_copy_move_semantic/" -I"$(CURDIR)/../../src/test_move_forward/" -I"$(CURDIR)/../../src/test_universal_reference/"

default: clean
	$(CC) src/main.cpp -o $(BuildF)main $(LIBRARIES)

default_flag: clean
	$(CC) src/main.cpp -fno-elide-constructors -o $(BuildF)main $(LIBRARIES)

move_semantic_flag: clean
	$(CC) src/main.cpp -D MOVE_SEMANTIC -fno-elide-constructors -o $(BuildF)main $(LIBRARIES)

wrong_copy_semantic_flag: clean
	$(CC) src/main.cpp -D WRONG_COPY_SEMANTIC -fno-elide-constructors -o $(BuildF)main $(LIBRARIES)

wrong_move_semantic_flag: clean
	$(CC) src/main.cpp -D WRONG_MOVE_SEMANTIC -fno-elide-constructors -o $(BuildF)main $(LIBRARIES)



clean:
	rm -rf $(BuildF)/*.o