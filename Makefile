BIN = app

SRC = $(wildcard ./*.c)
OBJ = $(subst .c,.o,$(SRC))

all:$(BIN)

$(BIN):$(OBJ)
	gcc -o $@ $^

$(OBJ):%.o:%.c
	gcc -c $< -o $@

clean:
	rm -rf ./*.o
	rm -rf ${BIN} ${OBJ}

.PHONY: clean BIN
