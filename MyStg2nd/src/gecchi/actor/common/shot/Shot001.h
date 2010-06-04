#ifndef SHOT001_H_
#define SHOT001_H_
namespace MyStg2nd {

/**
 * �ėp�e001(��) .
 * �j��\�œ��������ړ�<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot001 : public GgafDx9LibStg::DefaultMeshSetActor {
public:

    /** �ړ��X�v���C���v���O���� */
    GgafDx9Core::GgafDx9SplineProgram* _pSplineProgram;
    /** �X�v���C����`�����ւ̐ڑ� */
    Spline3DConnection* _pSplineCon;
    Shot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~Shot001();
};

}
#endif /*SHOT001_H_*/

