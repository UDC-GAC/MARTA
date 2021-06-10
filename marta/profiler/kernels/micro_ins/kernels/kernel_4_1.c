__tmp159 = _mm_load_ss(&p[6]);
__tmp172 = _mm256_loadu_ps(&p[0]);
__tmp174 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp159),__tmp172,0xbb);DO_NOT_TOUCH(__tmp174);
