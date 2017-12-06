# Ising_model
This set of code snippets was initially written for a pset problem in the course _Statistical Thermodynamics_ in MIT ([MIT OpenCourseWare](https://ocw.mit.edu/courses/chemistry/5-72-statistical-mechanics-spring-2012/syllabus/)). The original problem asked you to investigate the behaviour of Ising model in a 2D square lattice

![Image of Ising model Hamiltonia](http://www.hongzhouye.com/wp-content/uploads/2017/12/Ising_hamiltonian-e1512527965653.png)

with an special emphasis on the critical behaviour (for the special case of 2D square lattice, _Tc_ = 2.269185 _J_ / _kB_).

To run the code, simply clone this repositary and type
```
make
```
An executable `mc` will be generated in the same directory.

A sample input file is provided in `input/inp`, which is pretty self-explainary. It can be ran as follows
```
./mc input/inp
```
You will see standard output as well as appropriate output files such as the trajectory file.
