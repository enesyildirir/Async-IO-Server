CC     = gcc
CFLAGS = -Wall -Wextra -g -std=c11

BINDIR = bin
SRCDIR = src
CLIDIR = client

SERVER_BIN = $(BINDIR)/server
CLIENT_BIN = $(BINDIR)/client

SERVER_SRCS = $(SRCDIR)/server.c        \
              $(SRCDIR)/epoll_core.c    \
              $(SRCDIR)/client_manager.c \
              $(SRCDIR)/broadcast.c     \
              $(SRCDIR)/utils.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)

.PHONY: all clean run test

all: $(BINDIR) $(SERVER_BIN) $(CLIENT_BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

$(SERVER_BIN): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "[OK] Sunucu derlendi: $@"

$(CLIENT_BIN): $(CLIDIR)/client.c
	$(CC) $(CFLAGS) -o $@ $^
	@echo "[OK] Istemci derlendi: $@"

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(SERVER_BIN)
	./$(SERVER_BIN) 8080

test: $(CLIENT_BIN) $(SERVER_BIN)
	bash $(CLIDIR)/load_test.sh 10 127.0.0.1 8080

clean:
	rm -f $(SERVER_OBJS) $(SERVER_BIN) $(CLIENT_BIN)
	@echo "[TEMIZ]"
