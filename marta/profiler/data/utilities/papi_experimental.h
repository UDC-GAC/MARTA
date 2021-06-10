/**
 * Copyright 2019-2021 (c) Colorado State University
 * Copyright 2020-2021 (c) Universidade da Coruña
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined(POLYBENCH_PAPI_EXPERIMENTAL)\
struct T {\
  char *name;
  char *feat;
  long flops;
  long_long counters[128];
} values_t;

struct T values[128];

long long n_func = 0;

void update_row(char *name, char *features, long flops, int t, long_long val) {
  if (t == 0) {
    struct T tmp;
    tmp.name = name;
    tmp.feat = features;
    tmp.flops = flops;
    tmp.counters[t] = val;
    values[n_func] = tmp;
    return;
  }
  values[n_func].counters[t] = val;
}
char *__polybench_papi_eventlist[] = {
#include "papi_counters.list"
    NULL};
#undef PROFILE_FUNCTION
#define PROFILE_FUNCTION(STEPS, X, name, features, flops, t)
{
  polybench_start_instruments_single(t);
  X;
  polybench_stop_instruments_single(t);
  update_row(name, features, flops, t, polybench_get_value(t));
  n_func++;
}
#undef MARTA_BENCHMARK_BEGIN
#define MARTA_BENCHMARK_BEGIN(cond)                                            \
  int main(int argc, char **argv) {                                            \
    int i = 0;                                                                 \
    int n = N;                                                                 \
    int m = M;                                                                 \
    MARTA_CHECK_HEADERS(cond);                                                 \
    if (cond) {                                                                \
      printf("name,features,flops,");                                          \
      while (__polybench_papi_eventlist[i] != NULL) {                          \
        if (__polybench_papi_eventlist[i + 1] == NULL) {                       \
          printf("%s", __polybench_papi_eventlist[i++]);                       \
        } else {                                                               \
          printf("%s,", __polybench_papi_eventlist[i++]);                      \
        }                                                                      \
      }                                                                        \
      printf("\n");                                                            \
    }                                                                          \
    i = 0;                                                                     \
    polybench_papi_init();                                                     \
    while (__polybench_papi_eventlist[i] != NULL) {                            \
      n_func = 0;                                                              \
      polybench_prepare_instruments();

#undef MARTA_BENCHMARK_END
#define MARTA_BENCHMARK_END                                                    \
  i++;                                                                         \
  }                                                                            \
  int n_count = i;                                                             \
  for (int n = 0; n < n_func; ++n) {                                           \
    struct T val = values[n];                                                  \
    printf("%s,%s,%ld,", val.name, val.feat, val.flops);                       \
    for (int c = 0; c < n_count; ++c) {                                        \
      printf("%llu", val.counters[c]);                                         \
      if (c + 1 < n_count) {                                                   \
        printf(",");                                                           \
      }                                                                        \
    }                                                                          \
    printf("\n");                                                              \
  }                                                                            \
  polybench_papi_close();                                                      \
  return 0;                                                                    \
  }
#endif