//#include "CmRandomNumberGenerator.h"
#include "stdafx.h"
using namespace GgafCore;

//!< Period Parameter for Mersenne Twister
#define	MATRIX_A	(0x9908b0dfUL)	//!< constant vector a
#define	UPPER_MASK	(0x80000000UL)	//!< most significant w-r bits
#define	LOWER_MASK	(0x7fffffffUL)	//!< least significant r bits


/**
 * @file	CmRandomNumberGenerator.cpp
 * @brief	Random Number Generator CPP file
 * @author  Takayuki HARUKI (University of Toyama, Japan)
 * @since	Nov. 2005
 *
 */
CmRandomNumberGenerator* CmRandomNumberGenerator::s_pInstance = nullptr;

UINT32 CmRandomNumberGenerator::mt[__N__];
int CmRandomNumberGenerator::mti = __N__ + 1;

/******************************************************************************
 *
 * 			Constructor
 *
 * @author  Takayuki HARUKI (University of Toyama, Japan)
 * @date	Nov. 2005
 *
 ******************************************************************************/
CmRandomNumberGenerator::CmRandomNumberGenerator() {
}

/******************************************************************************
 *
 * 			Destructor
 *
 * @author  Takayuki HARUKI (University of Toyama, Japan)
 * @date	Nov. 2005
 *
 ******************************************************************************/
CmRandomNumberGenerator::~CmRandomNumberGenerator() {
}

/******************************************************************************
 *
 * 			Get Instance
 *
 * @return	Instance Pointer
 * @author  Takayuki HARUKI (University of Toyama, Japan)
 * @date	Nov. 2005
 *
 ******************************************************************************/
CmRandomNumberGenerator* CmRandomNumberGenerator::getInstance() {
    if (nullptr == s_pInstance) {
        s_pInstance = NEW CmRandomNumberGenerator();
    }

    return s_pInstance;
}

/******************************************************************************
 *
 * 			Release Instance
 *
 * @author  Takayuki HARUKI (University of Toyama, Japan)
 * @date	Nov. 2005
 *
 ******************************************************************************/
void CmRandomNumberGenerator::release() {
    DELETE_POSSIBLE_NULL(s_pInstance);
}

/******************************************************************************
 *
 * 			Get Float Type Random Number [0, 1]
 *
 * @return	Float Type Random Number
 * @author  Takayuki HARUKI (University of Toyama, Japan)
 * @date	Nov. 2005
 *
 ******************************************************************************/
float CmRandomNumberGenerator::getFloat() {
    return (float)genrand_real1();
}

/******************************************************************************
 *
 * 			Get Double Type Random Number [0, 1]
 *
 * @return	Double Type Random Number
 * @author  Takayuki HARUKI (University of Toyama, Japan)
 * @date	Nov. 2005
 *
 ******************************************************************************/
double CmRandomNumberGenerator::getDouble() {
    return genrand_real1();
}

/******************************************************************************
 *
 * 			Change Seed for Generating Random Numbers
 *
 * @param	a_ulSeed	(I)	Seed of Random Generator
 * @author  Takayuki HARUKI (University of Toyama, Japan)
 * @date	Nov. 2005
 *
 ******************************************************************************/
void CmRandomNumberGenerator::changeSeed(UINT32 a_ulSeed) {
    init_genrand(a_ulSeed);
}

/******************************************************************************
 * 			Mersenne Twister
 ******************************************************************************/

/* initializes mt[__N__] with a seed */
void CmRandomNumberGenerator::init_genrand(UINT32 s) {
    mt[0] = s & 0xffffffffUL;

    for (mti = 1; mti < __N__; mti++) {
        mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* generates a random number on [0,0xffffffff]-interval */
UINT32 CmRandomNumberGenerator::genrand_int32(void) {
    UINT32 y;
    static UINT32 mag01[2] = {0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= __N__) {
        /* generate __N__ words at one time */
        int kk;

        if (mti == __N__ + 1) /* if init_genrand() has not been called, */
        init_genrand(5489UL); /* a default initial seed is used */

        for (kk = 0; kk < __N__ - __M__; kk++) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + __M__] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }

        for (; kk < __N__ - 1; kk++) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (__M__ - __N__)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }

        y = (mt[__N__ - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[__N__ - 1] = mt[__M__ - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
INT32 CmRandomNumberGenerator::genrand_int31(void) {
    return (INT32)(genrand_int32() >> 1);
}

/* generates a random number on [0,1]-real-interval */
double CmRandomNumberGenerator::genrand_real1(void) {
    return genrand_int32() * (1.0 / 4294967295.0);
    /* divided by 2^32-1 */
}

/* generates a random number on [0,1)-real-interval */
double CmRandomNumberGenerator::genrand_real2(void) {
    return genrand_int32() * (1.0 / 4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double CmRandomNumberGenerator::genrand_real3(void) {
    return (((double)genrand_int32()) + 0.5) * (1.0 / 4294967296.0);
    /* divided by 2^32 */
}
