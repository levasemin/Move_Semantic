CC = g++

BuildF = build/
LIBRARIES = -I"$(CURDIR)/../../src/SuperType/" -I"$(CURDIR)/../../src/test_copy_move_semantic/" -I"$(CURDIR)/../../src/test_move_forward/" -I"$(CURDIR)/../../src/test_universal_reference/"

wrong_copy_semantic_flag: clean
	$(CC) ../../src/main.cpp -D WRONG_COPY_SEMANTIC -fno-elide-constructors -o $(BuildF)main_wrong_copy $(LIBRARIES)

wrong_move_semantic_flag: clean
	$(CC) ../../src/main.cpp -D WRONG_MOVE_SEMANTIC -fno-elide-constructors -o $(BuildF)main_wrong_move $(LIBRARIES)

clean:
	rm -rf $(BuildF)/*.o