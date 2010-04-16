/******************************************************************************
 * @file	CmRandomNumberGenerator.h
 * @brief	Random Number Generator H file
 * @author  Takayuki HARUKI (University of Toyama, Japan)
 * @since	Nov. 2005
 *
 ******************************************************************************/

// このプログラムは松本眞氏、西村拓士氏らによって開発された
// Mersenne Twister法のCプログラムがオリジナルです。
// CmRandomNumberGenerator クラスは、Takayuki HARUKI により
// Singletonパターンに書き直されたコードです。
// 本コード内容は、CmRandomNumberGenerator を、ほぼそのままに流用しております。
//
// 多大な努力と時間を費やし研究された、開発者の皆様に敬意を表しまして、利用させていただきます。
// 良質の乱数をこのように手軽に利用できる事に感謝。
//
//                                         2008/09/09 Masatoshi Tsuge
//
// 【Mersenne Twister Home Page】
// http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/mt.html
// 【CmRandomNumberGeneratorのダウンロード】
// http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/VERSIONS/C-LANG/Singleton.zip


#ifndef _CM_RANDOM_NUMBER_GENERATOR_H_INCLUDED_
#define _CM_RANDOM_NUMBER_GENERATOR_H_INCLUDED_

//#include <stdio.h>

//!< Period Parameter for Mersenne Twister
#define	N (624)
#define	M (397)

/**
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
    void changeSeed(unsigned long a_ulSeed);
    //@}

    //private:

    void init_genrand(unsigned long s); // initialize mt[N] with a seed
    unsigned long genrand_int32(void); // [0, 0xffffffff]
    long genrand_int31(void); // [0, 0x7fffffff]
    double genrand_real1(void); // [0, 1]
    double genrand_real2(void); // [0, 1)
    double genrand_real3(void); // (0, 1)

private:

    static CmRandomNumberGenerator* s_pInstance;

    static unsigned long mt[N]; //!< array for the state vector
    static int mti; //!< mti==N+1 means mt[N] is not initialized
};

#endif // _CM_RANDOM_NUMBER_GENERATOR_H_INCLUDED_
