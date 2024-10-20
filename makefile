main:
	rm -f m a.out
	gcc -g *.c

main_sanitize:
	rm -f m a.out
	gcc -g -ggdb -fsanitize=address *.c