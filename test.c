#include <stdio.h>
#include <stdlib.h>

#include "x86utils.h"

int main(void)
{
  int e;

  printf("cpu-vendor: %s: %s\n",
         x86_get_vendor_id(),
         x86_get_brand_string());

#define FEAT(name, bit) if (e & (1 << bit)) printf(#name " "); else printf("!" #name " ");

  e = x86_get_features_1();
  printf("features-1: ");
  X86_FEATURES_1;
  printf("\n");

  e = x86_get_features_2();
  printf("features-2: ");
  X86_FEATURES_2;
  printf("\n");

  e = x86_get_features_3();
  printf("features-3: ");
  X86_FEATURES_3;
  printf("\n");

  e = x86_get_features_4();
  printf("features-4: ");
  X86_FEATURES_4;
  printf("\n");
  
  if (x86_has_sse())
    printf("x86_has_sse\n");
  
  if (x86_has_sse2())
    printf("x86_has_sse2\n");
  
  if (x86_has_sse3())
    printf("x86_has_sse3\n");
  
  if (x86_has_pclmuldq())
    printf("x86_has_pclmuldq\n");
  
  if (x86_has_aes())
    printf("x86_has_aes\n");

  return 0;
}

