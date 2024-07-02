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
							$(MAKE) -C $(d); cd ..),:)
foreach-subdir-clean := $(if $(subdirs), \
							$(foreach d, $(subdirs), \
							$(MAKE) -C $(d) clean; cd ..),:)

# Notice that above variables look so similar that should be abstracted
# as function
#
# The call Function
#
# $(call variable, param, param, ...)
#
# This example doesn't work. According to GNU make manual, the call function
# expands the param arguments before assigning them to temporary variables.
# This means that `variable` values containing references to built-in functions
# that have special expansion rules, like `foreach` or `if`, may not work
# as you expect.
# Hence I guess it is not good idea to mix `call` together with `foreach` or
# `if` to use like that
foreach-subdir-make := $(if $(subdirs), \
							$(foreach d, $(subdirs), \
							$(MAKE) -C $(d) $(1); cd ..))

all: 
	$(Q)$(call foreach-subdir-make)

clean:
	$(Q)$(call foreach-subdir-make,clean)
	$(Q)$(foreach-subdir-clean)  # fallback

.PHONY: all clean
