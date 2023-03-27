all:
	+$(MAKE) -C 1-Pig-latin
	+$(MAKE) -C 2-Shuffling
	+$(MAKE) -C 3-Beggar-your-neighbour

clean:
	+$(MAKE) -C 1-Pig-latin clean
	+$(MAKE) -C 2-Shuffling clean
	+$(MAKE) -C 3-Beggar-your-neighbour clean