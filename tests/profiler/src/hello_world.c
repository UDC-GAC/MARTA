#include <stdio.h>

int main() {
  FILE *fp;
  fp = fopen("/tmp/___marta_results.txt", "w");
  fprintf(fp, "10000\n");
  fclose(fp);
  return 0;
}