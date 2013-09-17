#ifndef GRAPHBARACTOR_H_
#define GRAPHBARACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/util/PxQuantity.h"

namespace GgafLib {

/**
 * ���ʃo�[�i�P�������`�j .
 * @version 1.00
 * @since 2012/09/17
 * @author Masatoshi Tsuge
 */
class GraphBarActor : public DefaultBoardActor {

public:
    /** �����s�N�Z�� */
    const float _chip_width;
    const float _rate_org_chip_width;

    /** ���e�� */
    PxQuantity* _pPxQuantity;
    int _min_val;
    int _max_val;
    bool _is_new_PxQuantity;
public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQuantity config�ς݂� PxQuantity�I�u�W�F�N�g�̎Q��
     */
    GraphBarActor(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQuantity);

    GraphBarActor(const char* prm_name, const char* prm_model);

    /**
     * �����̃o�[�̒l��ێ����� PxQuantity ��u�������� .
     * @param prm_pPxQuantity
     */
    void linkPxQuantity(PxQuantity* prm_pPxQuantity);

    /**
     * �o�[�̒l�ɑ΂���s�N�Z���l��ݒ� .
     * @param prm_max_val �o�[�̒l�̍ő�l
     * @param prm_max_val_px    �o�[�̒l�̍ő�l�ɑ΂����ʂ̃s�N�Z���l
     */
    inline void graduate(int prm_min_val, int prm_max_val, pixcoord prm_max_val_px ) {
        _min_val = prm_min_val;
        _max_val = prm_max_val;
        _pPxQuantity->graduate(prm_max_val, prm_max_val_px);
    }

    /**
     * �o�[�̒l��ݒ� .
     * @param prm_val ���[�^�[�l
     */
    inline void setQty(int prm_val) {
        if (_max_val < prm_val) {
            _pPxQuantity->set(_max_val);
        } else if (_min_val > prm_val) {
            _pPxQuantity->set(_min_val);
        } else {
            _pPxQuantity->set(prm_val);
        }
    }

    /**
     * �o�[�̒l���擾 .
     * @return �o�[�̒l
     */
    inline int getQty() {
        return _pPxQuantity->get();
    }

    /**
     * �o�[�̌��ݒl�ɑΉ�����s�N�Z���l���擾
     * @return �s�N�Z���l
     */
    inline pixcoord getBarPx() {
        return _pPxQuantity->getPx();
    }

    /**
     * �o�[�̒l�����Z .
     * @param prm_val �o�[�̉��Z�l
     */
    inline void incQty(int prm_val) {
        setQty(_pPxQuantity->get() + prm_val);
    }

    /**
     * �o�[�̒l�����Z .
     * @param prm_val �o�[�̌��Z�l
     */
    inline void decQty(int prm_val) {
        setQty(_pPxQuantity->get() - prm_val);
    }

    void processDraw() override;

    virtual ~GraphBarActor();
};

}
#endif /*GRAPHBARACTOR_H_*/

