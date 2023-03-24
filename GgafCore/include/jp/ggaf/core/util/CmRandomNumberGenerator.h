/******************************************************************************
 * @file	CmRandomNumberGenerator.h
 * @brief	Random Number Generator H file
 * @author  Takayuki HARUKI (University of Toyama, Japan)
 * @since	Nov. 2005
 *
 ******************************************************************************/


#ifndef _CM_RANDOM_NUMBER_GENERATOR_H_INCLUDED_
#define _CM_RANDOM_NUMBER_GENERATOR_H_INCLUDED_
#include "jp/ggaf/GgafCommonHeader.h"

namespace GgafCore {

//!< Period Parameter for Mersenne Twister
#define	N___ (624)
#define	M___ (397)


/**
 * 乱数生成クラス .
 * このプログラムは松本眞氏、西村拓士氏らによって開発された
 * Mersenne Twister法のCプログラムがオリジナルです。<BR>
 * CmRandomNumberGenerator クラスは、Takayuki HARUKI により
 * Cプログラムを C++のSingleton パターンに書き直されたコードです。<BR>
 * 本コード内容は、CmRandomNumberGenerator を流用しております。<BR>
 * 多大な努力と時間を費やし研究された、松本・西村両氏に敬意を表し、
 * 利用させていただきます。<BR>
 *                                         2008/09/09 Masatoshi Tsuge<BR>
 * 【Mersenne Twister Home Page】<BR>
 * http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/mt.html<BR>
 * 【Original C code】<BR>
 * http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html as mt19937ar.tgz<BR>
 * 【Download CmRandomNumberGenerator】<BR>
 * http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/VERSIONS/C-LANG/Singleton.zip<BR>
 *
 * 以下はオリジナルCプログラムの使用ライセンスです。<BR>
 * <pre>
 * A C-program for MT19937, with initialization improved 2002/1/26.
 * Coded by Takuji Nishimura and Makoto Matsumoto.
 *
 * Before using, initialize the state by using init_genrand(seed)
 * or init_by_array(init_key, key_length).
 *
 * Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   3. The names of its contributors may not be used to endorse or promote
 *      products derived from this software without specific prior written
 *      permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Any feedback is very welcome.
 * http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
 * email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
 * </pre>
 * @class	CmRandomNumberGenerator
 * @brief	Class (of mathematical module) for generating random number
 *			by Mersenne Twister
 * @author  Takayuki HARUKI (University of Toyama, Japan)
 * @date	Nov. 2005
 * @par	how to use
 *			-# get singleton object by using getInstance
 *			-# change seed by changeSeed if you want
 *			-# get random number by calling getFloat or getDouble functions
 *			-# call release finally only at once
 *
 */
class CmRandomNumberGenerator {
private:

    /**
     * @name Constructor and Destructor (private for SINGLETON)
     */
    //@{
    CmRandomNumberGenerator();
    virtual ~CmRandomNumberGenerator();
    //@}

public:

    /**
     * @name Singleton
     */
    //@{
    static CmRandomNumberGenerator* getInstance();
    void release();
    //@}

    /**
     * @name Random number
     */
    //@{
    float getFloat();
    double getDouble();
    //@}

    /**
     * @name Seed
     */
    //@{
    void changeSeed(uint32_t a_ulSeed);
    //@}

    //private:

    void init_genrand(uint32_t s); // initialize mt[N___] with a seed
    uint32_t genrand_int32(void); // [0, 0xffffffff]
    int32_t genrand_int31(void); // [0, 0x7fffffff]
    double genrand_real1(void); // [0, 1]
    double genrand_real2(void); // [0, 1)
    double genrand_real3(void); // (0, 1)

private:

    static CmRandomNumberGenerator* s_pInstance;

    static uint32_t mt[N___]; //!< array for the state vector
    static int mti; //!< mti==N___+1 means mt[N___] is not initialized
};

}
#endif // _CM_RANDOM_NUMBER_GENERATOR_H_INCLUDED_
