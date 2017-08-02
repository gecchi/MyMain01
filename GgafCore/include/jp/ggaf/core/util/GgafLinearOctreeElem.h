#ifndef GGAFCORE_GGAFLINEAROCTREEELEM_H_
#define GGAFCORE_GGAFLINEAROCTREEELEM_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafCore {

/**
 * ���`�����ؔz��p��ԂɂԂ牺����v�f�N���X .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class GgafLinearOctreeElem : public GgafObject {

    friend class GgafLinearOctree;
    friend class GgafLinearQuadtree;
private:
    /**
     * ���g�������Ԃ��痣�E�A������Ԃ̏��������Ȃ�폜 .
     */
    void clear();
    /**
     * ���g�������Ԃ̖����ɂԂ牺����ǉ������ .
     * ��x belongTo() �����s�����������Ȃ�΁A
     * GgafLinearOctree::clearElem();
     * �ɂāA�����ؑS�v�f�N���A�����܂ŁA�ēx belongTo() �͏o���Ȃ��B
     * @param prm_pOctant_target ����������
     */
    void belongTo(GgafLinearOctreeOctant* const prm_pOctant_target);

public:
    /** [r]�����c���[ */
    GgafLinearOctree* const _pLinearOctree;
    /** [r]�v�f�I�u�W�F�N�g�i���ꂪ�{�́j */
    GgafObject* const _pObject;
    /** [r]�v�f�I�u�W�F�N�g�̎�� */
    uint32_t _kindbit;
    /** [r]������� */
    GgafLinearOctreeOctant* _pOctant_current;
    /** [r]���v�f */
    GgafLinearOctreeElem* _pNext;
    /** [r]�O�v�f */
    GgafLinearOctreeElem* _pPrev;
    /** [r]�o�^���X�g�p�����N */
    GgafLinearOctreeElem* _pRegLinkNext;

    /**
     * �R���X�g���N�^
     * @param prm_pObject �ΏۃI�u�W�F�N�g(�L�����N�^�Ȃǔ����؂ŊǗ����������ۂ̒l)
     * @param prm_kindbit ���̑ΏۃI�u�W�F�N�̎�ʁA��ޕ����s�v�ȏꍇ�́A�C�ӂ̐��l�ł悢�B
     * @return
     */
    GgafLinearOctreeElem(GgafLinearOctree* prm_pLinearOctree, GgafObject* prm_pObject, uint32_t prm_kindbit);

    void dump();

    virtual ~GgafLinearOctreeElem();
};

}
#endif /*GGAFCORE_GGAFLINEAROCTREEELEM_H_*/

