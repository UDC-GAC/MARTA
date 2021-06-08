__tmp98 = _mm256_loadu_ps(&p[49]);
__tmp99 = _mm_load_ss(&p[48]);
__tmp104 = _mm256_loadu_ps(&p[16]);
__tmp112 = _mm256_loadu_ps(&p[0]);
__tmp124 = _mm256_shuffle_ps(__tmp98,_mm256_castps128_ps256(__tmp99),0xc4);DO_NOT_TOUCH(__tmp124);
__tmp125 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp99),__tmp104,0x8e);DO_NOT_TOUCH(__tmp125);
__tmp126 = _mm256_shuffle_ps(__tmp104,__tmp112,0x35);DO_NOT_TOUCH(__tmp126);
