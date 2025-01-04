#ifndef KE_H
#define KE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifndef KE_OUT
#define KE_OUT stderr
#endif // KE_OUT

#define KE_ERROR(message) (ke_error((message), __FILE__, __LINE__))
#define KE_ERROR_KILL(message) (ke_error_kill((message), __FILE__, __LINE__))
#define KE_ERROR_EXIT(message) (ke_error_exit((message), __FILE__, __LINE__))

/* Function that does the set up of the KE error-handling library */
void ke_init(void);
/* Function that does the clean up of the KE error-handling library */
void ke_free(void);

/* Function that adds a new scope to handle */
void ke_push_scope(bool function_scope);
/* Function that removes the newest scope, it gets handled */
void ke_pop_scope(void);
/* Function that removes the newest scope, it doesn't get handled */
void ke_pop_scope_no(void);

/* Function that adds a new element to the current scope to handle
  One and only one of the two parameters must be set
*/
void ke_push_elem(void *pointer, void (*function)(void));
/* Function that removes the newest element from the current scope, it gets handled */
void ke_pop_elem(void);
/* Function that removes the newest element from the current scope, it doesn't get handled */
void ke_pop_elem_no(void);

/* Function that prints an error message to the output and handles all scopes until and including the first scope added that is marked as a function scope (gets f*ed by returns) */
void ke_error(const char *message, const char *file, int line);
/* Function that prints an error message to the output and handles all scopes */
void ke_error_kill(const char *message, const char *file, int line);
/* Function that prints an error message to the output and handles all scopes and exits the whole application */
void ke_error_exit(const char *message, const char *file, int line);

#ifdef KE_IMPL
#undef KE_IMPL

typedef enum ke_elem_type_enum {
  KE_TYPE_UNUSED = 0,
  KE_TYPE_POINTER,
  KE_TYPE_FUNCTION
} KE_ELEM_TYPE;

typedef struct ke_elem_struct {
  union ke_elem_union {
    void *point;
    void (*func)(void);
  } value;
  KE_ELEM_TYPE elem_type;
} ke_elem_t;

typedef struct ke_scope_struct {
  bool function_scope;
  ke_elem_t *elems;
  size_t elems_count, elems_space;
} ke_scope_t;

typedef struct ke_stack_struct {
  ke_scope_t *scopes;
  size_t scopes_count, scopes_space;
} ke_stack_t;

ke_stack_t ke_stack;


void ke_free_scope(size_t index) {
  while (ke_stack.scopes[index].elems_count) ke_pop_elem();

  if ((ke_stack.scopes[index].elems != NULL) && ke_stack.scopes[index].elems_space) free(ke_stack.scopes[index].elems);

  ke_stack.scopes[index].elems = NULL;
  ke_stack.scopes[index].elems_count = 0;
  ke_stack.scopes[index].elems_space = 0;
}

void ke_init(void) {
  ke_stack.scopes = NULL;
  ke_stack.scopes_count = 0;
  ke_stack.scopes_space = 0;
}
void ke_free(void) {
  size_t i;
  for (i = 0; i < ke_stack.scopes_space; ++i) ke_free_scope(i);
  if ((ke_stack.scopes != NULL) && ke_stack.scopes_space) free(ke_stack.scopes);

  ke_stack.scopes = NULL;
  ke_stack.scopes_count = 0;
  ke_stack.scopes_space = 0;
}

void ke_push_scope(bool function_scope) {
  if (ke_stack.scopes_count == ke_stack.scopes_space) {
    if (!(ke_stack.scopes_space)) ke_stack.scopes_space = 1;

    ke_stack_t temp = ke_stack;

    ke_stack.scopes = (ke_scope_t *)realloc(ke_stack.scopes, sizeof(ke_scope_t) * ke_stack.scopes_space * 2);
    if (ke_stack.scopes == NULL) {
      fprintf(KE_OUT, "ERROR in %s at %d: Couldn't allocate space for new KE scope. This might help: %s\n", __FILE__, __LINE__, strerror(errno));

      ke_stack = temp;
      ke_free();
      exit(1);
    }

    ke_stack.scopes_space *= 2;

    size_t i;
    for (i = ke_stack.scopes_count; i < ke_stack.scopes_space; ++i) {
      ke_stack.scopes[i].function_scope = false;
      ke_stack.scopes[i].elems = NULL;
      ke_stack.scopes[i].elems_count = 0;
      ke_stack.scopes[i].elems_space = 0;
    }
  }

  ke_stack.scopes[ke_stack.scopes_count].function_scope = function_scope;
  ke_stack.scopes[ke_stack.scopes_count].elems_count = 0;

  ++(ke_stack.scopes_count);
}
void ke_pop_scope(void) {
  if (!(ke_stack.scopes_count)) return;

  while (ke_stack.scopes[ke_stack.scopes_count - 1].elems_count) ke_pop_elem();

  ke_stack.scopes[ke_stack.scopes_count - 1].function_scope = false;
  ke_stack.scopes[ke_stack.scopes_count - 1].elems_count = 0;

  --(ke_stack.scopes_count);
}
void ke_pop_scope_no(void) {
  if (!(ke_stack.scopes_count)) return;

  while (ke_stack.scopes[ke_stack.scopes_count - 1].elems_count) ke_pop_elem_no();

  ke_stack.scopes[ke_stack.scopes_count - 1].function_scope = false;
  ke_stack.scopes[ke_stack.scopes_count - 1].elems_count = 0;

  --(ke_stack.scopes_count);
}

