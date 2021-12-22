#include "marta_wrapper.h"

static inline void kernel() {
  // MARTA_CMD: ASM_CODE
}

MARTA_BENCHMARK_BEGIN(0);

// MARTA_CMD: ASM_INIT

PROFILE_FUNCTION(kernel());

MARTA_BENCHMARK_END;