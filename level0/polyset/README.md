# Polyset – starter code vs. implementation

This directory deliberately separates **starter files supplied with the exercise** from **files to implement in the exam**.

## Starter files (provided, not to reimplement)
`given/bag.hpp`, `given/searchable_bag.hpp`, `given/array_bag.hpp`, `given/array_bag.cpp`, `given/tree_bag.hpp`, `given/tree_bag.cpp`, `given/main.cpp`.

The starter snapshot was obtained from the `subject/` directory in the community archive [fbkeskin/42-exam-rank-05](https://github.com/fbkeskin/42-exam-rank-05/tree/master/level0/polyset/subject). It is **not** code authored for this repo.

**One compatibility correction**: the mirrored `tree_bag.hpp` declared `copy_node` returning `void*`, but `tree_bag.cpp` defines it returning `node*`. The `given/tree_bag.hpp` copy has a one-line return-type correction to build; the byte-for-byte mirrored header is saved as `given/tree_bag.original.hpp.txt`.

The provided `main.cpp` is archived verbatim as a reference; it contains nonportable syntax and missing direct includes. Use `tests/main.cpp` for compiling this repo, or adapt the exam-provided main locally if needed.

## Implement yourself during the exam
`solution/searchable_array_bag.hpp`, `solution/searchable_array_bag.cpp`, `solution/searchable_tree_bag.hpp`, `solution/searchable_tree_bag.cpp`, `solution/set.hpp`, `solution/set.cpp`.

In the community subject, `searchable_tree_bg.cpp` is a spelling error; the natural matching file is `searchable_tree_bag.cpp`. Verify the **actual** exam subject if it differs.

### Build
```sh
make polyset
./build/polyset 1 2 2 3
```

The `set` is a non-owning wrapper of a `searchable_bag`; start with an empty bag if you need uniqueness of all elements (the underlying array bag can already hold duplicates).
