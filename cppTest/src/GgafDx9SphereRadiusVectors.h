#ifndef GGAFDX9SPHERERADIUSVECTORS_H_
#define GGAFDX9SPHERERADIUSVECTORS_H_

//�߂������ɉ�]
#define TURN_CLOSE_TO 0
//���v���ɉ�]
#define TURN_CLOCKWISE (-1)
//�����v���ɉ�]
#define TURN_COUNTERCLOCKWISE 1
//��]�ǂ���ł�
#define TURN_BOTH 0



//��X
#define AXIS_X 0
//��Y
#define AXIS_Y 1
//��Z
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

