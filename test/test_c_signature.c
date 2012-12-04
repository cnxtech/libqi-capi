

//#include <gtest/gtest.h>
#include <qimessaging/c/signature_c.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define check(retcode, str) \
{ \
  printf("current signature: %s, ret: %d\n", qi_signature_current(sig), ret); \
  assert(ret == retcode); \
  verify(sig, str); \
  printf("\n");\
  }

void verify(qi_signature_t *sig, char *current)
{
  assert(sig);
  if (qi_signature_current(sig))
    assert(!strcmp(qi_signature_current(sig), current));
  else
    assert(qi_signature_current(sig) == current);
}

//TEST(TestCSignature, BasicPrint) {
void test() {
  qi_signature_t *sig;
  int             ret;

  printf("Signature: Us**S\n");
  sig = qi_signature_create("Us**S");
  ret = qi_signature_next(sig); check(2, 0);
  ret = qi_signature_next(sig); check(2, 0);
  qi_signature_destroy(sig);

  printf("Signature: s\n");
  sig = qi_signature_create("s");
  ret = qi_signature_next(sig); check(0, "s");
  ret = qi_signature_next(sig); check(1, "");
  ret = qi_signature_next(sig); check(1, "");
  qi_signature_destroy(sig);


  printf("Signature: s[s]{ss}\n");
  sig = qi_signature_create("s[s]{ss}");
  ret = qi_signature_next(sig); check(0, "s");
  ret = qi_signature_next(sig); check(0, "[s]");
  ret = qi_signature_next(sig); check(0, "{ss}");
  ret = qi_signature_next(sig); check(1, "");
  ret = qi_signature_next(sig); check(1, "");
  qi_signature_destroy(sig);


  printf("SubSignature: [s[s]{ss}]\n");
  sig = qi_signature_create_subsignature("[s[s]{ss}]");
  ret = qi_signature_next(sig); check(0, "s");
  ret = qi_signature_next(sig); check(0, "[s]");
  ret = qi_signature_next(sig); check(0, "{ss}");
  ret = qi_signature_next(sig); check(1, "");
  ret = qi_signature_next(sig); check(1, "");
  qi_signature_destroy(sig);
}

void test_split() {
  char buffer[512];
  int size = 512;
  int ret;

  ret = qi_signature_get_name("poutre::i:i", buffer, size);
  printf("name: %d %d %s\n", ret, size, buffer);
  ret = qi_signature_get_return("poutre::i:i", buffer, size);
  printf("name: %d %d %s\n", ret, size, buffer);
  ret = qi_signature_get_params("poutre::i:i", buffer, size);
  printf("name: %d %d %s\n", ret, size, buffer);
}

int main(void) {
  test_split();
  return 0;
}
