// atoi
static inline int tabula_is_digit(int c) {
  return (c >= '0') && (c <= '9') ? (c - '0') + 1 : 0;
}

intmax_t tabula_atoi(const char * restrict in, const char ** restrict out_ptr) {
  intmax_t i = 0;
  intmax_t n = (*in == '-' ? (in++, -1) : *in == '+' ? (in++, 1) : 1);
  int c;
  while((c = tabula_is_digit(*in))) {
    i = i * 10 + (c - 1);
    in++;
  }
  if(out_ptr != NULL) {
    *out_ptr = in;
  }
  return n * i;
}

