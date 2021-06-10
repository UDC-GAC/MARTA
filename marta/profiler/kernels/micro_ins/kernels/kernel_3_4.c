__tmp133 = _mm256_loadu_ps(&p[18]);
__tmp137 = _mm256_loadu_ps(&p[16]);
__tmp145 = _mm256_loadu_ps(&p[0]);
__tmp153 = _mm256_shuffle_ps(__tmp133,__tmp137,0x90);DO_NOT_TOUCH(__tmp153);
__tmp154 = _mm256_shuffle_ps(__tmp137,__tmp145,0x3e);DO_NOT_TOUCH(__tmp154);
