# Porting to your kernel

To build uDRM, you need either GCC or Clang. You don't need a hosted toolchain,
uDRM can be compiled for a freestanding environment.

To add uDRM to your kernel, you have to add `include/` to the include search path.
Then, implement all common `uAPI` functions (see `include/udrm/kernel_api.h`).
Build and link against `src/udrm.c`, `src/udrm_core.c` and `src/udrm_*.c` for drivers.

If you have a custom DRM backend that you would like to use instead of the one
provided by uDRM, don't link against `src/udrm_core.c`. You then have to implement
all headers in `include/udrm/core/` for it to work.
