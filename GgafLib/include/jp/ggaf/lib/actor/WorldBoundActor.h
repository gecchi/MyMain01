#ifndef WORLDBOUNDACTOR_H_
#define WORLDBOUNDACTOR_H_
namespace GgafLib {

/**
 * ���E���E.
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class WorldBoundActor : public GgafDxCore::GgafDxWorldBoundActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* _pScaler;

    frame _offset_frames;

    WorldBoundActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

   virtual void processSettlementBehavior() override;

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override {
    }

    int isOutOfView() override {
        //��ʊO���薳��
        return 0;
    }

    bool isOutOfUniverse() override {;
        //�Q�[�����W�͈͊O���薳��
        return false;
    }
    virtual ~WorldBoundActor();
};

}
#endif /*WORLDBOUNDACTOR_H_*/
