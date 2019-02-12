#ifndef GGAF_LIB_PIEGRAPHSPRITEACTOR_H_
#define GGAF_LIB_PIEGRAPHSPRITEACTOR_H_
#include "jp/ggaf/lib/actor/DefaultRegularPolygonSpriteActor.h"
#include "jp/ggaf/lib/util/Quantity.hpp"

namespace GgafLib {


/**
 * ���ʉ~�O���t .
 * @version 1.00
 * @since 2013/09/17
 * @author Masatoshi Tsuge
 */
class PieGraphSpriteActor : public DefaultRegularPolygonSpriteActor {

protected:
    /** [r]�R���X�g���N�^��PxQuantity ��new�����ꍇ true */
    bool _is_new_Quantity;

public:
    /** [r]���ʉ~�O���t���e�l<���ۂ̐���, ��t�@���̐�> */
    Quantity<int, int>* _pFanQty;
    /** [r]���ʉ~�O���t�ő�l */
    int _min_val;
    /** [r]���ʉ~�O���t�ŏ��l */
    int _max_val;

public:
    /**
     *
     * @param prm_name
     * @param prm_pFanQty config�ς݂� PxQuantity�I�u�W�F�N�g�̎Q��
     */
    PieGraphSpriteActor(const char* prm_name, const char* prm_model, Quantity<int, int>* prm_pFanQty);

    PieGraphSpriteActor(const char* prm_name, const char* prm_model);

    /**
     * �����̉~�O���t�̒l��ێ����� Quantity ��u�������� .
     * @param prm_pFanQty
     */
    void linkQty(Quantity<int, int>* prm_pFanQty);

    /**
     * �����̉~�O���t�̒l��ێ����� Quantity �̎Q�ƕϐ���ύX .
     * @param prm_pVariable
     */
    void linkVariable(int* prm_pVariable);

    /**
     * �~�O���t�̒l�ɑ΂���s�N�Z���̖ڐ����t����B
     * @param prm_min_val �~�O���t�������l�̍ŏ��l��ݒ�i����ȉ��̒l�̓Z�b�g�ł��Ȃ��Ȃ�j
     * @param prm_max_val �~�O���t�������l�̍ő�l��ݒ�i����ȏ�̒l�̓Z�b�g�ł��Ȃ��Ȃ�j
     * @param prm_min_fan_num prm_min_val�ɑΉ�����FAN�̐�
     * @param prm_max_fan_num prm_max_val�ɑΉ�����FAN�̐�
     */
    inline void scale(int prm_min_val, int prm_max_val, int prm_min_fan_num, int prm_max_fan_num) {
        _min_val = prm_min_val;
        _max_val = prm_max_val;
        _pFanQty->scale(prm_min_val, prm_max_val, prm_min_fan_num, prm_max_fan_num);
    }

    /**
     * �~�O���t�̒l��ݒ� .
     * link���Ă���ꍇ�A�����N���̕ϐ��̒l���ύX�����̂Œ��� .
     * @param prm_val �~�O���t�̒l
     */
    inline void setVal(int prm_val) {
        if (_max_val < prm_val) {
            _pFanQty->setVal(_max_val);
        } else if (_min_val > prm_val) {
            _pFanQty->setVal(_min_val);
        } else {
            _pFanQty->setVal(prm_val);
        }
    }

    /**
     * �~�O���t�̒l���擾 .
     * @return �~�O���t�̒l
     */
    inline int getVal() {
        return _pFanQty->getVal();
    }

    /**
     * �~�O���t�̌��ݒl�ɑΉ�����FAN�̖������擾
     * @return FAN�̖���
     */
    inline int getFanNum() {
        return _pFanQty->getQty();
    }

    /**
     * �~�O���t�̒l�����Z .
     * link���Ă���ꍇ�A�����N���̒l���ύX�����̂Œ��ӁB
     * @param prm_val �~�O���t�̉��Z�l
     */
    inline void incVal(int prm_val) {
        setVal(_pFanQty->getVal() + prm_val);
    }

    /**
     * �~�O���t�̒l�����Z .
     * link���Ă���ꍇ�A�����N���̒l���ύX�����̂Œ��ӁB
     * @param prm_val �~�O���t�̌��Z�l
     */
    inline void decVal(int prm_val) {
        setVal(_pFanQty->getVal() - prm_val);
    }

    void processDraw() override;

    virtual ~PieGraphSpriteActor();
};

}
#endif /*GGAF_LIB_PIEGRAPHSPRITEACTOR_H_*/

