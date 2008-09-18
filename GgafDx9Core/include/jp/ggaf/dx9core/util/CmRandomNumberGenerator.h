/******************************************************************************
 /**
 * @file	CmRandomNumberGenerator.h
 * @brief	Random Number Generator H file
 * @author  Takayuki HARUKI (University of Toyama, Japan)
 * @since	Nov. 2005
 *
 ******************************************************************************/

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
 * @data	Nov. 2005
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
