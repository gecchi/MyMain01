#ifndef FORMATIONIRIS002_H_
#define FORMATIONIRIS002_H_
namespace VioletVreath {

/**
 * �G�@�C���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationIris002 : public GgafLib::TreeFormation {

    DepositoryConnection* pDepoCon_;
    SplineLineConnection* pSplLineCon_;

public:
    /** �ґ���(RANK�ϓ�) */
    int num_Iris_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;
    /** �ړ����x(RANK�ϓ�) */
    velo velo_mv_;

public:
    FormationIris002(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationIris002();
};

}
#endif /*FORMATIONIRIS002_H_*/
