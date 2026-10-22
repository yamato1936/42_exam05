CXX = c++
CC = cc
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CFLAGS = -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE
POLYFLAGS = -Wall -Wextra -Werror -std=c++11
BUILD = build

.PHONY: all test clean vect2 bigint polyset life bsq
all: vect2 bigint polyset life bsq

$(BUILD):
	mkdir -p $(BUILD)

vect2: | $(BUILD)
	$(CXX) $(CXXFLAGS) level0/vect2/vect2.cpp level0/vect2/tests/main.cpp -o $(BUILD)/vect2

bigint: | $(BUILD)
	$(CXX) $(CXXFLAGS) level0/bigint/bigint.cpp level0/bigint/tests/main.cpp -o $(BUILD)/bigint

polyset: | $(BUILD)
	$(CXX) $(POLYFLAGS) -Ilevel0/polyset/given -Ilevel0/polyset/solution level0/polyset/given/array_bag.cpp level0/polyset/given/tree_bag.cpp level0/polyset/solution/searchable_array_bag.cpp level0/polyset/solution/searchable_tree_bag.cpp level0/polyset/solution/set.cpp level0/polyset/tests/main.cpp -o $(BUILD)/polyset

life: | $(BUILD)
	$(CC) $(CFLAGS) level1/life/life.c -o $(BUILD)/life

bsq: | $(BUILD)
	$(CC) $(CFLAGS) level1/bsq/bsq.c -o $(BUILD)/bsq

test: all
	./$(BUILD)/vect2
	./$(BUILD)/bigint
	./$(BUILD)/polyset
	printf 'dxss' | ./$(BUILD)/life 3 3 1 | grep -q 'OOO'
	./$(BUILD)/bsq level1/bsq/tests/map.txt | diff - level1/bsq/tests/expected.txt
	@echo 'All practice checks passed'

clean:
	rm -rf $(BUILD)
