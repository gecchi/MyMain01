#ifndef VVVCURSOR_H_
#define VVVCURSOR_H_
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VVViewer {

/**
 * �e�X�g�L���� .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCursor : public GgafLib::DefaultSpriteActor {

public:
    enum {
        CUR_SINK =1,
        CUR_ON_MOVE,
        CUR_STAY,
    };
    coord tX_, tY_, tZ_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    VvvCursor(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;
    void moveTo(GgafDxCore::GgafDxGeometricActor* pT) {
        moveTo(pT->_x,pT->_y,pT->_z);
    }
    void moveTo(coord X, coord Y, coord Z);
    void sinkMe();


    virtual ~VvvCursor();
};

}
#endif /*SMPACTOR_H_*/

