__tmp134 = _mm_load_ss(&p[17]);
__tmp137 = _mm256_loadu_ps(&p[16]);
__tmp145 = _mm256_loadu_ps(&p[0]);
__tmp146 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp134),__tmp137,0x0);DO_NOT_TOUCH(__tmp146);
__tmp147 = _mm256_shuffle_ps(__tmp137,__tmp145,0x55);DO_NOT_TOUCH(__tmp147);
