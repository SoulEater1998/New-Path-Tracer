# New Path Tracer

This renderer is based off [Path Tracer](https://github.com/JamesGriffin/Path-Tracer)

Compile:

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Features

- using SAH(Bounding Volume Hierarchy) to build BVH

## TODO

- [ ] Accelerating vector operation with SIMD
- [x] use BVH
- [x] **A REAL Monte Carlo integrator with Disney BSDF**
- [ ] **MIS(Multiple Importance Sampling)**
- [ ] QT GUI
- [x] .xml loader
- [ ] **path guiding**
- [ ] **bi-directional path tracing**
- [ ] animation

I will add some new technologies in TODO list later.