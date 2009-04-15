#ifndef MYLASERCHIP_H_
#define MYLASERCHIP_H_
namespace MyStg2nd {

class MyLaserChip : public GgafDx9Core::GgafDx9MeshActor {

private:
    D3DXHANDLE _hX, _hY, _hZ, _hMatWorld_front;

public:
    /** ��O���̃��[�U�[�`�b�v */
    MyLaserChip* _pChip_front;
    /** �����̃��[�U�[�`�b�v */
	MyLaserChip* _pChip_behind;
    /** ���g��WORLD�ϊ��s�� */
    D3DXMATRIX _matWorld;
    /** ��O����WORLD�ϊ��s�� */
    D3DXMATRIX _matWorld_front;
    /** ���g���Ǘ����Ă郍�[�e�[�V�����A�N�^�[ */
    MyLaserChipRotationActor* _pRotation;
    /** ���ˌ��A�N�^�[ */
    GgafDx9UntransformedActor* _pActor_Radical;


    GgafDx9LibStg::StgChecker* _pChecker;


    MyLaserChip(const char* prm_name, MyLaserChipRotationActor* prm_pRotation);

    /**
     * ��OverRide �ł���
     */
    void initialize();

    /**
     * ��OverRide �ł���
     */
    void processBehavior();

    /**
     * ��OverRide �ł���
     */
    void processJudgement();

    void processDrawPrior() {
        GgafDx9Core::GgafDx9MeshActor::processDrawPrior();
    }

    void processDrawTerminate();

    /**
     * ��OverRide �ł���
     */
    void processDrawMain();

    void processHappen(int prm_no) {
    }

    void processFinal() {
    }

    /**
     * ��OverRide �ł���
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    void setRadicalActor(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor) {
        _pActor_Radical = prm_pActor;
    }

    bool isOffScreen();

    /**
     * �o�����R�[���o�b�N����
     */
    void onActive();

    /**
     * �������R�[���o�b�N����
     */
    void onInactive();

    virtual ~MyLaserChip();

};

}
#endif /*MYLASERCHIP_H_*/

