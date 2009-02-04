#ifndef GGAFDX9CUBEACTORD_H_
#define GGAFDX9CUBEACTORD_H_
namespace GgafDx9Core {

/**
 * �L���[�u�A�N�^�[.
 * GgafDx9UntransformedActor ���p�����A�L���[�u�i�����́j��\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A�����P�̗�����(���S��(0,0,0))�̃��b�V����ǂݍ��܂��Ă��������B
 */
class GgafDx9CubeActor : public GgafDx9MeshActor {
private:

public:
	GgafDx9CubeActor(char* prm_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

 	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processDrawMain();

	void drawBox(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2);

	virtual ~GgafDx9CubeActor();		//�f�X�g���N�^
};


}
#endif /*GGAFDX9CUBEACTORD_H_*/
