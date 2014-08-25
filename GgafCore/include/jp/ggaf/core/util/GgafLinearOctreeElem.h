#ifndef GGAFCORE_GGAFLINEAROCTREEELEM_H_
#define GGAFCORE_GGAFLINEAROCTREEELEM_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafCore {

/**
 * ���`�����ؔz��p��Ԃ̗v�f�N���X .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class GgafLinearOctreeElem : public GgafObject {

    friend class GgafLinearOctree;

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
     * @param prm_pSpace_target ����������
     */
    void belongTo(GgafLinearOctreeSpace* prm_pSpace_target);

public:
    /** [r]�����c���[ */
    GgafLinearOctree* _pLinearOctree;
    /** [r]������� */
    GgafLinearOctreeSpace* _pSpace_current;
    /** [r]���v�f */
    GgafLinearOctreeElem* _pNext;
    /** [r]�O�v�f */
    GgafLinearOctreeElem* _pPrev;
    /** [r]�ΏۃI�u�W�F�N�g */
    GgafObject* _pObject;
    /** [r]�ΏۃI�u�W�F�N�g��� */
    uint32_t _kindbit;
    /** [r]�o�^���X�g�p�����N */
    GgafLinearOctreeElem* _pRegLinkNext;

    /**
     * �R���X�g���N�^
     * @param prm_pObject �ΏۃI�u�W�F�N�g(�L�����N�^�Ȃǔ����؂ŊǗ����������ۂ̒l)
     * @param prm_kindbit ���̑ΏۃI�u�W�F�N�̎�ʁA��ޕ����s�v�ȏꍇ�́A�C�ӂ̐��l�ł悢�B
     * @return
     */
    GgafLinearOctreeElem(GgafObject* prm_pObject, uint32_t prm_kindbit);

    void dump();

    virtual ~GgafLinearOctreeElem();
};

}
#endif /*GGAFCORE_GGAFLINEAROCTREEELEM_H_*/

