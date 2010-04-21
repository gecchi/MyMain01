#ifndef SHOT003_H_
#define SHOT003_H_
namespace MyStg2nd {

/**
 * �ėp�e003(��) .
 * �j��s�\�œ��������ړ�<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot003 : public GgafDx9LibStg::DefaultMeshSetActor {
public:
    Shot003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~Shot003();
};

}
#endif /*SHOT003_H_*/
