#ifndef GGAFDX9SPHERERADIUSVECTORS_H_
#define GGAFDX9SPHERERADIUSVECTORS_H_
namespace GgafDx9Core {


/**
 * �����x�N�g���\����.
 * �e�v�f�̒P�ʂ́A10000�{�̐����ŕێ�����܂��B<BR>
 * ���၄<BR>
 * �P�ʃx�N�g��(0.6583, 0.1132, 0.744) ��<BR>
 * SR_VECTOR�ł́A(6583, 1132, 7440) �ł�<BR>
 */
struct SR_VECTOR {
	unsigned __int16 x;
	unsigned __int16 z;
	unsigned __int16 y;
};

/**
 * �\�[�g�\�����x�N�g���N���X.
 * SR_VECTOR�ɑ召�̒l�����A��r�\�ɂ��������o�����N���X�B<BR>
 * �召�̒l�̋����́Ay�v�f �� z�v�f �� x�v�f �̏��ł��B<BR>
 */
class COMPARE_ABLE_SR_VECTOR : public GgafCore::GgafObject {
public:
	unsigned __int64 num_yzx;
	SR_VECTOR vec;
	COMPARE_ABLE_SR_VECTOR() : GgafObject() {
	}
	/**
	 * �P�ʃx�N�g����ݒ肷��B<BR>
	 * @param prm_x �����x�N�g��X�v�f
	 * @param prm_y �����x�N�g��Y�v�f
	 * @param prm_z �����x�N�g��Z�v�f
	 */
	void set(unsigned __int16 prm_x, unsigned __int16 prm_y, unsigned __int16 prm_z) {
		vec.x = prm_x;
		vec.y = prm_y;
		vec.z = prm_z;
		num_yzx = (prm_y * 65536LL * 65536LL ) +
                  (prm_z * 65536LL ) +
                  (prm_x );
	}
};


/**
 * �P�ʋ��ƁA�P�ʃx�N�g���̊֌W��ێ�����N���X�ł��B .
 * �A���ێ�����Ă���͈͂́Ax��0 y��0 z��0 �͈̔͂����ł��B�i1/8�����̂݁j<BR>
 * �y�⑫�z<BR>
 * �ێ����Ă���x�N�g���̊e�v(X,Y,Z)�̒P��(unsigned __int16)�́A����1 �� 10000 �ɑ������鐮���ɂȂ��Ă��܂��B<BR>
 * �p�x�̒P�ʁis_ang�j�́A1�x �� 10 �ɑ������܂��B���p�� 900 �ɂȂ�܂��Bangle�l(1�x��1000)�ƍ��݂��Ȃ��悤�ɒ���<BR>
 */
class GgafDx9SphereRadiusVectors : public GgafCore::GgafObject {
public:
	/** 1/8�����̃\�[�g�\�����x�N�g���z��(�v�f����900*900) */
	static COMPARE_ABLE_SR_VECTOR _sr[];

	GgafDx9SphereRadiusVectors();

	/**
	 * ������X,Y,Z�����x�N�g������A��������Z����]��Y����]�̒l�����������ŋ��߂�B
	 * �A���AX,Y,Z �͑S�Đ��łȂ��Ă͂Ȃ�Ȃ�
	 * @param prm_x �����x�N�g��X�v�f
	 * @param prm_y �����x�N�g��Y�v�f
	 * @param prm_z �����x�N�g��Z�v�f
	 * @param out_angRotZ Z����]�l�i�P��s_ang�j
	 * @param out_angRotY Y����]�l�i�P��s_ang�j
	 */
	void getRotAngleClosely(unsigned __int16 prm_x, unsigned __int16 prm_y, unsigned __int16 prm_z, s_ang& out_angRotZ, s_ang& out_angRotY);

	/**
	 * ������Z����]��Y����]�̒l����A��������P�ʕ����x�N�g�������������ŋ��߂�B
	 * �A���A���ʂ̕����x�N�g���̊e�v�f(X,Y,Z)�����̒l�ɂȂ�悤�Ȉ��������󂯕t���Ȃ��B
	 * @param prm_angRotY Z����]�l�i�P��s_ang�j
	 * @param prm_angRotZ Y����]�l�i�P��s_ang�j
	 * @param out_x �����x�N�g��X�v�f
	 * @param out_y �����x�N�g��Y�v�f
	 * @param out_z �����x�N�g��Z�v�f
	 */
	void getVectorClosely(s_ang prm_angRotY, s_ang prm_angRotZ, unsigned __int16& out_x, unsigned __int16& out_y, unsigned __int16& out_z);


	virtual ~GgafDx9SphereRadiusVectors();
};


}
#endif /*GGAFDX9SPHERERADIUSVECTORS_H_*/

