#ifndef IFORMATIONABLE_H_
#define IFORMATIONABLE_H_

namespace GgafLib {



/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * processJudgement()�������ς݂̂��߁A
 * �p���N���X��processJudgement()�g�p�����ӂ��邱�ƁB
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class IFormationAble {
public:

    GgafLib::FormationActor* _pFormation;

    IFormationAble();

    void informDestroyedFollower();
//    virtual void onDestroyedFormation(GgafDxCore::GgafDxDrawableActor* prm_pActor_LastDestroyed) = 0;
    virtual ~IFormationAble();
};

}
#endif /*IFORMATIONABLE_H_*/
