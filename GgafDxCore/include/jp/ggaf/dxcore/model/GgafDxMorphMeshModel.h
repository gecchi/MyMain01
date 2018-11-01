#ifndef GGAFDXCORE_GGAFDXMORPHMESHMODEL_H_
#define GGAFDXCORE_GGAFDXMORPHMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

/**
 * GgafDxMorphMeshModel�p�̃��f���N���X.
 * GgafDxMorphMeshModel �� GgafDxMeshModel �̕`�悷��@�\�ɉ����A���[�t�A�j���[�V�����@�\��L���郂�f���ł��B<BR>
 * <b>�����̃��f���� ( prm_model_name ) �̗^�������Ɠǂݍ��܂��X�t�@�C���ɂ���</b><BR>
 * ���၄<BR>
 * <table border=1>
 * <tr>
 * <th>prm_model_name</th>
 * <th>�v���C�}�����b�V�� X�t�@�C��</th>
 * <th>���[�t�^�[�Q�b�g X�t�@�C��</th>
 * </tr>
 * <tr>
 * <td>"M,ball_0"</td>
 * <td>ball_0.x</td>
 * <td>����</td>
 * </tr>
 * <tr>
 * <td>"M,ball_1"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x</td>
 * </tr>
 * <tr>
 * <td>"M,ball_2"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x, ball_2.x</td>
 * </tr>
 * <tr>
 * <td>"M,ball_6"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x, ball_2.x, ball_3.x,�E�E�Eball_6.x</td>
 * </tr>
 * </table>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDxMorphMeshModel : public GgafDxModel {
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


    /** �v���C�}�����b�V���̒��_�t�H�[�}�b�g��` */
    struct VERTEX_PRIMARY : public GgafDxModel::VERTEX_3D_BASE {
        DWORD color;      // ���_�̐F�i���ݖ��g�p�j
        float tu, tv;     // �e�N�X�`�����W
    };

    /** ���[�t�^�[�Q�b�g���b�V���̒��_�t�H�[�}�b�g��` */
    struct VERTEX_MORPH : public GgafDxModel::VERTEX_3D_BASE {
    };

    /** ���[�t�^�[�Q�b�g�� */
    int _morph_target_num;
    /** �V�F�[�_�[���͒��_�t�H�[�}�b�g */
    LPDIRECT3DVERTEXDECLARATION9 _pVertexDeclaration;
    /** ���_�o�b�t�@�i�v���C�}���j */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_primary;
    /** ���_�o�b�t�@�̔z��i�v�f�������[�t�^�[�Q�b�g���j */
    LPDIRECT3DVERTEXBUFFER9* _paIDirect3DVertexBuffer9_morph;

    /** �C���f�b�N�X�o�b�t�@�i�v���C�}���̂݁j */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;

    /** ���_�̃T�C�Y�i�v���C�}���j */
    UINT _size_vertices_primary;
    /** 1���_�̃T�C�Y�i�v���C�}���j */
    UINT _size_vertex_unit_primary;
    /** ���_�̃T�C�Y�i���[�t�^�[�Q�b�g�j */
    UINT _size_vertices_morph;
    /** 1���_�̃T�C�Y�i���[�t�^�[�Q�b�g�j */
    UINT _size_vertex_unit_morph;

    /** DrawIndexedPrimitive�`��p�����[�^�[�i�v���C�}���̂݁j */
    INDEXPARAM* _paIndexParam;
    /** �}�e���A����ސ��i�v���C�}���̂݁j */
    UINT _material_list_grp_num;

    /** ���_�o�b�t�@�̎ʂ��R�s�[�̒��_�z��i�v���C�}���j */
    VERTEX_PRIMARY* _paVtxBuffer_data_primary;
    /** ���_�o�b�t�@�̎ʂ��R�s�[�̒��_�z��̃��[�t�^�[�Q�b�g���z�� */
    VERTEX_MORPH**  _papaVtxBuffer_data_morph;
    /** �C���f�b�N�X�o�b�t�@�̎ʂ��R�s�[�i�v���C�}���̂݁j */
    WORD* _paIndexBuffer_data;

    /** Paul���񃂃f���i�v�f�����v���C�}���{���[�t�^�[�Q�b�g���j */
    Frm::Model3D** _papModel3D;
    /** Paul���񃁃b�V���i�v�f�����v���C�}���{���[�t�^�[�Q�b�g���j */
    Frm::Mesh** _papMeshesFront;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name ���f����`�̎��ʖ�
     */
    GgafDxMorphMeshModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxMorphMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXMORPHMESHMODEL_H_*/
