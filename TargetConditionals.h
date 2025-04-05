/*
 * Copyright (c) 2000-2008 by Apple Inc.. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 * Portions Copyright (c) 2025 Zormeister. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/*
     File:       TargetConditionals.h
 
     Contains:   Autoconfiguration of TARGET_ conditionals for Mac OS X and iPhone
     
                 Note:  TargetConditionals.h in 3.4 Universal Interfaces works
                        with all compilers.  This header only recognizes compilers
                        known to run on Mac OS X.
  
*/

/* ZORMEISTER: This is a modified version of the header from CarbonHeaders. */

#ifndef __TARGETCONDITIONALS__
#define __TARGETCONDITIONALS__
/****************************************************************************************************

    TARGET_CPU_*    
    These conditionals specify which microprocessor instruction set is being
    generated.  At most one of these is true, the rest are false.

        TARGET_CPU_PPC          - Compiler is generating PowerPC instructions for 32-bit mode
        TARGET_CPU_PPC64        - Compiler is generating PowerPC instructions for 64-bit mode
        TARGET_CPU_68K          - Compiler is generating 680x0 instructions
        TARGET_CPU_X86          - Compiler is generating x86 instructions for 32-bit mode
        TARGET_CPU_X86_64       - Compiler is generating x86 instructions for 64-bit mode
        TARGET_CPU_ARM          - Compiler is generating ARM instructions for 32-bit mode
        TARGET_CPU_ARM64        - Compiler is generating ARM instructions for 64-bit mode
        TARGET_CPU_MIPS         - Compiler is generating MIPS instructions for 32-bit mode
        TARGET_CPU_MIPS64       - Compiler is generating MIPS instructions for 64-bit mode
        TARGET_CPU_SPARC        - Compiler is generating Sparc instructions
        TARGET_CPU_ALPHA        - Compiler is generating Dec Alpha instructions
        TARGET_CPU_WASM32       - Compiler is generating WebAssembly instructions for 32-bit mode


    TARGET_OS_* 
    These conditionals specify in which Operating System the generated code will
    run. The MAC/WIN32/UNIX conditionals are mutually exclusive.  The EMBEDDED/IPHONE 
	conditionals are variants of TARGET_OS_MAC. 

        TARGET_OS_MAC           - Generated code will run under any Darwin based OS (macOS, iOS, etc)
            TARGET_OS_DRIVERKIT     - Generated code will run under the DriverKit runtime

            TARGET_OS_EXCLAVECORE   - Generated code will run under the ExclaveCore runtime

            TARGET_OS_EXCLAVEKIT    - Generated code will run under the ExclaveKit runtime

            TARGET_OS_IPHONE        - Generated code will run under any embedded Apple OS
                TARGET_OS_BRIDGE        - Generated code will run under bridgeOS
                TARGET_OS_IOS           - Generated code will run under iOS/iPadOS (or variants)
                TARGET_OS_TV            - Generated code will run under tvOS
                TARGET_OS_VISION        - Generated code will run under visionOS
                TARGET_OS_WATCH         - Generated code will run under watchOS
            
            TARGET_OS_SIMULATOR     - Generated code will run under any simulator platform, such as
                                      the iPhone Simualtor or watchOS Simulator

            TARGET_OS_EMBEDDED      - Generated code will run under any embedded Apple OS, alternative
                                      to TARGET_OS_IPHONE

        TARGET_OS_WINDOWS       - Generated code will run under a Windows NT based OS
            TARGET_OS_WIN32         - Generated code will run under a 32-bit Windows environment
            TARGET_OS_EFI           - Generated code will run under a UEFI environment

        TARGET_OS_UNIX          - Generated code will run under a non Mac OS X UNIX OS

        TARGET_OS_LINUX         - Generated code will run under a Linux system, be it GNU or musl
            TARGET_OS_ANDROID       - Generated code will run under an Android based OS
            TARGET_OS_CYGWIN        - Generated code will run under a Cygwin environment

        TARGET_OS_WASI          - Generated code will run under a WebAssembly System Interface environment

        TARGET_OS_BSD           - Generated code will run under a BSD based OS (that's not Darwin)


    TARGET_RT_* 
    These conditionals specify in which runtime the generated code will
    run. This is needed when the OS and CPU support more than one runtime
    (e.g. Mac OS X supports CFM and mach-o).

        TARGET_RT_LITTLE_ENDIAN - Generated code uses little endian format for integers
        TARGET_RT_BIG_ENDIAN    - Generated code uses big endian format for integers    
        TARGET_RT_64_BIT        - Generated code uses 64-bit pointers    
        TARGET_RT_MAC_CFM       - TARGET_OS_MAC is true and CFM68K or PowerPC CFM (TVectors) are used
        TARGET_RT_MAC_MACHO     - TARGET_OS_MAC is true and Mach-O/dyld runtime is used


        

****************************************************************************************************/

