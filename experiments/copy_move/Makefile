CC = g++

BuildF = build/
LIBRARIES = -I"$(CURDIR)/../../src/SuperType/" -I"$(CURDIR)/../../src/test_copy_move_semantic/" -I"$(CURDIR)/../../src/test_move_forward/" -I"$(CURDIR)/../../src/test_universal_reference/"


default_flag: clean
	$(CC) ../../src/main.cpp -fno-elide-constructors -o $(BuildF)main_copy $(LIBRARIES)

move_semantic_flag: clean
	$(CC) ../../src/main.cpp -D MOVE_SEMANTIC -fno-elide-constructors -o $(BuildF)main_move $(LIBRARIES)

clean:
	rm -rf $(BuildF)/*.o