CFLAGS = -Wall -g
LDFLAGS = -lm
src = $(wildcard *.c)
obj = $(src:.c=.o)
myprog = a.out


$(myprog): $(obj) 
	$(CC) ${CFLAGS} -o $@ $^ $(LDFLAGS) 
	make clean-obj

clean:
	rm -f $(obj) $(myprog)

clean-obj:
	rm -f $(obj)