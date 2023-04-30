CC := gcc
CFLAGS := -Wall -Wextra -Werror=implicit -Wconversion -Wdouble-promotion -pedantic -g3 -fsanitize=address -fsanitize=undefined -Ilib/inc
CLIBS := -lm

SRCFILES := $(wildcard lib/*.c)
SRCFILES += $(wildcard test/*.c)
OBJFILES := $(SRCFILES:%.c=obj/%.o)
DEPFILES := $(SRCFILES:%.c=obj/%.dep)
DEPFLAGS = -M -MT $@ -MMD -MP -MF $(@:.o=.dep)
TARGET := bin/cutils-test


all: $(TARGET)

clean:
	rm -rf bin/ obj/

test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test


$(TARGET): mkdir $(OBJFILES)
	$(CC) $(CFLAGS) $(CLIBS) $(OBJFILES) -o $(TARGET)

obj/%.o: %.c
	@$(CC) $(CFLAGS) $(DEPFLAGS) $<
	$(CC) $(CFLAGS) -c $< -o $@

mkdir:
	@mkdir -p bin/ obj/lib/ obj/test/


$(DEPFILES): mkdir

include $(DEPFILES)
