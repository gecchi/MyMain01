#ifndef GRAPHBARACTOR_H_
#define GRAPHBARACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/util/PxQuantity.h"

namespace GgafLib {

/**
 * ���ʃo�[�i�P�������`�j .
 * @version 1.00
 * @since 2013/09/17
 * @author Masatoshi Tsuge
 */
class GraphBarActor : public DefaultBoardActor {

protected:
    /** [r]�R���X�g���N�^��PxQuantity ��new�����ꍇ true */
    bool _is_new_PxQuantity;
    /** [r]���f���`�b�v�����s�N�Z�� */
    const float _chip_width;
    /** [r] 1.0 / _chip_width �̒l�B�v�Z�p */
    const float _rate_org_chip_width;

public:
    /** [r]���ʃo�[���e�l */
    PxQuantity* _pPxQty;
    /** [r]���ʃo�[�ő�l */
    int _min_val;
    /** [r]���ʃo�[�ŏ��l */
    int _max_val;

public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQty config�ς݂� PxQuantity�I�u�W�F�N�g�̎Q��
     */
    GraphBarActor(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQty);

    GraphBarActor(const char* prm_name, const char* prm_model);

    /**
     * �����̃o�[�̒l��ێ����� PxQuantity ��u�������� .
     * @param prm_pPxQty
     */
    void linkQty(PxQuantity* prm_pPxQty);

    /**
     * �o�[�̒l�ɑ΂���s�N�Z���l��ݒ� .
     * @param prm_max_val �o�[�̒l�̍ő�l
     * @param prm_max_val_px    �o�[�̒l�̍ő�l�ɑ΂����ʂ̃s�N�Z���l
     */

    /**
     * �o�[�̒l�ɑ΂���s�N�Z���̖ڐ����t����B
     * @param prm_min_val �o�[�ŏ��l��ݒ�i����ȉ��̒l�̓Z�b�g�ł��Ȃ��Ȃ�j
     * @param prm_max_val �o�[�ő�l��ݒ�i����ȏ�̒l�̓Z�b�g�ł��Ȃ��Ȃ�j
     * @param prm_px_from_min_to_max �ŏ��l�`�ő�l�̉�ʏ�̃s�N�Z������ݒ�
     */
    inline void graduate(int prm_min_val, int prm_max_val, pixcoord prm_px_from_min_to_max ) {
        _min_val = prm_min_val;
        _max_val = prm_max_val;
        _pPxQty->graduate(prm_max_val - prm_min_val, prm_px_from_min_to_max);
    }

    /**
     * �o�[�̒l��ݒ� .
     * @param prm_val ���[�^�[�l
     */
    inline void setQty(int prm_val) {
        if (_max_val < prm_val) {
            _pPxQty->set(_max_val);
        } else if (_min_val > prm_val) {
            _pPxQty->set(_min_val);
        } else {
            _pPxQty->set(prm_val);
        }
    }

    /**
     * �o�[�̒l���擾 .
     * @return �o�[�̒l
     */
    inline int getQty() {
        return _pPxQty->get();
    }

    /**
     * �o�[�̌��ݒl�ɑΉ�����s�N�Z���l���擾
     * @return �s�N�Z���l
     */
    inline pixcoord getBarPx() {
        return _pPxQty->getPx();
    }

    /**
     * �o�[�̒l�����Z .
     * @param prm_val �o�[�̉��Z�l
     */
    inline void incQty(int prm_val) {
        setQty(_pPxQty->get() + prm_val);
    }

    /**
     * �o�[�̒l�����Z .
     * @param prm_val �o�[�̌��Z�l
     */
    inline void decQty(int prm_val) {
        setQty(_pPxQty->get() - prm_val);
    }

    void processDraw() override;

    virtual ~GraphBarActor();
};

}
#endif /*GRAPHBARACTOR_H_*/

