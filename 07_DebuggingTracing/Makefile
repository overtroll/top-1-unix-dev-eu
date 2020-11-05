GENERATES = *.so
TRASH = *.o *~ o.* *.a

all:
	cc -shared -fPIC wrapper.c -ldl -o wrapper.so

test:
	make all
	touch "test_files_foo"
	touch "test_files_FIX"
	LD_PRELOAD=`pwd`/wrapper.so rm "test_files_foo"
	LD_PRELOAD=`pwd`/wrapper.so rm "test_files_FIX"

clean:
	rm -f $(TRASH)

distclean: clean
	rm  -f $(GENERATES)