/* use these funny lil macros */

// research sources:
// - https://stackoverflow.com/questions/12132933/preprocessor-macro-for-os-x-targets
// - https://epir.at/2019/10/30/api-availability-and-target-conditionals/
// - https://chaosinmotion.com/2021/08/02/things-to-remember-compiler-conditionals-for-macos-ios-etc/

#ifdef __has_builtin
    #if __has_builtin(__is_target_arch)
        #if __has_builtin(__is_target_environment)
            #if __has_builtin(__is_target_os)
                #if __has_builtin(__is_target_vendor)
                    #define DYNAMIC_TARGETS_SELECTED 1

                    #if __is_target_vendor(apple)
                        #if __is_target_os(ios) && __is_target_environment(macabi)
                            #define TARGET_OS_MAC               1
                            #define TARGET_OS_IOS               1
                            #define TARGET_OS_IPHONE            1
                            #define TARGET_OS_MACCATALYST       1
                            #define TARGET_OS_UIKITFORMAC       1
                        #endif

                        #if __is_target_os(driverkit)
                            #define TARGET_OS_MAC               1
                            #define TARGET_OS_DRIVERKIT         1 /* Darwin 19+ */
                        #endif

                        #if __is_target_os(ios)
                            #define TARGET_OS_MAC               1
                            #define TARGET_OS_IOS               1
                            #define TARGET_OS_IPHONE            1
                        #endif

                        #if __is_target_environment(simulator) && !(__is_target_os(macos) || __is_target_os(driverkit))
                            /* It's impossible for a macOS/DriverKit simulator to exist unless someone makes one. */
                            #define TARGET_OS_SIMULATOR         1
                        #endif

                        #if __is_target_os(macos)
                            #define TARGET_OS_MAC               1
                            #define TARGET_OS_OSX               1
                        #endif

                        #if __is_target_os(bridgeos)
                            #define TARGET_OS_MAC               1
                            #define TARGET_OS_BRIDGE            1
                            #define TARGET_OS_IPHONE            1
                        #endif

                        #if __is_target_os(tvos)
                            #define TARGET_OS_MAC               1
                            #define TARGET_OS_TV                1
                            #define TARGET_OS_IPHONE            1
                        #endif

                        #if __is_target_os(xros)
                            #define TARGET_OS_MAC               1
                            #define TARGET_OS_IPHONE            1
                            #define TARGET_OS_IOS               1
                            #define TARGET_OS_VISION            1
                        #endif

                        #if __is_target_environment(exclavecore)
                            #define TARGET_OS_EXCLAVECORE       1
                        #endif

                        #if __is_target_environment(exclavekit)
                            #define TARGET_OS_EXCLAVEKIT        1
                        #endif
                    #else
                        #if __is_target_vendor(pc)
                            #if __is_target_os(linux) // This is actually REALLY useful for me. Might deploy this variant of TargetConditionals to my projects.
                                #define TARGET_OS_LINUX             1

                                #if __is_target_environment(android)
                                    #define TARGET_OS_ANDROID       1
                                #endif

                                #if __is_target_environment(cygwin)
                                    #define TARGET_OS_CYGWIN        1
                                #endif
                            #endif

                            #if __is_target_os(windows)
                                #if __is_target_arch(i386)
                                    #define TARGET_OS_WIN32         1
                                #endif

                                #define TARGET_OS_WINDOWS           1
                            #endif

                            #if __is_target_os(uefi)
                                #if __is_target_arch(i386)
                                    #define TARGET_OS_WIN32         1
                                #endif

                                #define TARGET_OS_WINDOWS           1
                                #define TARGET_OS_EFI               1
                            #endif

                            #if __is_target_os(freebsd) || __is_target_os(kfreebsd) || __is_target_os(netbsd) || __is_target_os(openbsd)
                                #define TARGET_OS_BSD               1
                            #endif
                        #endif
                    #endif

                    #ifndef TARGET_OS_BRIDGE
                        #define TARGET_OS_BRIDGE                0
                    #endif

                    #ifndef TARGET_OS_BSD
                        #define TARGET_OS_BSD                   0
                    #endif

                    #ifndef TARGET_OS_DRIVERKIT
                        #define TARGET_OS_DRIVERKIT             0
                    #endif

                    #ifndef TARGET_OS_EXCLAVECORE
                        #define TARGET_OS_EXCLAVECORE           0
                    #endif

                    #ifndef TARGET_OS_EXCLAVEKIT
                        #define TARGET_OS_EXCLAVEKIT            0
                    #endif

                    #ifndef TARGET_OS_IOS
                        #define TARGET_OS_IOS                   0
                    #endif

                    #ifndef TARGET_OS_IPHONE
                        #define TARGET_OS_IPHONE                0
                    #endif

                    #ifndef TARGET_OS_MACCATALYST
                        #define TARGET_OS_MACCATALYST           0
                        #define TARGET_OS_UIKITFORMAC           0
                    #endif

                    #ifndef TARGET_OS_OSX
                        #define TARGET_OS_OSX                   0
                    #endif

                    #ifndef TARGET_OS_SIMULATOR
                        #define TARGET_OS_SIMULATOR             0
                    #endif

                    #ifndef TARGET_OS_TV
                        #define TARGET_OS_TV                    0
                    #endif

                    #ifndef TARGET_OS_VISION
                        #define TARGET_OS_VISION                0
                    #endif

                    #ifndef TARGET_OS_WATCH
                        #define TARGET_OS_WATCH                 0
                    #endif

                    #ifndef TARGET_OS_WINDOWS
                        #define TARGET_OS_EFI                   0
                        #define TARGET_OS_WIN32                 0
                        #define TARGET_OS_WINDOWS               0
                    #endif

                    #ifndef TARGET_OS_LINUX
                        #define TARGET_OS_LINUX                 0
                        #define TARGET_OS_ANDROID               0
                        #define TARGET_OS_CYGWIN                0
                    #endif

                    /* Account for the 'deprecated' macros */
                    #define TARGET_IPHONE_SIMULATOR             TARGET_OS_SIMULATOR
                    #define TARGET_OS_NANO                      TARGET_OS_WATCH
                    #define TARGET_OS_EMBEDDED                  TARGET_OS_IPHONE
                #endif
            #endif
        #endif
    #endif
