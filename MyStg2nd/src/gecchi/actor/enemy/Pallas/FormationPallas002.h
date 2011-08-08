#ifndef FORMATIONPALLAS002_H_
#define FORMATIONPALLAS002_H_
namespace MyStg2nd {

/**
 * �G�@�C���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationPallas002 : public GgafDx9Core::GgafDx9FormationActor {
    /** �C���X�̔��˒e�̎؂���ꌳStore�����ւ̐ڑ� */
    StoreConnection* _pStoreCon;
    /** �X�v���C����`�����ւ̐ڑ� */
    Spline3DConnection* _pSplCon;
public:
    /** �ґ���(RANK�ϓ�) */
    int _num_Pallas;
    /** �C���X�̔z��(RANK�ϓ�) */
    EnemyPallas** _papPallas;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame _interval_frames;
    /** �ړ����x(RANK�ϓ�) */
    velo _mv_velo;

    FormationPallas002(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override {
    }
    virtual void onActive() override;
    virtual ~FormationPallas002();
};

}
#endif /*FORMATIONPALLAS002_H_*/
