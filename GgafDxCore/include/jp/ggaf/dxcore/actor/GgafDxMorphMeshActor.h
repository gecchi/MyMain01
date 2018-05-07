#ifndef GGAFDXCORE_GGAFDXMORPHMESHACTOR_H_
#define GGAFDXCORE_GGAFDXMORPHMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpherAssistantA.hpp"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * ���[�t���b�V���A�N�^�[.
 * GgafDxFigureActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\�y��<BR>
 * ���[�t�A�j���[�V�����@�\��������A�N�^�[<BR>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDxMorphMeshActor : public GgafDxFigureActor {

private:
    /** ���[�t�B���O�x���I�u�W�F�N�g */
    GgafDxMorpher<GgafDxMorphMeshActor>* const _pMorpher;

public:
    /** [r]���[�t�^�[�Q�b�g��(���f���̃R�s�[�����l) */
    int _morph_target_num;
    /** [r]���f������ */
    GgafDxMorphMeshModel* const _pMorphMeshModel;
    /** [r]�G�t�F�N�g���� */
    GgafDxMorphMeshEffect* const _pMorphMeshEffect;
    /** [r/w]���[�t�^�[�Q�b�g�̏d��(0.0 �` 1.0) */
    float _weight[MAX_MORPH_TARGET+1]; //[0]�͖��g�p�A[1]�`[6]�����[�t�^�[�Q�b�g1�`6�̏d��

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    GgafDxMorphMeshActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker );

    /**
     * ���ʌp���p�R���X�g���N�^
     * @param prm_name �A�N�^�[���́i�C�Ӂj
     * @param prm_model_id ���f����`��
     * @param prm_model_type ���f���^�C�v
     * @param prm_effect_id �G�t�F�N�g��`��
     * @param prm_effect_type �G�t�F�N�g�^�C�v
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    GgafDxMorphMeshActor(const char* prm_name,
                         const char* prm_model_id,
                         const char prm_model_type,
                         const char* prm_effect_id,
                         const char prm_effect_type,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker);

    virtual void processDraw() override;

    /**
     * ���[�t�^�[�Q�b�g���b�V�����擾
     * @return ���[�t�^�[�Q�b�g���b�V����
     */
    int getMorphTergetNum();

    /**
     * ���[�t�^�[�Q�b�g�̏d�݂𒼐ڎw�� .
     * @param prm_target_mesh_no ���[�t�^�[�Q�b�g���b�V��NO(1 �`)
     * @param prm_weight �d�� �d��0.0�`1.0�B����ȏ���\
     */
    void setMorphWeight(int prm_target_mesh_no, float prm_weight);

    /**
     * �S���[�t�^�[�Q�b�g�̏d�݂𒼐ڎw��
     * @param prm_target_mesh_no �d��0.0�`1.0�B����ȏ���\
     */
    void setMorphWeight(float prm_weight);

    float getMorphWeight(int prm_target_mesh_no);

    void addMorphWeight(int prm_target_mesh_no, float prm_add_weight);

    inline GgafDxMorpher<GgafDxMorphMeshActor>* getMorpher() {
        return _pMorpher;
    }

    virtual ~GgafDxMorphMeshActor (); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXMORPHMESHACTOR_H_*/
