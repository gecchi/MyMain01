#ifndef GGAF_CORE_TREEELEM_H_
#define GGAF_CORE_TREEELEM_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/util/TreeSpace.hpp"
#include "jp/ggaf/core/util/LinearOctree.h"
namespace GgafCore {

/**
 * ���`N���ؔz��p��ԂɂԂ牺����v�f�N���X .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
template<uint32_t DIMENSION>
class TreeElem : public Object {

    friend class LinearOctree;
    friend class LinearQuadtree;

public:
    /** ��Ԃ̔z�� */
    TreeSpace<DIMENSION>* _paSpace;
    /** [r]�v�f�I�u�W�F�N�g�i���ꂪ�{�́j */
    Object* const _pObject;
    /** [r]�v�f�I�u�W�F�N�g�̎�� */
    kind_t _kind;
    /** [r]������� */
    TreeSpace<DIMENSION>* _pSpace_current;
    /** [r]���v�f */
    TreeElem* _pNext;
    /** [r]�O�v�f */
    TreeElem* _pPrev;
    /** [r]�o�^���X�g�p�����N */
    TreeElem* _pRegLinkNext;

    /**
     * �R���X�g���N�^ .
     * @param prm_paSpace ��Ԃ̔z��ւ̃|�C���^
     * @param prm_pObject �ΏۃI�u�W�F�N�g(�L�����N�^�Ȃ�N���؂ŊǗ����������ۂ̒l)
     */
    TreeElem(TreeSpace<DIMENSION>* prm_paSpace, Object* prm_pObject) : Object() ,
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

    virtual ~TreeElem() {
    }
};

}
#endif /*GGAF_CORE_TREEELEM_H_*/

