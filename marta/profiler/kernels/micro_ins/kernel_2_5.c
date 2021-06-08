__tmp98 = _mm256_loadu_ps(&p[49]);
__tmp100 = _mm256_loadu_ps(&p[48]);
__tmp104 = _mm256_loadu_ps(&p[16]);
__tmp112 = _mm256_loadu_ps(&p[0]);
__tmp127 = _mm256_shuffle_ps(__tmp98,__tmp100,0x15);DO_NOT_TOUCH(__tmp127);
__tmp128 = _mm256_shuffle_ps(__tmp100,__tmp104,0xd5);DO_NOT_TOUCH(__tmp128);
__tmp129 = _mm256_shuffle_ps(__tmp104,__tmp112,0x75);DO_NOT_TOUCH(__tmp129);