#endif

#ifndef DYNAMIC_TARGETS_SELECTED
/* Fallback. */
#undef TARGET_OS_OSX
#define TARGET_OS_OSX           1
#endif

#if defined(__has_builtin)
    #if __has_builtin(__is_target_arch)
        #if __is_target_arch(arm)
            #define TARGET_CPU_PPC          0
            #define TARGET_CPU_PPC64        0
            #define TARGET_CPU_68K          0
            #define TARGET_CPU_X86          0
            #define TARGET_CPU_X86_64       0
            #define TARGET_CPU_ARM          1
            #define TARGET_CPU_ARM64        0
            #define TARGET_CPU_MIPS         0
            #define TARGET_CPU_MIPS64       0
            #define TARGET_CPU_SPARC        0
            #define TARGET_CPU_S390X        0
            #define TARGET_CPU_ALPHA        0
            #define TARGET_CPU_WASM32       0
        #endif

        #if __is_target_arch(arm64) || __is_target_arch(arm64e) || __is_target_arch(arm64_32)
            #define TARGET_CPU_PPC          0
            #define TARGET_CPU_PPC64        0
            #define TARGET_CPU_68K          0
            #define TARGET_CPU_X86          0
            #define TARGET_CPU_X86_64       0
            #define TARGET_CPU_ARM          0
            #define TARGET_CPU_ARM64        1
            #define TARGET_CPU_MIPS         0
            #define TARGET_CPU_MIPS64       0
            #define TARGET_CPU_S390X        0
            #define TARGET_CPU_SPARC        0
            #define TARGET_CPU_ALPHA        0
            #define TARGET_CPU_WASM32       0
        #endif

        #if __is_target_arch(i386)
            #define TARGET_CPU_PPC          0
            #define TARGET_CPU_PPC64        0
            #define TARGET_CPU_68K          0
            #define TARGET_CPU_X86          1
            #define TARGET_CPU_X86_64       0
            #define TARGET_CPU_ARM          0
            #define TARGET_CPU_ARM64        0
            #define TARGET_CPU_MIPS         0
            #define TARGET_CPU_MIPS64       0
            #define TARGET_CPU_S390X        0
            #define TARGET_CPU_SPARC        0
            #define TARGET_CPU_ALPHA        0
            #define TARGET_CPU_WASM32       0
        #endif

        #if __is_target_arch(ppc)
            #define TARGET_CPU_PPC          1
            #define TARGET_CPU_PPC64        0
            #define TARGET_CPU_68K          0
            #define TARGET_CPU_X86          0
            #define TARGET_CPU_X86_64       0
            #define TARGET_CPU_ARM          0
            #define TARGET_CPU_ARM64        0
            #define TARGET_CPU_MIPS         0
            #define TARGET_CPU_MIPS64       0
            #define TARGET_CPU_S390X        0
            #define TARGET_CPU_SPARC        0
            #define TARGET_CPU_ALPHA        0
            #define TARGET_CPU_WASM32       0
        #endif

        #if __is_target_arch(ppc64)
            #define TARGET_CPU_PPC          0
            #define TARGET_CPU_PPC64        1
            #define TARGET_CPU_68K          0
            #define TARGET_CPU_X86          0
            #define TARGET_CPU_X86_64       0
            #define TARGET_CPU_ARM          0
            #define TARGET_CPU_ARM64        0
            #define TARGET_CPU_MIPS         0
            #define TARGET_CPU_MIPS64       0
            #define TARGET_CPU_S390X        0
            #define TARGET_CPU_SPARC        0
            #define TARGET_CPU_ALPHA        0
            #define TARGET_CPU_WASM32       0
        #endif

        #if __is_target_arch(m68k)
            #define TARGET_CPU_PPC          0
            #define TARGET_CPU_PPC64        0
            #define TARGET_CPU_68K          1
            #define TARGET_CPU_X86          0
            #define TARGET_CPU_X86_64       0
            #define TARGET_CPU_ARM          0
            #define TARGET_CPU_ARM64        0
            #define TARGET_CPU_MIPS         0
            #define TARGET_CPU_MIPS64       0
            #define TARGET_CPU_S390X        0
            #define TARGET_CPU_SPARC        0
            #define TARGET_CPU_ALPHA        0
            #define TARGET_CPU_WASM32       0
        #endif

        #if __is_target_arch(mips)
            #define TARGET_CPU_PPC          0
            #define TARGET_CPU_PPC64        0
            #define TARGET_CPU_68K          0
            #define TARGET_CPU_X86          0
            #define TARGET_CPU_X86_64       0
            #define TARGET_CPU_ARM          0
            #define TARGET_CPU_ARM64        0
            #define TARGET_CPU_MIPS         1
            #define TARGET_CPU_MIPS64       0
            #define TARGET_CPU_S390X        0
            #define TARGET_CPU_SPARC        0
            #define TARGET_CPU_ALPHA        0
            #define TARGET_CPU_WASM32       0
        #endif

        #if __is_target_arch(mips64)
            #define TARGET_CPU_PPC          0
            #define TARGET_CPU_PPC64        0
            #define TARGET_CPU_68K          0
            #define TARGET_CPU_X86          0
            #define TARGET_CPU_X86_64       0
            #define TARGET_CPU_ARM          0
            #define TARGET_CPU_ARM64        0
            #define TARGET_CPU_MIPS         0
            #define TARGET_CPU_MIPS64       1
            #define TARGET_CPU_S390X        0
            #define TARGET_CPU_SPARC        0
            #define TARGET_CPU_ALPHA        0
            #define TARGET_CPU_WASM32       0
        #endif

        #if __is_target_arch(s390)
            #define TARGET_CPU_PPC          0
            #define TARGET_CPU_PPC64        0
            #define TARGET_CPU_68K          0
            #define TARGET_CPU_X86          0
            #define TARGET_CPU_X86_64       0
            #define TARGET_CPU_ARM          0
            #define TARGET_CPU_ARM64        0
            #define TARGET_CPU_MIPS         0
            #define TARGET_CPU_MIPS64       0
            #define TARGET_CPU_S390X        1
            #define TARGET_CPU_SPARC        0
            #define TARGET_CPU_ALPHA        0
            #define TARGET_CPU_WASM32       0
        #endif

        #if __is_target_arch(sparc)
            #define TARGET_CPU_PPC          0
            #define TARGET_CPU_PPC64        0
            #define TARGET_CPU_68K          0
            #define TARGET_CPU_X86          0
            #define TARGET_CPU_X86_64       0
            #define TARGET_CPU_ARM          0
            #define TARGET_CPU_ARM64        0
            #define TARGET_CPU_MIPS         0
            #define TARGET_CPU_MIPS64       0
            #define TARGET_CPU_S390X        0
            #define TARGET_CPU_SPARC        1
            #define TARGET_CPU_ALPHA        0
            #define TARGET_CPU_WASM32       0
        #endif

        #if __is_target_arch(x86_64)
            #define TARGET_CPU_PPC          0
            #define TARGET_CPU_PPC64        0
            #define TARGET_CPU_68K          0
            #define TARGET_CPU_X86          0
            #define TARGET_CPU_X86_64       1
            #define TARGET_CPU_ARM          0
            #define TARGET_CPU_ARM64        0
            #define TARGET_CPU_MIPS         0
            #define TARGET_CPU_MIPS64       0
            #define TARGET_CPU_S390X        0
            #define TARGET_CPU_SPARC        0
            #define TARGET_CPU_ALPHA        0
            #define TARGET_CPU_WASM32       0
        #endif

        #if __is_target_arch(wasm32) /* Is this it? */
            #define TARGET_CPU_PPC          0
            #define TARGET_CPU_PPC64        0
            #define TARGET_CPU_68K          0
            #define TARGET_CPU_X86          0
            #define TARGET_CPU_X86_64       0
            #define TARGET_CPU_ARM          0
            #define TARGET_CPU_ARM64        0
            #define TARGET_CPU_MIPS         0
            #define TARGET_CPU_MIPS64       0
            #define TARGET_CPU_S390X        0
            #define TARGET_CPU_SPARC        0
            #define TARGET_CPU_ALPHA        0
            #define TARGET_CPU_WASM32       1
        #endif
    #endif

