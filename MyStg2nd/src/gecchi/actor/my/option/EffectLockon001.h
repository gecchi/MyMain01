#ifndef EFFECTLOCKON001_H_
#define EFFECTLOCKON001_H_
namespace MyStg2nd {

enum {
    LOCKON001_PROG_FIRST_LOCK = 1,
    LOCKON001_PROG_LOCK          ,
    LOCKON001_PROG_RELEASE       ,
};

/**
 * ���b�N�I��
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockon001 : public GgafLib::DefaultSpriteSetActor {

public:
    GgafDxCore::GgafDxGeometricActor* _pTarget;

    EffectLockon001(const char* prm_name, const char* prm_model_id);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void onActive() override;

    virtual void onInactive() override;

    virtual void processJudgement() override;

    virtual void releaseLockon() = 0;

    virtual void lockon(GgafDxGeometricActor* prm_pTarget) = 0;

    virtual ~EffectLockon001();


//DEBUG���[�h�A�v���I�����̃c���[�\�����A
//_pTarget���s���ɂȂ�ꍇ�����邽�߁A�K�v�ȂƂ��ɃR�����g���O���Ďd�l���邱�ƂƂ���B
//
//    /**
//     * �^�[�Q�b�g���\������_���v(�f�o�b�O�p) .
//     */
//    void dump();
//
//    /**
//     * �^�[�Q�b�g���\������_���v(�f�o�b�O�p) .
//     */
//    void dump(std::string prm_parent);

};

}
#endif /*EFFECTLOCKON001_H_*/

