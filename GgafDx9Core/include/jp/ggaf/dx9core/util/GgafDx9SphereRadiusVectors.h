#ifndef GGAFDX9SPHERERADIUSVECTORS_H_
#define GGAFDX9SPHERERADIUSVECTORS_H_


struct SR_VECTOR {
	unsigned __int16 x;
	unsigned __int16 z;
	unsigned __int16 y;
};

struct COMPARE_ABLE_SR_VECTOR {
	unsigned __int64 num_yzx;
	SR_VECTOR vec;
};
//class GgafDx9SphereRadiusVectors;



class GgafDx9SphereRadiusVectors {
public:
	static COMPARE_ABLE_SR_VECTOR _sr[];

	GgafDx9SphereRadiusVectors();

	/**
	 * X,Y,Z�����x�N�g������A����������Z����]��Y����]�̒l�����߂�B
	 * �A���AX,Y,Z �͑S�Đ��łȂ��Ă͂Ȃ�Ȃ�
	 * @param prm_x �����x�N�g��X�v�f
	 * @param prm_y �����x�N�g��Y�v�f
	 * @param prm_z �����x�N�g��Z�v�f
	 * @param out_angRotZ Z����]�l�i�P�ʒ��Ӂj
	 * @param out_angRotY Y����]�l�i�P�ʒ��Ӂj
	 */
	void getRotAngleClosely(unsigned __int16 prm_x, unsigned __int16 prm_y, unsigned __int16 prm_z, int& out_angRotZ, int& out_angRotY);

	/**
	 *
	 * @param prm_angRotY
	 * @param prm_angRotZ
	 * @param out_x
	 * @param out_y
	 * @param out_z
	 */
	void getVectorClosely(s_ang prm_angRotY, s_ang prm_angRotZ, unsigned __int16& out_x, unsigned __int16& out_y, unsigned __int16& out_z);


	virtual ~GgafDx9SphereRadiusVectors();
};


#endif /*GGAFDX9SPHERERADIUSVECTORS_H_*/

