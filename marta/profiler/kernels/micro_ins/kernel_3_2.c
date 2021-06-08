__tmp130 = _mm_load_ss(&p[19]);
__tmp137 = _mm256_loadu_ps(&p[16]);
__tmp145 = _mm256_loadu_ps(&p[0]);
__tmp150 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp130),__tmp137,0x6e);DO_NOT_TOUCH(__tmp150);
__tmp151 = _mm256_shuffle_ps(__tmp137,__tmp145,0x8b);DO_NOT_TOUCH(__tmp151);
