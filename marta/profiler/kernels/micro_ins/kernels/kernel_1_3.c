__tmp61 = _mm256_loadu_ps(&p[48]);
__tmp65 = _mm256_loadu_ps(&p[32]);
__tmp69 = _mm256_loadu_ps(&p[16]);
__tmp73 = _mm256_loadu_ps(&p[0]);
__tmp86 = _mm256_shuffle_ps(__tmp61,__tmp65,0xcd);DO_NOT_TOUCH(__tmp86);
__tmp87 = _mm256_shuffle_ps(__tmp65,__tmp69,0x1c);DO_NOT_TOUCH(__tmp87);
__tmp88 = _mm256_shuffle_ps(__tmp69,__tmp73,0x8b);DO_NOT_TOUCH(__tmp88);
