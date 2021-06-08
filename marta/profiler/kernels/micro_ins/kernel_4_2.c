__tmp157 = _mm_load_ss(&p[7]);
__tmp172 = _mm256_loadu_ps(&p[0]);
__tmp175 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp157),__tmp172,0x9c);DO_NOT_TOUCH(__tmp175);
