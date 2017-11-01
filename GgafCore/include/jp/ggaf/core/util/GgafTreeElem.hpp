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
template<uint32_t DIMENSION>
class GgafTreeElem : public GgafObject {

    friend class GgafLinearOctree;
    friend class GgafLinearQuadtree;

public:
    /** ��Ԃ̔z�� */
    GgafTreeSpace<DIMENSION>* _paSpace;
    /** [r]�v�f�I�u�W�F�N�g�i���ꂪ�{�́j */
    GgafObject* const _pObject;
    /** [r]�v�f�I�u�W�F�N�g�̎�� */
    kind_t _kind;
    /** [r]������� */
    GgafTreeSpace<DIMENSION>* _pSpace_current;
    /** [r]���v�f */
    GgafTreeElem* _pNext;
    /** [r]�O�v�f */
    GgafTreeElem* _pPrev;
    /** [r]�o�^���X�g�p�����N */
    GgafTreeElem* _pRegLinkNext;

    /**
     * �R���X�g���N�^ .
     * @param prm_paSpace ��Ԃ̔z��ւ̃|�C���^
     * @param prm_pObject �ΏۃI�u�W�F�N�g(�L�����N�^�Ȃ�N���؂ŊǗ����������ۂ̒l)
     */
    GgafTreeElem(GgafTreeSpace<DIMENSION>* prm_paSpace, GgafObject* prm_pObject) : GgafObject() ,
        _paSpace(prm_paSpace),
        _pObject(prm_pObject)
    {
        _kind = 0;
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

