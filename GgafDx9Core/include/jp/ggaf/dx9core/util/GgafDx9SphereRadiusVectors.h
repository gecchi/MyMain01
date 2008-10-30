#ifndef GGAFDX9SPHERERADIUSVECTORS_H_
#define GGAFDX9SPHERERADIUSVECTORS_H_


struct SR_VECTOR {
	unsigned __int16 x;
	unsigned __int16 z;
	unsigned __int16 y;
};

union COMPARE_ABLE_SR_VECTOR {
	unsigned __int64 num_yzx;
	SR_VECTOR vec;
};
//class GgafDx9SphereRadiusVectors;



class GgafDx9SphereRadiusVectors {
public:
	static COMPARE_ABLE_SR_VECTOR _sr[];

	GgafDx9SphereRadiusVectors();

	void getRotAngleClosely(unsigned __int16 prm_x, unsigned __int16 prm_y, unsigned __int16 prm_z, int& out_angRotZ, int& out_angRotY);

	void getVectorClosely(int out_angRotY, int prm_angRotZ, unsigned __int16& out_x, unsigned __int16& out_y, unsigned __int16& out_z);


	virtual ~GgafDx9SphereRadiusVectors();
};


#endif /*GGAFDX9SPHERERADIUSVECTORS_H_*/

