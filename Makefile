CC = gcc
NAME = int2bin
PREFIX=/usr/local

$(NAME): $(NAME).o
	$(CC) -o $(NAME) $(NAME).o

$(NAME).o: $(NAME).c

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(NAME)

.PHONY: install
install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $(NAME) $(DESTDIR)$(PREFIX)/bin/$(NAME)

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(NAME)
