# Stack-Machine

## Software Labs II | Laboratórios de Informática II
## Grade: 20/20 :star:

This project was developed during the second semester of the 1st year of the Software Engineering degree @ University of Minho.

The project consisted of developing a stack-oriented programming language, using C. You can learn more about this paradigm [here](https://en.wikipedia.org/wiki/Stack-oriented_programming).

Examples of expressions that can be evaluated by the language itself:

  - `1 2 +`, evaluated to `3`
  - `[ 3 5 7 1 2 ] 2 =`, evaluated to `7` - basically, it is returning the element in the 2nd position of the given array.
  - `2 { 3 * } ~`, evaluated to `6` - basically, it is applying the block (or function) `3 *` to its predecessor(s).

Note: More examples can be seen at the [assignment](Assignment.pdf).

## Installing and running the project

#### Clone the repository

```bash
$ git clone git@github.com:RuiL1904/Stack-Machine-LI2.git
```

#### Compiling
```sh
$ cd Stack-Machine-LI2
$ make
```

### Running the project
```sh
$ make run
```

Note: There are a couple more `make` commands, useful in some situations, available. Check them out at the [Makefile](Makefile).

# Developed by:
- [Rui Lopes](https://github.com/RuiL1904)
- [Duarte Ribeiro](https://github.com/DuduWater12)
- [Filipe Pereira](https://github.com/Filipe2817)
- [Miguel Gramoso](https://github.com/gramosomi)
