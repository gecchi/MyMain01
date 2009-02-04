#ifndef GGAFDX9SQUAREACTORD_H_
#define GGAFDX9SQUAREACTORD_H_
namespace GgafDx9Core {

/**
 * �X�N�G�A�A�N�^�[.
 * GgafDx9UntransformedActor ���p�����A�X�N�G�A�i�l�p�`�j��\�����邽�߂̃A�N�^�[�ł��B<BR>
 * �f�o�b�O�p�̓����蔻��̈�\���Ȃǂŗ��p����܂��B<BR>
 */
class GgafDx9SquareActor : public GgafDx9UntransformedActor {

private:


public:
	GgafDx9ModelLead* _pModelLead;
	GgafDx9SquareModel* _pSquareModel;

	GgafDx9SquareActor(char* prm_name, char* prm_squaremodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processDrawMain();

	virtual ~GgafDx9SquareActor();		//�f�X�g���N�^

};


}
#endif /*GGAFDX9SQUAREACTORD_H_*/