#elif defined(__GNUC__) && ( defined(__APPLE_CPP__) || defined(__APPLE_CC__) || defined(__MACOS_CLASSIC__) )
    #ifndef DYNAMIC_TARGETS_SELECTED
        #define TARGET_OS_MAC 1
        #define TARGET_OS_OSX 1
    #endif

    #if defined(__ppc__) 
        #define TARGET_CPU_PPC          1
        #define TARGET_CPU_PPC64        0
        #define TARGET_CPU_68K          0
        #define TARGET_CPU_X86          0
        #define TARGET_CPU_X86_64       0
        #define TARGET_CPU_ARM          0
        #define TARGET_CPU_MIPS         0
        #define TARGET_CPU_MIPS64       0
        #define TARGET_CPU_S390X        0
        #define TARGET_CPU_SPARC        0   
        #define TARGET_CPU_ALPHA        0
        #define TARGET_CPU_WASM32       0
    #elif defined(__ppc64__) 
        #define TARGET_CPU_PPC          0
        #define TARGET_CPU_PPC64        1
        #define TARGET_CPU_68K          0
        #define TARGET_CPU_X86          0
        #define TARGET_CPU_X86_64       0
        #define TARGET_CPU_ARM          0
        #define TARGET_CPU_ARM64        0
        #define TARGET_CPU_MIPS         0
        #define TARGET_CPU_MIPS64       0
        #define TARGET_CPU_S390X        0
        #define TARGET_CPU_SPARC        0   
        #define TARGET_CPU_ALPHA        0
        #define TARGET_CPU_WASM32       0
    #elif defined(__i386__) 
        #define TARGET_CPU_PPC          0
        #define TARGET_CPU_PPC64        0
        #define TARGET_CPU_68K          0
        #define TARGET_CPU_X86          1
        #define TARGET_CPU_X86_64       0
        #define TARGET_CPU_ARM          0
        #define TARGET_CPU_ARM64        0
        #define TARGET_CPU_MIPS         0
        #define TARGET_CPU_MIPS64       0
        #define TARGET_CPU_S390X        0
        #define TARGET_CPU_SPARC        0
        #define TARGET_CPU_ALPHA        0
        #define TARGET_CPU_WASM32       0
    #elif defined(__x86_64__) 
        #define TARGET_CPU_PPC          0
        #define TARGET_CPU_PPC64        0
        #define TARGET_CPU_68K          0
        #define TARGET_CPU_X86          0
        #define TARGET_CPU_X86_64       1
        #define TARGET_CPU_ARM          0
        #define TARGET_CPU_ARM64        0
        #define TARGET_CPU_MIPS         0
        #define TARGET_CPU_MIPS64       0
        #define TARGET_CPU_S390X        0
        #define TARGET_CPU_SPARC        0
        #define TARGET_CPU_ALPHA        0
        #define TARGET_CPU_WASM32       0
    #elif defined(__arm__) 
        #define TARGET_CPU_PPC          0
        #define TARGET_CPU_PPC64        0
        #define TARGET_CPU_68K          0
        #define TARGET_CPU_X86          0
        #define TARGET_CPU_X86_64       0
        #define TARGET_CPU_ARM          1
        #define TARGET_CPU_MIPS         0
        #define TARGET_CPU_MIPS64       0
        #define TARGET_CPU_S390X        0
        #define TARGET_CPU_SPARC        0
        #define TARGET_CPU_ALPHA        0
        #define TARGET_CPU_WASM32       0
    #elif defined(__arm64__) 
        #define TARGET_CPU_PPC          0
        #define TARGET_CPU_PPC64        0
        #define TARGET_CPU_68K          0
        #define TARGET_CPU_X86          0
        #define TARGET_CPU_X86_64       0
        #define TARGET_CPU_ARM          0
        #define TARGET_CPU_ARM64        1
        #define TARGET_CPU_MIPS         0
        #define TARGET_CPU_MIPS64       0
        #define TARGET_CPU_S390X        0
        #define TARGET_CPU_SPARC        0
        #define TARGET_CPU_ALPHA        0
        #define TARGET_CPU_WASM32       0
    #elif defined(__mips64__) 
        #define TARGET_CPU_PPC          0
        #define TARGET_CPU_PPC64        0
        #define TARGET_CPU_68K          0
        #define TARGET_CPU_X86          0
        #define TARGET_CPU_X86_64       0
        #define TARGET_CPU_ARM          0
        #define TARGET_CPU_ARM64        0
        #define TARGET_CPU_MIPS         0
        #define TARGET_CPU_MIPS64       1
        #define TARGET_CPU_S390X        0
        #define TARGET_CPU_SPARC        0
        #define TARGET_CPU_ALPHA        0
        #define TARGET_CPU_WASM32       0
    #elif defined(__mips__) 
        #define TARGET_CPU_PPC          0
        #define TARGET_CPU_PPC64        0
        #define TARGET_CPU_68K          0
        #define TARGET_CPU_X86          0
        #define TARGET_CPU_X86_64       0
        #define TARGET_CPU_ARM          0
        #define TARGET_CPU_ARM64        0
        #define TARGET_CPU_MIPS         1
        #define TARGET_CPU_MIPS64       0
        #define TARGET_CPU_S390X        0
        #define TARGET_CPU_SPARC        0
        #define TARGET_CPU_ALPHA        0
        #define TARGET_CPU_WASM32       0
    #elif defined(__s390x__) 
        #define TARGET_CPU_PPC          0
        #define TARGET_CPU_PPC64        0
        #define TARGET_CPU_68K          0
        #define TARGET_CPU_X86          0
        #define TARGET_CPU_X86_64       0
        #define TARGET_CPU_ARM          0
        #define TARGET_CPU_ARM64        0
        #define TARGET_CPU_MIPS         0
        #define TARGET_CPU_MIPS64       0
        #define TARGET_CPU_S390X        1
        #define TARGET_CPU_SPARC        0
        #define TARGET_CPU_ALPHA        0
        #define TARGET_CPU_WASM32       0
    #elif defined(__wasm32__) 
        #define TARGET_CPU_PPC          0
        #define TARGET_CPU_PPC64        0
        #define TARGET_CPU_68K          0
        #define TARGET_CPU_X86          0
        #define TARGET_CPU_X86_64       0
        #define TARGET_CPU_ARM          0
        #define TARGET_CPU_ARM64        0
        #define TARGET_CPU_MIPS         0
        #define TARGET_CPU_MIPS64       0
        #define TARGET_CPU_S390X        0
        #define TARGET_CPU_SPARC        0
        #define TARGET_CPU_ALPHA        0
        #define TARGET_CPU_WASM32       0
    #else
        #error unsupported GNU C compiler
    #endif

