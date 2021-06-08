__tmp100 = _mm256_loadu_ps(&p[48]);
__tmp104 = _mm256_loadu_ps(&p[16]);
__tmp112 = _mm256_loadu_ps(&p[0]);
__tmp122 = _mm256_shuffle_ps(__tmp100,__tmp104,0x8a);DO_NOT_TOUCH(__tmp122);
__tmp123 = _mm256_shuffle_ps(__tmp104,__tmp112,0xf3);DO_NOT_TOUCH(__tmp123);
