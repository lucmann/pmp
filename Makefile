# Normally make prints each line of the recipe before it is executed
# When a line starts with `@`, the echoing of that line is suppressed
Q = @


export Q

subdirs := c

all: 
	$(Q)$(MAKE) -C $(subdirs)

clean:
	$(Q)$(MAKE) -C $(subdirs) clean

.PHONY: all clean
