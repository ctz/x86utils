#ifndef X86UTILS_H
#define X86UTILS_H

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

#ifdef __cplusplus
extern "C" {
#endif

extern const char * x86_get_vendor_id(void);
extern const char * x86_get_brand_string(void);

#define FEAT(name, bit) x86_feature_##name = (1<<bit),

enum x86_features_1
{
  /* low ecx */
#define X86_FEATURES_1  \
  FEAT(OSXSAVE, 27)     \
  FEAT(XSAVE, 26)       \
  FEAT(AES, 25)         \
  FEAT(POPCNT, 23)      \
  FEAT(MOVBE, 22)       \
  FEAT(x2APIC, 21)      \
  FEAT(SSE4_2, 20)      \
  FEAT(SSE4_1, 19)      \
  FEAT(DCA, 18)         \
  FEAT(PDCM, 15)        \
  FEAT(xTPR, 14)        \
  FEAT(CMPXCHG16B, 13)  \
  FEAT(CNTXID, 10)      \
  FEAT(SSSE3, 9)        \
  FEAT(TM2, 8)          \
  FEAT(EST, 7)          \
  FEAT(SMX, 6)          \
  FEAT(VMX, 5)          \
  FEAT(DSCPL, 4)        \
  FEAT(Monitor, 3)      \
  FEAT(DTES64, 2)       \
  FEAT(PCLMULDQ, 1)     \
  FEAT(SSE3, 0)

  X86_FEATURES_1
};

enum x86_features_2
{
  /* high ecx */
#define X86_FEATURES_2  \
  FEAT(IBS, 10)         \
  FEAT(OSVW, 9)         \
  FEAT(3DNowPrefetch, 8)\
  FEAT(MisAlignSSE, 7)  \
  FEAT(SSE4A, 6)        \
  FEAT(ABM, 5)          \
  FEAT(AltMovCr8, 4)    \
  FEAT(ExpApicSpace, 3) \
  FEAT(SVM, 2)          \
  FEAT(CmpLegacy, 1)    \
  FEAT(LahfSahf, 0)

  X86_FEATURES_2
};

enum x86_features_3
{
#define X86_FEATURES_3  \
  FEAT(TM, 29)          \
  FEAT(HTT, 28)         \
  FEAT(SSE2, 26)        \
  FEAT(SSE, 25)         \
  FEAT(FXSR, 24)        \
  FEAT(MMX, 23)         \
  FEAT(CLFSH, 19)       \
  FEAT(PSE36, 17)       \
  FEAT(PAT, 16)         \
  FEAT(CMOV, 15)        \
  FEAT(MCA, 14)         \
  FEAT(PGE, 13)         \
  FEAT(MTRR, 12)        \
  FEAT(SysEnterExit, 11)\
  FEAT(APIC, 9)         \
  FEAT(CMPXCHG8B, 8)    \
  FEAT(MCE, 7)          \
  FEAT(PAE, 6)          \
  FEAT(MSR, 5)          \
  FEAT(TSC, 4)          \
  FEAT(PSE, 3)          \
  FEAT(DE, 2)           \
  FEAT(VME, 1)          \
  FEAT(FPU, 0)
  
  X86_FEATURES_3
};

enum x86_features_4
{
#define X86_FEATURES_4  \
  FEAT(3DNow, 31)       \
  FEAT(3DNowExt, 30)    \
  FEAT(LM, 29)          \
  FEAT(RDTSCP, 27)      \
  FEAT(Page1GB, 26)     \
  FEAT(FFXSR, 25)       \
  FEAT(MmxExt, 22)      \
  FEAT(NX, 20)          \
  FEAT(SysCallRet, 11)

  X86_FEATURES_4
};

#undef FEAT

extern enum x86_features_1 x86_get_features_1(void);
extern enum x86_features_2 x86_get_features_2(void);
extern enum x86_features_3 x86_get_features_3(void);
extern enum x86_features_4 x86_get_features_4(void);

#define x86_has_sse()       (x86_get_features_3() & x86_feature_SSE)
#define x86_has_sse2()      (x86_get_features_3() & x86_feature_SSE2)
#define x86_has_sse3()      (x86_get_features_1() & x86_feature_SSE3)
#define x86_has_pclmuldq()  (x86_get_features_1() & x86_feature_PCLMULDQ)
#define x86_has_aes()       (x86_get_features_1() & x86_feature_AES)

#ifdef __cplusplus
}
#endif

#endif
