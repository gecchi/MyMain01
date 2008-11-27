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
	 * X,Y,Z方向ベクトルから、だいたいのZ軸回転とY軸回転の値を求める。
	 * 但し、X,Y,Z は全て正でなくてはならない
	 * @param prm_x 方向ベクトルX要素
	 * @param prm_y 方向ベクトルY要素
	 * @param prm_z 方向ベクトルZ要素
	 * @param out_angRotZ Z軸回転値（単位注意）
	 * @param out_angRotY Y軸回転値（単位注意）
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

