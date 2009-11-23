#ifndef GGAFLINEAROCTREEELEM_H_
#define GGAFLINEAROCTREEELEM_H_
namespace GgafCore {


/**
 * ���`�����ؔz���Ԃ̗v�f�N���X .
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

    /**
     * �R���X�g���N�^
     * @param prm_pObject �ΏۃI�u�W�F�N�g(�L�����N�^�Ȃǔ����؂ŊǗ����������ۂ̒l)
     * @param prm_kindbit ���̑ΏۃI�u�W�F�N�̎�ʁA��ޕ����s�v�ȏꍇ�́A�C�ӂ̐��l�ł悢�B
     * @return
     */
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

