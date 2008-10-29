#ifndef GGAFDX9SPHERERADIUSVECTORS_H_
#define GGAFDX9SPHERERADIUSVECTORS_H_

//‹ß‚¢•ûŒü‚É‰ñ“]
#define TURN_CLOSE_TO 0
//ŽžŒv‰ñ‚è‚É‰ñ“]
#define TURN_CLOCKWISE (-1)
//”½ŽžŒv‰ñ‚è‚É‰ñ“]
#define TURN_COUNTERCLOCKWISE 1
//‰ñ“]‚Ç‚¿‚ç‚Å‚à
#define TURN_BOTH 0



//Ž²X
#define AXIS_X 0
//Ž²Y
#define AXIS_Y 1
//Ž²Z
#define AXIS_Z 2

struct SR_VECTOR {
	unsigned short x;
	unsigned short z;
	unsigned short y;
};

union COMPARE_ABLE_SR_VECTOR {
	long long num_yzx;
	SR_VECTOR vec;
};
//class GgafDx9SphereRadiusVectors;



class GgafDx9SphereRadiusVectors {
public:
	static COMPARE_ABLE_SR_VECTOR _sr[];


	GgafDx9SphereRadiusVectors();

	void getRotAngleClosely(unsigned short x, unsigned short y, unsigned short z, angle& out_angRotZ, angle& out_angRotY);


	virtual ~GgafDx9SphereRadiusVectors();
};


#endif /*GGAFDX9SPHERERADIUSVECTORS_H_*/

