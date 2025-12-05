# lem-in

A program to move ants in a graph from A to B in the minimum number of steps.

## Usage

```sh
make
./lem-in -p < ./maps/map-06-big_superposition.txt
```

The `generator` program can be used on macos to generate test cases:

```sh
./generator --big-superposition > d && ./lem-in --p < d | grep 'lines'
```