#elif defined(__MWERKS__)
    #define TARGET_OS_MAC               1
    #define TARGET_OS_WIN32             0
    #define TARGET_OS_UNIX              0
    #define TARGET_OS_EMBEDDED          0
    #if defined(__POWERPC__)
        #define TARGET_CPU_PPC          1
        #define TARGET_CPU_PPC64        0
        #define TARGET_CPU_68K          0
        #define TARGET_CPU_X86          0
        #define TARGET_CPU_MIPS         0
        #define TARGET_CPU_SPARC        0
        #define TARGET_CPU_ALPHA        0
    #elif defined(__INTEL__)
        #define TARGET_CPU_PPC          0
        #define TARGET_CPU_PPC64        0
        #define TARGET_CPU_68K          0
        #define TARGET_CPU_X86          1
        #define TARGET_CPU_MIPS         0
        #define TARGET_CPU_SPARC        0
        #define TARGET_CPU_ALPHA        0
    #else
        #error unknown Metrowerks CPU type
    #endif

#endif

/*
 *    gcc based compiler used on Mac OS X
 */
#if defined(__GNUC__) && ( defined(__APPLE_CPP__) || defined(__APPLE_CC__) || defined(__MACOS_CLASSIC__) || defined(__clang__) )
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define TARGET_RT_LITTLE_ENDIAN 1
        #define TARGET_RT_BIG_ENDIAN    0
    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        #define TARGET_RT_LITTLE_ENDIAN 0
        #define TARGET_RT_BIG_ENDIAN    1
    #else
        #error "Bad __BYTE_ORDER__ configuration"
    #endif

    #if __LP64__
        #define TARGET_RT_64_BIT        1
    #else
        #define TARGET_RT_64_BIT        0
    #endif

    #if defined(__ppc__) && defined (__MACOS_CLASSIC__)
        #define TARGET_RT_MAC_CFM    1
        #define TARGET_RT_MAC_MACHO  0
    #else
        #define TARGET_RT_MAC_CFM    0
        #define TARGET_RT_MAC_MACHO  1
    #endif


