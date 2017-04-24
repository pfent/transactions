## build with
```bash
mkdir build
cd build
cmake ..
make
```

## run with
### only outputting the serializability as `true` / `false`
```bash
echo "w 1 x r 2 x w 2 y r 3 y w 3 z r 1 z" | ./transactions
```
### displaying the precedence graph
(with a little help of graphviz and imagemagick :sparkles:)
```bash
echo "w 1 x r 2 x w 2 y r 3 y w 3 z r 1 z" | ./transactions graph | dot -Tpng | display -
```