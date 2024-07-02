programs := $(patsubst %.c,%,$(wildcard *.c))

# The default goal is the first target of first rule in the first makefile
# Note that absence of recipe is legal in make
all: $(programs)

# `:` is a special built-in shell command which is used when a command
# is needed, as in the _then_ condition of an _if_ command, but nothing
# is to be done by the command. This command simply yields an exit status
# of zero (success). This can be useful, for example, when you are evaluating
# shell expressions for their side effects.
#
# `$@` is the file name of the target of the rule. If the target is an
# archive member, then `$@` is the name of the archive file. In a pattern
# rule that has multiple targets, `$@` is the name of whichever target
# caused the rule's recipe to be run.
#
# Pattern Rule
# You can override a built-in implicit rule by defining a new *pattern rule*
# with the same target and prerequisites, but a different recipe.
# What it means by *built-in implicit rule* is that the rule will be performed
# by make if there is none of the following rule.
%: %.c
	$(Q):; printf "Compiling ... "
	$(CC) $< -o $@

# Tab is prefix of a recipe in make. However it is allowed to alternate the
# prefix character of your recipe via .RECIPEPREFIX variable.

# %.o: %.c
	# $(CC) -c $< -o $@		# This line will be echoed and in an expanded way

clean:
	rm -rf $(programs) *.out

.PHONY: all clean
