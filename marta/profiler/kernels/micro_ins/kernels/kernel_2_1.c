__tmp97 = _mm_load_ss(&p[49]);
__tmp99 = _mm_load_ss(&p[48]);
__tmp104 = _mm256_loadu_ps(&p[16]);
__tmp112 = _mm256_loadu_ps(&p[0]);
__tmp116 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp97),_mm256_castps128_ps256(__tmp99),0x68);DO_NOT_TOUCH(__tmp116);
__tmp117 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp99),__tmp104,0x8e);DO_NOT_TOUCH(__tmp117);
__tmp118 = _mm256_shuffle_ps(__tmp104,__tmp112,0x1a);DO_NOT_TOUCH(__tmp118);
