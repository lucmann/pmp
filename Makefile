# Normally make prints each line of the recipe before it is executed
# When a line starts with `@`, the echoing of that line is suppressed
Q = @


export Q

subdirs := c cxx

# Functions for Conditionals
#
# $(if condition, then-part[, else-part])
#
# Note that `else-part` is optional, such as in this example
#
#
# The foreach Function
#
# $(foreach var, list, text)
#
# It causes one piece of text to be used repeatedly, each time with
# a different substitution performed on it.
foreach-subdir-all := $(if $(subdirs), \
							$(foreach d, $(subdirs), \
							$(MAKE) -C $(d); cd ..))
foreach-subdir-clean := $(if $(subdirs), \
							$(foreach d, $(subdirs), \
							$(MAKE) -C $(d) clean; cd ..))

all: 
	$(Q)$(foreach-subdir-all)

clean:
	$(Q)$(foreach-subdir-clean)

.PHONY: all clean
