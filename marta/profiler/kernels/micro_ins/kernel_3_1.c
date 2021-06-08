__tmp132 = _mm_load_ss(&p[18]);
__tmp137 = _mm256_loadu_ps(&p[16]);
__tmp145 = _mm256_loadu_ps(&p[0]);
__tmp148 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp132),__tmp137,0xe9);DO_NOT_TOUCH(__tmp148);
__tmp149 = _mm256_shuffle_ps(__tmp137,__tmp145,0x59);DO_NOT_TOUCH(__tmp149);
