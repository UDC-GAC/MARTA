__tmp0 = _mm_load_ss(&p[112]);
__tmp2 = _mm_load_ss(&p[96]);
__tmp4 = _mm_load_ss(&p[80]);
__tmp6 = _mm_load_ss(&p[64]);
__tmp8 = _mm_load_ss(&p[48]);
__tmp11 = _mm256_loadu_ps(&p[32]);
__tmp12 = _mm_load_ss(&p[16]);
__tmp14 = _mm_load_ss(&p[0]);
__tmp44 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp0),_mm256_castps128_ps256(__tmp2),0x87);DO_NOT_TOUCH(__tmp44);
__tmp45 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp2),_mm256_castps128_ps256(__tmp4),0x5a);DO_NOT_TOUCH(__tmp45);
__tmp46 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp4),_mm256_castps128_ps256(__tmp6),0xeb);DO_NOT_TOUCH(__tmp46);
__tmp47 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp6),_mm256_castps128_ps256(__tmp8),0x50);DO_NOT_TOUCH(__tmp47);
__tmp48 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp8),__tmp11,0x0);DO_NOT_TOUCH(__tmp48);
__tmp49 = _mm256_shuffle_ps(__tmp11,_mm256_castps128_ps256(__tmp12),0x38);DO_NOT_TOUCH(__tmp49);
__tmp50 = _mm256_shuffle_ps(_mm256_castps128_ps256(__tmp12),_mm256_castps128_ps256(__tmp14),0x28);DO_NOT_TOUCH(__tmp50);
