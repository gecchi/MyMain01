#ifndef GGAFLIB_GRAPHBARACTOR_H_
#define GGAFLIB_GRAPHBARACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/util/Quantity.hpp"

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
    bool _is_new_Quantity;
    /** [r]���f���`�b�v�����s�N�Z�� */
    const float _chip_width;
    /** [r] 1.0 / _chip_width �̒l�B�v�Z�p */
    const float _rate_org_chip_width;

public:
    /** [r]���ʃo�[���e�l */
    Quantity<int, pixcoord>* _pPxQty;
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
    GraphBarActor(const char* prm_name, const char* prm_model, Quantity<int, pixcoord>* prm_pPxQty);

    GraphBarActor(const char* prm_name, const char* prm_model);

    /**
     * �����̃o�[�̒l��ێ����� Quantity ��u�������� .
     * @param prm_pPxQty
     */
    void linkQty(Quantity<int, pixcoord>* prm_pPxQty);

    /**
     * �����̃o�[�̒l��ێ����� Quantity �̎Q�ƕϐ���ύX .
     * @param prm_pVariable
     */
    void linkVariable(int* prm_pVariable);

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
     * link���Ă���ꍇ�A�����N���̒l���ύX�����̂Œ��� .
     * @param prm_val ���[�^�[�l
     */
    inline void setVal(int prm_val) {
        if (_max_val < prm_val) {
            _pPxQty->setVal(_max_val);
        } else if (_min_val > prm_val) {
            _pPxQty->setVal(_min_val);
        } else {
            _pPxQty->setVal(prm_val);
        }
    }

    /**
     * �o�[�̒l���擾 .
     * @return �o�[�̒l
     */
    inline int getVal() {
        return _pPxQty->getVal();
    }

    /**
     * �o�[�̌��ݒl�ɑΉ�����s�N�Z���l���擾
     * @return �s�N�Z���l
     */
    inline pixcoord getPix() {
        return _pPxQty->getQty();
    }

    /**
     * �o�[�̒l�����Z .
     * link���Ă���ꍇ�A�����N���̒l���ύX�����̂Œ��ӁB
     * @param prm_val �o�[�̉��Z�l
     */
    inline void incVal(int prm_val) {
        setVal(_pPxQty->getVal() + prm_val);
    }

    /**
     * �o�[�̒l�����Z .
     * link���Ă���ꍇ�A�����N���̒l���ύX�����̂Œ��ӁB
     * @param prm_val �o�[�̌��Z�l
     */
    inline void decVal(int prm_val) {
        setVal(_pPxQty->getVal() - prm_val);
    }

    void processDraw() override;

    virtual ~GraphBarActor();
};

}
#endif /*GGAFLIB_GRAPHBARACTOR_H_*/

