#ifndef GGAFDXCORE_GGAFDXDYNAD3DXMESHACTOR_H_
#define GGAFDXCORE_GGAFDXDYNAD3DXMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

namespace GgafDxCore {

//���ӁF���̃N���X�͌��ݖ��g�p�ł��B�폜�\��B
//     �Œ�@�\�p�C�v���C�����ɒ��_���������̂��ߍ쐬�������A
//     ���݂͑S�ăv���O���}�u���V�F�[�_�[�ł��邽�߁A�����g��Ȃ��B
/**
 * ���b�V���A�N�^�[.
 * GgafDxDrawableActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł��B<BR>
 * GgafDxD3DXMeshActor �Ƃ̈Ⴂ�́A���_�o�b�t�@�ɒ��ڃA�N�Z�X�����Ƃɍl�����āA<BR>
 * D3DXMESH_DYNAMIC �I�v�V�������g�p���Ă���Ƃ��낾���ł��B<BR>
 * ���_�����b�N����ꍇ��GgafDxD3DXMeshActor�ł͂Ȃ��A��������p�����Ă��������B<BR>
 * @version 1.00
 * @since 2008/11/17
 * @author Masatoshi Tsuge
 */
class GgafDxDynaD3DXMeshActor : public GgafDxDrawableActor {

public:
    static DWORD FVF;
    GgafDxD3DXMeshModel* _pD3DXMeshModel;
    /** �G�t�F�N�g���� */
    GgafDxMeshEffect* _pMeshEffect;

public:
    GgafDxDynaD3DXMeshActor(const char* prm_name,
                             const char* prm_model_id,
                             const char* prm_effect_id,
                             const char* prm_technique,
                             GgafCore::GgafStatus* prm_pStat,
                             GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    /**
     * ���ݒ�.
     * @param prm_alpha
     */
    virtual void setAlpha(float prm_alpha) override;

    /**
     * �����Z .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;

    virtual ~GgafDxDynaD3DXMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXDYNAD3DXMESHACTOR_H_*/
