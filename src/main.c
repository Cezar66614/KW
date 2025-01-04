#define KE_IMPL
#include "ke.h"

#define ABNF_IMPL
#include "abnf.h"

int main(int argc, char **argv) {
  ke_init();
  ke_push_scope(true);

  ke_pop_scope();
  ke_free();
  return 0;
}
