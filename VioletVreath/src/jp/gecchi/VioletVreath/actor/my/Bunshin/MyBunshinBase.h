#ifndef MYBUNSHINCONTROLLER_H_
#define MYBUNSHINCONTROLLER_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * ���g�y�� .
 * @version 1.00
 * @since 2015/04/17
 * @author Masatoshi Tsuge
 */
class MyBunshinBase : public GgafLib::DefaultMeshActor {
//class MyBunshinBase : public GgafDxCore::GgafDxGeometricActor {

public:
    /** �ő啪�g�� */
    static int max_bunshin_num_;
    /** [r]���g�ƕ��g�̊Ԋu */
    static frame bunshin_d_;

    /** [r]���g�{�� */
    MyBunshin* pBunshin_;
    /** ���@�g���[�X�̍��W����̃I�t�Z�b�g(�t���[�łȂ��ꍇ��0) */
    GgafDxCore::GgafDxGeoElem trace_offset_;
    /** ���g�ԍ�(1�`) */
    int no_;

    /** [r]���g�𒆐S�Ƃ����A���g�̌��]�̔��a */
    coord bunshin_radius_position_;
    /** [r]���g�𒆐S�Ƃ����A���g�̌��]�O����̈ʒu */
    angle bunshin_ang_position_;
    /** [r]���g�̍L����p�x */
    angle bunshin_expanse_;
    /** [r]���g�𒆐S�Ƃ����A���g�̌��]�̊p���x */
    angvelo bunshin_angvelo_mv_;

public:
    MyBunshinBase(const char* prm_name, int prm_no);

    void config(
            coord prm_radius_position,
            angle prm_ang_position,
            angle prm_expanse,
            angvelo prm_angvelo_mv);

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

//DefaultMeshActor���ŕ\���������ꍇ�̓R�����g�ɂ��邱��
//GgafDxGeometricActor�̏ꍇ�̓R�����g���O������
    //virtual void processDraw() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {}

    virtual ~MyBunshinBase();


};

}
#endif /*MYBUNSHINCONTROLLER_H_*/

