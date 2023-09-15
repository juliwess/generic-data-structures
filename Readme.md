# Projekt Alpha

## Building the project
The build system provided for this projecdt is cmake
You can use the following command to create the build-folder and some
executable test files
```
cmake -S . -B build && cmake --build build
```


If the project doesn't build like that you are most likely missing some external packages. However you should be able to import and use the classes after cloning the project


## Organaisation
Unfortunately the implemantion had to happen in the hpp-files as the data structures are generic

