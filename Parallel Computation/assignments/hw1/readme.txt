running from terminal:

mpicc static.c -o static -lm
mpiexec -np 2 ./static
mpiexec -np 4 ./static
mpiexec -np 10 ./static

mpicc dynamic.c -o dynamic -lm
mpiexec -np 2 ./dynamic
mpiexec -np 4 ./dynamic
mpiexec -np 10 ./dynamic

we found that without that -lm flag the compilation fails.