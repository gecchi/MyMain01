#ifndef GGAFLINEAROCTREEELEM_H_
#define GGAFLINEAROCTREEELEM_H_
namespace GgafCore {


/**
 * ��ԗv�f�N���X .
 */
class GgafLinearOctreeElem {
public:
    /** �����c���[ */
    GgafLinearOctree* _pLinearOctree;
    /** ������� */
    GgafLinearOctreeSpace* _pSpace_Current;
    /** ���v�f */
    GgafLinearOctreeElem* _pNext;
    /** �O�v�f */
    GgafLinearOctreeElem* _pPrev;
    /** �ΏۃI�u�W�F�N�g */
    GgafObject* _pObject;
    /** �ΏۃI�u�W�F�N�g��� */
    DWORD _kindbit;
    /** �o�^���X�g�p�����N */
    GgafLinearOctreeElem* _pRegLinkNext;

    GgafLinearOctreeElem(GgafObject* prm_pObject, DWORD prm_kindbit);

    /**
     * ���g�����痣�E
     */
    void extract();

    /**
     * ���g�������Ԃ̖����ɒǉ�
     */
    void addElem(GgafLinearOctreeSpace* prm_pSpace_target);

    /**
     * ���g�����瑼��Ԃֈړ�
     * extract()����addElem()���܂�.
     * @param prm_pSpace_target
     */
    //void moveToSpace(GgafLinearOctreeSpace* prm_pSpace_target);
    void dump();

    virtual ~GgafLinearOctreeElem();
};

}
#endif /*GGAFLINEAROCTREEELEM_H_*/

