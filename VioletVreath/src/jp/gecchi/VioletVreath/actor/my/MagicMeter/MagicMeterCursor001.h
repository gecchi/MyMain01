#ifndef MAGICMETERCURSOR001_H_
#define MAGICMETERCURSOR001_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"



namespace VioletVreath {

/**
 * ���[�^�[��J�[�\�� .
 * @version 1.00
 * @since 2011/12/12
 * @author Masatoshi Tsuge
 */
class MagicMeterCursor001 : public GgafLib::DefaultBoardActor {

public:
    /** ���߂̏���A */
    GgafDxCore::GgafDxKurokoAsstA* pKurokoAsstA_;
    /** �ړ��ڕWX���W */
    coord tx_;
    /** �ړ��ڕWY���W */
    coord ty_;
    /** �ޔ�p */
    float tmp_alpha_;
    MagicMeter* pMagicMeter_;

public:
   MagicMeterCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;
    void moveTo(int prm_magic_mater_index);

    virtual ~MagicMeterCursor001();
};

}
#endif /*MAGICMETERCURSOR001_H_*/

