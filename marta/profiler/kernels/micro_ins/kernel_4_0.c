__tmp161 = _mm_load_ss(&p[5]);
__tmp172 = _mm256_loadu_ps(&p[0]);
__tmp173 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp161),__tmp172,0xc1);DO_NOT_TOUCH(__tmp173);