void ke_push_elem(void *pointer, void (*function)(void)) {
  if (!(ke_stack.scopes_count)) return;

  if (ke_stack.scopes[ke_stack.scopes_count - 1].elems_count == ke_stack.scopes[ke_stack.scopes_count - 1].elems_space) {
    if (!(ke_stack.scopes[ke_stack.scopes_count - 1].elems_space)) ke_stack.scopes[ke_stack.scopes_count - 1].elems_space = 1;

    ke_stack_t temp = ke_stack;

    ke_stack.scopes[ke_stack.scopes_count - 1].elems = (ke_elem_t *)realloc(ke_stack.scopes[ke_stack.scopes_count - 1].elems, sizeof(ke_elem_t) * ke_stack.scopes[ke_stack.scopes_count - 1].elems_space * 2);
    if (ke_stack.scopes[ke_stack.scopes_count - 1].elems == NULL) {
      fprintf(KE_OUT, "ERROR in %s at %d: Couldn't allocate space for new KE element. This might help: %s\n", __FILE__, __LINE__, strerror(errno));

      ke_stack = temp;
      ke_free();
      exit(1);
    }

    ke_stack.scopes[ke_stack.scopes_count - 1].elems_space *= 2;

    size_t i;
    for (i = ke_stack.scopes[ke_stack.scopes_count - 1].elems_count; i < ke_stack.scopes[ke_stack.scopes_count - 1].elems_space; ++i) {
      ke_stack.scopes[ke_stack.scopes_count - 1].elems[i].value.point = NULL;
      ke_stack.scopes[ke_stack.scopes_count - 1].elems[i].value.func = NULL;
      ke_stack.scopes[ke_stack.scopes_count - 1].elems[i].elem_type = KE_TYPE_UNUSED;
    }
  }

  if (pointer != NULL) {
    ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count].value.point = pointer;
    ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count].elem_type = KE_TYPE_POINTER;
  } else if (function != NULL) {
    ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count].value.func = function;
    ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count].elem_type = KE_TYPE_FUNCTION;
  }
  else return;

  ++(ke_stack.scopes[ke_stack.scopes_count - 1].elems_count);
}
void ke_pop_elem(void) {
  if (!(ke_stack.scopes[ke_stack.scopes_count - 1].elems_count)) return;

  if (ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count - 1].elem_type == KE_TYPE_POINTER) {
    if (ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count - 1].value.point != NULL) {
      free(ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count - 1].value.point);
    }
  } else if (ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count - 1].elem_type == KE_TYPE_FUNCTION) {
    if (ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count - 1].value.func != NULL) {
      ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count - 1].value.func();
    }
  }

  ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count - 1].value.point = NULL;
  ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count - 1].value.func = NULL;
  ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count - 1].elem_type = KE_TYPE_UNUSED;

  if (ke_stack.scopes[ke_stack.scopes_count - 1].elems_count) --(ke_stack.scopes[ke_stack.scopes_count - 1].elems_count);
}
void ke_pop_elem_no(void) {
  if (!(ke_stack.scopes[ke_stack.scopes_count - 1].elems_count)) return;

  ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count - 1].value.point = NULL;
  ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count - 1].value.func = NULL;
  ke_stack.scopes[ke_stack.scopes_count - 1].elems[ke_stack.scopes[ke_stack.scopes_count - 1].elems_count - 1].elem_type = KE_TYPE_UNUSED;

  if (ke_stack.scopes[ke_stack.scopes_count - 1].elems_count) --(ke_stack.scopes[ke_stack.scopes_count - 1].elems_count);
}

void ke_error(const char *message, const char *file, int line) {
  fprintf(KE_OUT, "ERROR in %s at %d: %s. This might help: %s\n", file, line, message, strerror(errno));

  while (ke_stack.scopes_count && !(ke_stack.scopes[ke_stack.scopes_count - 1].function_scope)) ke_pop_scope();
  if (ke_stack.scopes_count && ke_stack.scopes[ke_stack.scopes_count - 1].function_scope) ke_pop_scope();
}
void ke_error_kill(const char *message, const char *file, int line) {
  fprintf(KE_OUT, "ERROR in %s at %d: %s. This might help: %s\n", file, line, message, strerror(errno));

  while (ke_stack.scopes_count) ke_pop_scope();
}
void ke_error_exit(const char *message, const char *file, int line) {
  ke_error_kill(message, file, line);
  ke_free();
  exit(1);
}


#endif // KE_IMPL

#endif // KE_H
