#ifndef GGAFDXMORPHMESHMODEL_H_
#define GGAFDXMORPHMESHMODEL_H_
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
 * <td>"M/0/ball"</td>
 * <td>ball_0.x</td>
 * <td>����</td>
 * </tr>
 * <tr>
 * <td>"M/1/ball"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x</td>
 * </tr>
 * <tr>
 * <td>"M/2/ball"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x<BR>ball_2.x</td>
 * </tr>
 * <tr>
 * <td>"M/3/ball"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x<BR>ball_2.x<BR>ball_3.x</td>
 * </tr>
 * <tr>
 * <td>"M/6/ball"</td>
 * <td>ball_0.x</td>
 * <td>ball_1.x<BR>ball_2.x<BR>ball_3.x<BR>�E�E�E<BR>ball_6.x</td>
 * </tr>
 * </table>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDxMorphMeshModel : public GgafDxModel {
    friend class GgafDxModelManager;

protected:
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
    struct VERTEX_PRIMARY {
        float x, y, z;    // ���_���W
        float nx, ny, nz; // �@��
        DWORD color;      // ���_�̐F�i���ݖ��g�p�j
        float tu, tv;     // �e�N�X�`�����W
    };

    /** ���[�t�^�[�Q�b�g���b�V���̒��_�t�H�[�}�b�g��` */
    struct VERTEX_MORPH {
        float x, y, z;    // ���_���W
        float nx, ny, nz; // �@��
    };

    /** ���[�t�^�[�Q�b�g�� */
    int _morph_target_num;
    /** �V�F�[�_�[���͒��_�t�H�[�}�b�g */
    LPDIRECT3DVERTEXDECLARATION9 _pIDirect3DVertexDeclaration9;
    /** ���_�o�b�t�@�i�v���C�}���j */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9_primary;
    /** ���_�o�b�t�@�̔z��i�v�f�������[�t�^�[�Q�b�g���j */
    LPDIRECT3DVERTEXBUFFER9* _paIDirect3DVertexBuffer9_morph;

    /** �C���f�b�N�X�o�b�t�@�i�v���C�}���̂݁j */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;


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
    UINT _nMaterialListGrp;

    /** ���_�o�b�t�@�̎ʂ��R�s�[�̒��_�z��i�v���C�}���j */
    VERTEX_PRIMARY* _paVtxBuffer_org_primary;
    /** ���_�o�b�t�@�̎ʂ��R�s�[�̒��_�z��̃��[�t�^�[�Q�b�g���z�� */
    VERTEX_MORPH**  _papaVtxBuffer_org_morph;
    /** �C���f�b�N�X�o�b�t�@�̎ʂ��R�s�[�i�v���C�}���̂݁j */
    WORD* _paIdxBuffer_org;

    /** Paul���񃂃f���i�v�f�����v���C�}���{���[�t�^�[�Q�b�g���j */
    Frm::Model3D** _papModel3D;
    /** Paul���񃁃b�V���i�v�f�����v���C�}���{���[�t�^�[�Q�b�g���j */
    Frm::Mesh** _papMeshesFront;

    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name ���f����`�̎��ʖ�
     */
    GgafDxMorphMeshModel(char* prm_model_name);

public:

    /**
     * GgafDxMorphMeshModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDxMorphMeshModel
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxMorphMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXMORPHMESHMODEL_H_*/