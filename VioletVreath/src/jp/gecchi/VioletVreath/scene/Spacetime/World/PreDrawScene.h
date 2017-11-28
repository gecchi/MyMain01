#ifndef PREDRAWSCENE_H_
#define PREDRAWSCENE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * ���O�\���V�[�� .
 * �Q�[���̑O�Ɋe���f���̃L�������P�L�������o�͂��A
 * ���f���N���X���v�����[�h���Ă����B
 * @version 1.00
 * @since 2010/04/20
 * @author Masatoshi Tsuge
 */
class PreDrawScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_DISP ,
        PROG_CALM_DOWN ,
        PROG_WAIT ,
        PROG_BANPEI,
    };

    int order_id_begin_;
    int order_id_end_;
    int _id_;

public:
    PreDrawScene(const char* prm_name);
    void onReset() override;
    void ready();
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~PreDrawScene();
};

}
#endif /*PREDRAWSCENE_H_*/
