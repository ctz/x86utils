/* x86utils - x86 processor interrogation routines
 * 
 * Copyright (c) 2009 Joseph Birr-Pixton
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 
#include <stdint.h>
#include "x86utils.h"

#ifdef _MSC_VER
# undef GNU_AS
#elif __GNUC__
# define GNU_AS
#else
# error "platform not supported"
#endif

static uint32_t cpuid(uint32_t op, uint32_t extra_ecx, uint32_t reg)
{
  uint32_t output[4];

#ifdef GNU_AS
  __asm__
     ("cpuid;"
         : "=a"(output[0]), "=b"(output[1]), "=c"(output[2]), "=d"(output[3])
         : "a"(op), "c"(extra_ecx)
     );
#else
  __asm
  {
    mov eax, op
    mov ecx, extra_ecx
    cpuid
    mov output, eax
    mov output+4, ebx
    mov output+8, ecx
    mov output+12, edx
  }
#endif

  return output[reg];
}

static uint32_t cpuid_eax(uint32_t eax, uint32_t ecx) { return cpuid(eax, ecx, 0); }
static uint32_t cpuid_ebx(uint32_t eax, uint32_t ecx) { return cpuid(eax, ecx, 1); }
static uint32_t cpuid_ecx(uint32_t eax, uint32_t ecx) { return cpuid(eax, ecx, 2); }
static uint32_t cpuid_edx(uint32_t eax, uint32_t ecx) { return cpuid(eax, ecx, 3); }

static uint32_t max_ext_cpuid_func(void)
{
  return cpuid_eax(0x80000000, 0) & 0x7fffffff;
}

static uint32_t max_cpuid_func(void)
{
  return cpuid_eax(0x00000000, 0);
}

const char * x86_get_vendor_id(void)
{
  static union {
    char bytes[13]; /* registers not null-terminated */
    uint32_t words[3];
  } data;

#ifdef GNU_AS
  __asm__
     ("xor %%eax, %%eax;"
      "cpuid;"
         : "=b"(data.words[0]),
           "=d"(data.words[1]), 
           "=c"(data.words[2])
         :
         : "eax"
     );
#else
  __asm
  {
    xor eax, eax
    cpuid
    mov data.words, ebx
    mov data.words+4, edx
    mov data.words+8, ecx
  }
#endif

  return data.bytes;
}

const char * x86_get_brand_string(void)
{
  static union {
    char bytes[3*4*4];
    uint32_t words[3*4];
  } data;

  if (max_ext_cpuid_func() < 4)
    return data.bytes;

#ifdef GNU_AS
  __asm__
     ("movl $0x80000002, %%eax;"
      "cpuid;"
         : "=a"(data.words[0]),
           "=b"(data.words[1]), 
           "=c"(data.words[2]), 
           "=d"(data.words[3])
     );
  __asm__
     ("movl $0x80000003, %%eax;"
      "cpuid;"
         : "=a"(data.words[4]),
           "=b"(data.words[5]), 
           "=c"(data.words[6]), 
           "=d"(data.words[7])
     );
  __asm__
     ("movl $0x80000004, %%eax;"
      "cpuid;"
         : "=a"(data.words[8]),
           "=b"(data.words[9]), 
           "=c"(data.words[10]), 
           "=d"(data.words[11])
     );
#else
  __asm
  {
    mov eax, 0x80000002
    cpuid
    mov data.words+0, eax
    mov data.words+4, ebx
    mov data.words+8, ecx
    mov data.words+12, edx

    mov eax, 0x80000003
    cpuid
    mov data.words+16, eax
    mov data.words+20, ebx
    mov data.words+24, ecx
    mov data.words+28, edx

    mov eax, 0x80000004
    cpuid
    mov data.words+32, eax
    mov data.words+36, ebx
    mov data.words+40, ecx
    mov data.words+44, edx
  }
#endif

  return data.bytes;
}

enum x86_features_1 x86_get_features_1(void)
{
  return cpuid_ecx(0x00000001, 0);
}

enum x86_features_2 x86_get_features_2(void)
{
  return cpuid_ecx(0x80000001, 0);
}

enum x86_features_3 x86_get_features_3(void)
{
  return cpuid_edx(0x00000001, 0);
}

enum x86_features_4 x86_get_features_4(void)
{
  return cpuid_edx(0x80000001, 0);
}

enum x86_features_5 x86_get_features_5(void)
{
  return cpuid_ebx(7, 0);
}
