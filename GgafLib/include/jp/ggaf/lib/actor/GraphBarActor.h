#ifndef GRAPHBARACTOR_H_
#define GRAPHBARACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/util/PxQuantity.h"

namespace GgafLib {

/**
 * ���̐��ʃo�[ .
 * �iVV�̃N���X���珸�i�j
 * @version 1.00
 * @since 2012/09/11
 * @author Masatoshi Tsuge
 */
class GraphBarActor : public DefaultBoardActor {

public:
    /** �����s�N�Z�� */
    const float _chip_width;
    const float _rate_org_chip_width;

    /** ���e�� */
    PxQuantity* _pPxQuantity;
    bool _is_new_PxQuantity;
public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQuantity config�ς݂� PxQuantity�I�u�W�F�N�g�̎Q��
     */
    GraphBarActor(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQuantity);

    GraphBarActor(const char* prm_name, const char* prm_model);

    void linkPxQuantity(PxQuantity* prm_pPxQuantity);


    inline void graduatePxQty(pixcoord prm_max_val_px, int prm_max_val) {
        _pPxQuantity->graduate(prm_max_val_px, prm_max_val);
    }

    /**
     * ���[�^�[�l��ݒ� .
     * @param prm_val ���[�^�[�l
     */
    inline void setQty(int prm_val) {
        _pPxQuantity->set(prm_val);
    }

    /**
     * ���[�^�[�l���擾 .
     */
    inline int getQty() {
        return _pPxQuantity->get();
    }

    inline pixcoord getBarPx() {
        return _pPxQuantity->getPx();
    }
    /**
     * ���[�^�[�l�����Z .
     * �ݒ肷��ƁA���݂̃��[�^�[�̒���(_val_px) ���X�V�����
     * @param prm_val ���[�^�[���Z�l
     */
    inline void incQty(int prm_val) {
        _pPxQuantity->inc(prm_val);
    }

    /**
     * ���[�^�[�l�����Z .
     * �ݒ肷��ƁA���݂̃��[�^�[�̒���(_val_px) ���X�V�����
     * @param prm_val ���[�^�[���Z�l
     */
    inline void decQty(int prm_val) {
        _pPxQuantity->dec(prm_val);
    }
    void processBehavior() override;
    void processDraw() override;
    virtual ~GraphBarActor();
};

}
#endif /*GRAPHBARACTOR_H_*/

