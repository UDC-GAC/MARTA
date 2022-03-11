# Copyright 2022 Marcos Horro
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#!/bin/bash

#marta_profiler perf synthetic_matrices_2redux_fuse.yml
marta_profiler perf synthetic_matrices_4redux_fuse.yml -nsteps 1000 -nexec 20
marta_profiler perf synthetic_matrices_8redux_fuse.yml -nsteps 1000 -nexec 20
#marta_profiler perf synthetic_matrices_2redux_nofuse.yml
marta_profiler perf synthetic_matrices_4redux_nofuse.yml -nsteps 1000 -nexec 20
marta_profiler perf synthetic_matrices_8redux_nofuse.yml -nsteps 1000 -nexec 20