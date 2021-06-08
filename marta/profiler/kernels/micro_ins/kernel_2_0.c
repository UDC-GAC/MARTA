__tmp99 = _mm_load_ss(&p[48]);
__tmp100 = _mm256_loadu_ps(&p[48]);
__tmp104 = _mm256_loadu_ps(&p[16]);
__tmp112 = _mm256_loadu_ps(&p[0]);
__tmp113 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp99),__tmp100,0xc0);DO_NOT_TOUCH(__tmp113);
__tmp114 = _mm256_shuffle_ps(__tmp100,__tmp104,0xe6);DO_NOT_TOUCH(__tmp114);
__tmp115 = _mm256_shuffle_ps(__tmp104,__tmp112,0x9f);DO_NOT_TOUCH(__tmp115);