/*
 *   CodeWarrior compiler from Metrowerks/Motorola
 */
#elif defined(__MWERKS__)
    #if defined(__POWERPC__)
        #define TARGET_RT_LITTLE_ENDIAN 0
        #define TARGET_RT_BIG_ENDIAN    1
    #elif defined(__INTEL__)
        #define TARGET_RT_LITTLE_ENDIAN 1
        #define TARGET_RT_BIG_ENDIAN    0
    #else
        #error unknown Metrowerks CPU type
    #endif
    #define TARGET_RT_64_BIT            0
    #ifdef __MACH__
        #define TARGET_RT_MAC_CFM       0
        #define TARGET_RT_MAC_MACHO     1
    #else
        #define TARGET_RT_MAC_CFM       1
        #define TARGET_RT_MAC_MACHO     0
    #endif

/*
 *   unknown compiler
 */
#else
    #if defined(TARGET_CPU_PPC) && TARGET_CPU_PPC
        #define TARGET_CPU_PPC64    0
        #define TARGET_CPU_68K      0
        #define TARGET_CPU_X86      0
        #define TARGET_CPU_X86_64   0
        #define TARGET_CPU_ARM      0
        #define TARGET_CPU_MIPS     0
        #define TARGET_CPU_SPARC    0
        #define TARGET_CPU_ALPHA    0
    #elif defined(TARGET_CPU_PPC64) && TARGET_CPU_PPC64
        #define TARGET_CPU_PPC      0
        #define TARGET_CPU_68K      0
        #define TARGET_CPU_X86      0
        #define TARGET_CPU_X86_64   0
        #define TARGET_CPU_ARM      0
        #define TARGET_CPU_MIPS     0
        #define TARGET_CPU_SPARC    0
        #define TARGET_CPU_ALPHA    0
    #elif defined(TARGET_CPU_X86) && TARGET_CPU_X86
        #define TARGET_CPU_PPC      0
        #define TARGET_CPU_PPC64    0
        #define TARGET_CPU_X86_64   0
        #define TARGET_CPU_68K      0
        #define TARGET_CPU_ARM      0
        #define TARGET_CPU_MIPS     0
        #define TARGET_CPU_SPARC    0
        #define TARGET_CPU_ALPHA    0
    #elif defined(TARGET_CPU_X86_64) && TARGET_CPU_X86_64
        #define TARGET_CPU_PPC      0
        #define TARGET_CPU_PPC64    0
        #define TARGET_CPU_X86      0
        #define TARGET_CPU_68K      0
        #define TARGET_CPU_ARM      0
        #define TARGET_CPU_MIPS     0
        #define TARGET_CPU_SPARC    0
        #define TARGET_CPU_ALPHA    0
    #elif defined(TARGET_CPU_ARM) && TARGET_CPU_ARM
        #define TARGET_CPU_PPC      0
        #define TARGET_CPU_PPC64    0
        #define TARGET_CPU_X86      0
        #define TARGET_CPU_X86_64   0
        #define TARGET_CPU_68K      0
        #define TARGET_CPU_MIPS     0
        #define TARGET_CPU_SPARC    0
        #define TARGET_CPU_ALPHA    0
    #else
        /*
            NOTE:   If your compiler errors out here then support for your compiler 
            has not yet been added to TargetConditionals.h.  
            
            TargetConditionals.h is designed to be plug-and-play.  It auto detects
            which compiler is being run and configures the TARGET_ conditionals
            appropriately.  
            
            The short term work around is to set the TARGET_CPU_ and TARGET_OS_
            on the command line to the compiler (e.g. -DTARGET_CPU_MIPS=1 -DTARGET_OS_UNIX=1)
            
            The long term solution is to add a new case to this file which
            auto detects your compiler and sets up the TARGET_ conditionals.
            Then submit the changes to Apple Computer.
        */
        #error TargetConditionals.h: unknown compiler (see comment above)
        #define TARGET_CPU_PPC    0
        #define TARGET_CPU_68K    0
        #define TARGET_CPU_X86    0
        #define TARGET_CPU_ARM    0
        #define TARGET_CPU_MIPS   0
        #define TARGET_CPU_SPARC  0
        #define TARGET_CPU_ALPHA  0
    #endif
    #define TARGET_OS_MAC                1
    #define TARGET_OS_WIN32              0
    #define TARGET_OS_UNIX               0
    #define TARGET_OS_EMBEDDED           0
    #if TARGET_CPU_PPC || TARGET_CPU_PPC64
        #define TARGET_RT_BIG_ENDIAN     1
        #define TARGET_RT_LITTLE_ENDIAN  0
    #else
        #define TARGET_RT_BIG_ENDIAN     0
        #define TARGET_RT_LITTLE_ENDIAN  1
    #endif
    #if TARGET_CPU_PPC64 || TARGET_CPU_X86_64
        #define TARGET_RT_64_BIT         1
    #else
        #define TARGET_RT_64_BIT         0
    #endif
    #ifdef __MACH__
        #define TARGET_RT_MAC_MACHO      1
        #define TARGET_RT_MAC_CFM        0
    #else
        #define TARGET_RT_MAC_MACHO      0
        #define TARGET_RT_MAC_CFM        1
    #endif
    
#endif

#endif  /* __TARGETCONDITIONALS__ */
