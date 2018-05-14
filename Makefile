bintree:bintree.c seqstack.c
	gcc -g $^ -o $@

.PHONY:clean
	clean:
		rm bintree
