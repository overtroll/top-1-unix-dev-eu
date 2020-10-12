CFLAGS = -Wall -fPIC

GENERATES = prog prog-a prog-so README

TRASH = *.o *~ o.* *.a *.so test_dir

CUR_DIR = $(shell pwd)
TEST_DIR = test_dir

all:	README prog prog-a prog-so

fun.o:  outlib.h

prog.o:  outlib.h

liboutput_static.a:	const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	cc -shared $^ -o $@

prog:	const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc -L. $< -loutput_static -o $@

prog-so: export LD_LIBRARY_PATH=$(CUR_DIR)

prog-so: prog.o liboutput.so
	cc -L. $< -loutput -o $@

test: export LD_LIBRARY_PATH=$(CUR_DIR)
test:	prog prog-a prog-so
	mkdir -p $(TEST_DIR)
	cp -f prog $(TEST_DIR)/exe
	./$(TEST_DIR)/exe 2> $(TEST_DIR)/prog.txt
	./$(TEST_DIR)/exe a >> $(TEST_DIR)/prog.txt
	./$(TEST_DIR)/exe a b c >> $(TEST_DIR)/prog.txt
	cp -f prog-a $(TEST_DIR)/exe
	./$(TEST_DIR)/exe 2> $(TEST_DIR)/prog-a.txt
	./$(TEST_DIR)/exe a >> $(TEST_DIR)/prog-a.txt
	./$(TEST_DIR)/exe a b c >> $(TEST_DIR)/prog-a.txt
	cp -f prog-so $(TEST_DIR)/exe
	./$(TEST_DIR)/exe 2> $(TEST_DIR)/prog-so.txt
	./$(TEST_DIR)/exe a >> $(TEST_DIR)/prog-so.txt
	./$(TEST_DIR)/exe a b c >> $(TEST_DIR)/prog-so.txt
	cmp $(TEST_DIR)/prog.txt $(TEST_DIR)/prog-a.txt
	cmp $(TEST_DIR)/prog.txt $(TEST_DIR)/prog-so.txt
	rm -rf $(TEST_DIR)

README:	prog
	./$< 2> $@

clean:
	rm -rf $(TRASH)

distclean:	clean
	rm -rf $(GENERATES)
