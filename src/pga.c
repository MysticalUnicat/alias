#include <alias/pga.h>

alias_PGA_Grade1 alias_pga_e1 = ALIAS_PGA_TO_C(ALIAS_PGA_E1);
alias_PGA_Grade1 alias_pga_e2 = ALIAS_PGA_TO_C(ALIAS_PGA_E2);
alias_PGA_Grade1 alias_pga_e3 = ALIAS_PGA_TO_C(ALIAS_PGA_E3);
alias_PGA_Grade1 alias_pga_e4 = ALIAS_PGA_TO_C(ALIAS_PGA_E4);
alias_PGA_Grade2 alias_pga_e23 = ALIAS_PGA_TO_C(ALIAS_PGA_E23);
alias_PGA_Grade2 alias_pga_e31 = ALIAS_PGA_TO_C(ALIAS_PGA_E31);
alias_PGA_Grade2 alias_pga_e12 = ALIAS_PGA_TO_C(ALIAS_PGA_E12);
alias_PGA_Grade2 alias_pga_e43 = ALIAS_PGA_TO_C(ALIAS_PGA_E43);
alias_PGA_Grade2 alias_pga_e42 = ALIAS_PGA_TO_C(ALIAS_PGA_E42);
alias_PGA_Grade2 alias_pga_e41 = ALIAS_PGA_TO_C(ALIAS_PGA_E41);
alias_PGA_Grade3 alias_pga_e321 = ALIAS_PGA_TO_C(ALIAS_PGA_E321);
alias_PGA_Grade3 alias_pga_e124 = ALIAS_PGA_TO_C(ALIAS_PGA_E124);
alias_PGA_Grade3 alias_pga_e314 = ALIAS_PGA_TO_C(ALIAS_PGA_E314);
alias_PGA_Grade3 alias_pga_e234 = ALIAS_PGA_TO_C(ALIAS_PGA_E234);
alias_PGA_Grade4 alias_pga_e1234 = ALIAS_PGA_TO_C(ALIAS_PGA_E1234);

void test(void) {
  alias_pga_add(alias_pga_e1, alias_pga_e2);
}
