#ifndef GGAFCORE_GGAFTREEELEM_H_
#define GGAFCORE_GGAFTREEELEM_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/util/GgafTreeSpace.hpp"
#include "jp/ggaf/core/util/GgafLinearOctree.h"
namespace GgafCore {

/**
 * ���`N���ؔz��p��ԂɂԂ牺����v�f�N���X .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
template<uint32_t BIT_SHIFT_NUM>
class GgafTreeElem : public GgafObject {

    friend class GgafLinearOctree;
    friend class GgafLinearQuadtree;

public:
    /** ��Ԃ̔z�� */
    GgafTreeSpace<BIT_SHIFT_NUM>*  _paSpace;
    /** [r]�v�f�I�u�W�F�N�g�i���ꂪ�{�́j */
    GgafObject* const _pObject;
    /** [r]�v�f�I�u�W�F�N�g�̎�� */
    actorkind _kindbit;
    /** [r]������� */
    GgafTreeSpace<BIT_SHIFT_NUM>* _pSpace_current;
    /** [r]���v�f */
    GgafTreeElem* _pNext;
    /** [r]�O�v�f */
    GgafTreeElem* _pPrev;
    /** [r]�o�^���X�g�p�����N */
    GgafTreeElem* _pRegLinkNext;

    /**
     * �R���X�g���N�^
     * @param prm_pObject �ΏۃI�u�W�F�N�g(�L�����N�^�Ȃ�N���؂ŊǗ����������ۂ̒l)
     * @param prm_kindbit ���̑ΏۃI�u�W�F�N�̎�ʁA��ޕ����s�v�ȏꍇ�́A�C�ӂ̐��l�ł悢�B
     * @return
     */

    /**
     *
     * @param prm_paSpace
     * @param prm_pObject
     * @param prm_kindbit
     */
    GgafTreeElem(GgafTreeSpace<BIT_SHIFT_NUM>* prm_paSpace, GgafObject* prm_pObject, actorkind prm_kindbit) : GgafObject() ,
            _paSpace(prm_paSpace),
        _pObject(prm_pObject) {
        _kindbit = prm_kindbit;
        _pSpace_current = nullptr;
        _pNext = nullptr;
        _pPrev = nullptr;
        _pRegLinkNext = nullptr;
    }

    void dump() {
        _TRACE_N_("o");
    }

    virtual ~GgafTreeElem() {
    }
};

}
#endif /*GGAFCORE_GGAFTREEELEM_H_*/

