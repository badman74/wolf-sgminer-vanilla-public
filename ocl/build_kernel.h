#ifndef BUILD_KERNEL_H
#define BUILD_KERNEL_H

#include <stdbool.h>
#include "logging.h"

// I know. You would think I should include ocl.h here, because with code
// that wasn't retarded, I would.. The header algorithm.h needs the
// build_kernel_data type, but ocl.h includes algorithm.h because it requires
// the algorithm_t type. Therefore, this is the way I'm doing it, because
// I don't want to clean a ton of code right now, and this is the easiest
// fix I can think of that contains the least amount of stupid code.

#ifdef __APPLE_CC__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

typedef struct _build_kernel_data {
  char source_filename[255];
  char binary_filename[255];
  char compiler_options[512];

  cl_context context;
  cl_device_id *device;

// for compiler options
  char platform[64];
  char sgminer_path[255];
  const char *kernel_path;
  size_t work_size;
  bool has_bit_align;
  bool patch_bfi;
  float opencl_version;
} build_kernel_data;

bool needs_bfi_patch(build_kernel_data *data);
cl_program build_opencl_kernel(build_kernel_data *data, const char *filename);
bool save_opencl_kernel(build_kernel_data *data, cl_program program);
void set_base_compiler_options(build_kernel_data *data);

#endif /* BUILD_KERNEL_H */
