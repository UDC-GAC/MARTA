__tmp97 = _mm_load_ss(&p[49]);
__tmp100 = _mm256_loadu_ps(&p[48]);
__tmp104 = _mm256_loadu_ps(&p[16]);
__tmp112 = _mm256_loadu_ps(&p[0]);
__tmp119 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp97),__tmp100,0x61);DO_NOT_TOUCH(__tmp119);
__tmp120 = _mm256_shuffle_ps(__tmp100,__tmp104,0x58);DO_NOT_TOUCH(__tmp120);
__tmp121 = _mm256_shuffle_ps(__tmp104,__tmp112,0x5);DO_NOT_TOUCH(__tmp121);
