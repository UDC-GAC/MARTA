__tmp58 = _mm_load_ss(&p[49]);
__tmp61 = _mm256_loadu_ps(&p[48]);
__tmp65 = _mm256_loadu_ps(&p[32]);
__tmp69 = _mm256_loadu_ps(&p[16]);
__tmp73 = _mm256_loadu_ps(&p[0]);
__tmp82 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp58),__tmp61,0x9a);DO_NOT_TOUCH(__tmp82);
__tmp83 = _mm256_shuffle_ps(__tmp61,__tmp65,0x87);DO_NOT_TOUCH(__tmp83);
__tmp84 = _mm256_shuffle_ps(__tmp65,__tmp69,0xf0);DO_NOT_TOUCH(__tmp84);
__tmp85 = _mm256_shuffle_ps(__tmp69,__tmp73,0xc8);DO_NOT_TOUCH(__tmp85);
