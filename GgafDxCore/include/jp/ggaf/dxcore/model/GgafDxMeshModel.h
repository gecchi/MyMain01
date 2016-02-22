#ifndef GGAFDXCORE_GGAFDXMESHMODEL_H_
#define GGAFDXCORE_GGAFDXMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

// �{�v���O������ Paul Coppens ����̍쐬���ꂽ�AX�t�@�C����ǂݍ��ރT���v��
// �����ɁA�Ǝ��ɉ��ǏC���i��f�o�b�O�j�����N���X���g�p���Ă��܂��B
// ���肪�Ƃ� Paul����B
//
// �y�Ώہz
// Frm ���O��Ԃ̃N���X
//
// �yLoading and displaying .X files without DirectX �z
// http://www.gamedev.net/reference/programming/features/xfilepc/
//
//                                         2009/03/06 Masatoshi Tsuge

/**
 * ���b�V�����f���N���X(GgafDxMeshActor�p).
 * GgafDxMeshModel �͓Ǝ���X�t�@�C�����烂�f���f�[�^��ǂݍ��݁A<BR>
 * �I�u�W�F�N�g��`�悷��@�\���������ÓI���f���p�̃N���X�ł��B <BR>
 * <b>��������</b>  <BR>
 * �EX�t�@�C���̒��_����ۏ؁B <BR>
 * �EGgafDxD3DXMeshModel ���ǂݍ��݂������itemplate�Ƃ����ĂȂ��j�B <BR>
 * �EX�t�@�C���ɕ������b�V���o�^����Ă���ꍇ�A�����A�����Ĉ�̒��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�ƈ�������
 *   �`�悪��荂���ɂȂ�B <BR>
 * <b>���Z����</b> <BR>
 * �ED3DXLoadMeshFromX���g�p���Ă��炸�AX�t�@�C���� template �錾�͌��Ă��Ȃ����߁A�f�[�^�\�����̃w�b�_��
 *  ("Mesh"��"TextureFilename"���j�� �n�[�h�R�[�f�B���O����Ă���B�\�����Ȃ����G��X�t�@�C���͂܂��ǂ߂Ȃ��B<BR>
 * �E����ɋ��L���_�̖@���𕽋ω����� <BR>
 * <BR>
 * �u���̑����ӓ_�v<BR>
 * ���_����ۏ؂��邽�߁A�@��������Ȃ��Ȃ��Ă��܂��ꍇ������B�����ŋ��L���_�̖@���͓Ǝ��v�Z�ŕ��ω����s�����Ƃɂ��Ă���B<BR>
 * �����G�b�W���N�b�L���o�������ꍇ�́AX�t�@�C�����ōŏ����炿���Ɨ����̂Ȃ�Β��_��32�����΂悢�B<BR>
 * �܂��A�@���̖���X�t�@�C���ł����_�C���f�b�N�X���玩���Ŗ@�����v�Z����������B<BR>
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class GgafDxMeshModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:
    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

    class VERTEX : public GgafDxModel::VERTEX_3D_BASE {
    public:
        DWORD color; // ���_�̐F�i���ݖ��g�p�j
        float tu, tv; // �e�N�X�`�����W
        float tan_x, tan_y, tan_z; //
        float bin_x, bin_y, bin_z;
    };

    /** ���_��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;
    /** �C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;

    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;
    INDEXPARAM* _paIndexParam;

    UINT _material_list_grp_num;

    VERTEX* _paVtxBuffer_org;
    WORD* _paIdxBuffer_org;

//    /** Paul���񃂃f�� */
//    Frm::Model3D* _pModel3D;
//    /** Paul���񃁃b�V�� */
//    Frm::Mesh* _pMeshesFront;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxMeshModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXMESHMODEL_H_*/

