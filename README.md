# New Path Tracer

This renderer is based off [Path Tracer](https://github.com/JamesGriffin/Path-Tracer)

Compile:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Run:

```bash
$ ./pathtracer <number of samples>
```

## Features

- Accelerating vector operation with SIMD

## To Do

- [ ] Accelerating vector operation with SIMD
- [ ] use BVH
- [ ] **A REAL Monte Carlo integrator with MIS(Multiple Importance Sampling)**
- [ ] QT GUI
- [ ] .xml loader
- [ ] **path guiding**
- [ ] **bi-directional path tracing**
- [ ] animation

