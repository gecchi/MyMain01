#ifndef GGAF_DX_REGULARPOLYGONBOARDMODEL_H_
#define GGAF_DX_REGULARPOLYGONBOARDMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/interface/IPlaneModel.h"

namespace GgafDx {

/**
 * RegularPolygonBoardActor�p���f���N���X.
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class RegularPolygonBoardModel : public Model, public IPlaneModel {
    friend class ModelManager;
    friend class RegularPolygonBoardActor;

public:
    struct VERTEX : public Model::VERTEX_POS {
        float tu, tv; // �e�N�X�`�����W
    };

    /** ���_��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;
    VERTEX* _paVertexBuffer_data;

    /** FAN�`�揇���� 1:���v���/1�ȊO:�����v��� */
    int _drawing_order;
    /** �����p�`�� */
    int _angle_num;
    /** �ŏ��̒��_�� x ���W */
    float _y_center;
    /** �ŏ��̒��_�� y ���W */
    float _x_center;
    /** �ŏ��̒��_�� u ���W */
    float _u_center;
    /** �ŏ��̒��_�� v ���W */
    float _v_center;
public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_id �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    RegularPolygonBoardModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�RegularPolygonBoardModelManager�ł���<BR>
     */
    virtual ~RegularPolygonBoardModel();

};

}
#endif /*GGAF_DX_REGULARPOLYGONBOARDMODEL_H_*/
