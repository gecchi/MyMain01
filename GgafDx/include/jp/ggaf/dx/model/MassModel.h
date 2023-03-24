#ifndef GGAF_DX_MASSMODEL_H_
#define GGAF_DX_MASSMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

#define GGAFDXMASS_MAX_INSTANCE_NUM 512

/**
 * Mass���f�����N���X .
 * @version 1.00
 * @since 2016/02/26
 * @author Masatoshi Tsuge
 */
class MassModel : public Model {
    friend class ModelManager;

public:
    /**
     * ���_���C�A�E�g�i�C���X�^���X�j���
     */
    class VertexInstanceDataInfo {
    public:
        /** �C���X�^���X�f�[�^�̒��_���C�A�E�g�z�� */
        D3DVERTEXELEMENT9* paElement;
        /** �C���X�^���X�f�[�^�̒��_���C�A�E�g�̗v�f�� */
        int element_num;
        /** �C���X�^���X�f�[�^�̂P���_�̃T�C�Y */
        UINT size_vertex_unit_instancedata;
        /** �f�o�C�X�ɗ������ރC���X�^���X�f�[�^�����݂���擪�A�h���X */
        void* pInstancedata;
        VertexInstanceDataInfo() {
            paElement = nullptr;
            element_num = 0;
            size_vertex_unit_instancedata = 0;
            pInstancedata = nullptr;
        }
        ~VertexInstanceDataInfo() {
            GGAF_DELETEARR_NULLABLE(paElement);
        }
    };

    /**
     * ���_���C�A�E�g�i���f���j���
     */
    class VertexModelInfo {
    public:
        /** ���f�����_���C�A�E�g */
        D3DVERTEXELEMENT9* paElement;
        /** ���f�����_���C�A�E�g�̗v�f�� */
        int element_num;
        VertexModelInfo() {
            paElement = nullptr;
            element_num = 0;
        }
        ~VertexModelInfo() {
            GGAF_DELETEARR_NULLABLE(paElement);
        }
    };

    /** �f�o�C�X�̒��_�o�b�t�@�i���f���j */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer_model;
    /** �f�o�C�X�̒��_�o�b�t�@�i�C���X�^���X�F���[���h�ϊ��s����A�}�e���A���J���[���j */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer_instancedata;
    /** �f�o�C�X�̃C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _paIndexBuffer;
    /** �f�o�C�X�̃V�F�[�_�[���͒��_�t�H�[�}�b�g */
    LPDIRECT3DVERTEXDECLARATION9 _pVertexDeclaration;

    /** �P���_�̃T�C�Y�i���f���j */
    UINT _size_vertex_unit_model;
    /** �P���_�̃T�C�Y�i�C���X�^���X�j */
    UINT _size_vertex_unit_instancedata;
    /** �P���f�����_�T�C�Y�v */
    UINT _size_vertices_model;
    /** ���f�����_�� */
    UINT _nVertices;
    /** ���f���ʂ̐� */
    UINT _nFaces;
    /** ���_�o�b�t�@�i�C���X�^���X�f�[�^�j�ɗ������ރf�[�^�z��̐擪�A�h���X */
    void* _pInstancedata;
    /**
     * ���_���C�A�E�g�i���f���j���擾�R�[���o�b�N�֐� .
     * @param prm �Ȃɂ�����̃p�����[�^
     * @param out_info ���_���C�A�E�g�i���f���j��񂪐ݒ肳���
     */
    void (*_pFunc_getVertexModel)(void* prm, VertexModelInfo* out_info);
    /**
     * ���_���C�A�E�g�i�C���X�^���X�f�[�^�j���擾�R�[���o�b�N�֐� .
     * @param prm �Ȃɂ�����̃p�����[�^
     * @param out_info ���_���C�A�E�g�i�C���X�^���X�j��񂪐ݒ肳���
     */
    void (*_pFunc_getVertexInstanceData)(void* prm, VertexInstanceDataInfo* out_info);

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_model_id �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    MassModel(const char* prm_model_id);

    /**
     * ���_���C�A�E�g�i�C���X�^���X�f�[�^�j���擾�R�[���o�b�N�֐���o�^���� .
     * Model�N���X�̃R���X�g���N�^���ŌĂяo���A�o�^���Ă��������B
     * @param prm_pFunc_getVertexInstanceData ���_���C�A�E�g�i�C���X�^���X�f�[�^�j���擾�R�[���o�b�N�֐�
     */
    inline void registerCallback_VertexInstanceDataInfo(void (*prm_pFunc_getVertexInstanceData)(void*, VertexInstanceDataInfo*)) {
        _TRACE3_("_model_id=" << _model_id << " start");
#ifdef MY_DEBUG
        if (_pFunc_getVertexInstanceData && _pFunc_getVertexInstanceData != prm_pFunc_getVertexInstanceData) {
            throwCriticalException("���ɒ��_���C�A�E�g�͍쐬�ς݂ɂ�������炸�A�ʂ̒�`�֐���ݒ肵�悤�Ƃ��܂����B(1)");
        }
#endif
        _pFunc_getVertexInstanceData = prm_pFunc_getVertexInstanceData;
        if (_pFunc_getVertexInstanceData && _pFunc_getVertexModel) {
            if (_paVertexBuffer_instancedata == nullptr) {
                createVertexElements();
            }
        }
        _TRACE3_("_model_id=" << _model_id << " end");
    }
    /**
     * ���_���C�A�E�g�i���f���j���擾�R�[���o�b�N�֐���o�^���� .
     * Actor�N���X�̃R���X�g���N�^���ŌĂяo���A�o�^���Ă��������B
     * @param prm_pFunc_getVertexModel  ���_���C�A�E�g�i���f���f�[�^�j���擾�R�[���o�b�N�֐�
     */
    inline void registerCallback_VertexModelInfo(void (*prm_pFunc_getVertexModel)(void*, VertexModelInfo*)) {
        _TRACE3_("_model_id=" << _model_id << " start");
#ifdef MY_DEBUG
        if (_pFunc_getVertexModel && _pFunc_getVertexModel != prm_pFunc_getVertexModel) {
            throwCriticalException("���ɒ��_���C�A�E�g�͍쐬�ς݂ɂ�������炸�A�ʂ̒�`�֐���ݒ肵�悤�Ƃ��܂����B(2)");
        }
#endif
        _pFunc_getVertexModel = prm_pFunc_getVertexModel;
        if (_pFunc_getVertexInstanceData && _pFunc_getVertexModel) {
            if (_paVertexBuffer_instancedata == nullptr) {
                createVertexElements();
            }
        }
        _TRACE3_("_model_id=" << _model_id << " end");
    }

    /**
     * ���f���̒��_���C�A�E�g�A���_�C���X�^���X�f�[�^�̍쐬 .
     */
    void createVertexElements();

    virtual void resetStreamSourceFreq();

    virtual void onDeviceLost() override;

    virtual void release() override;

    virtual void restore() override;
    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~MassModel();
};

}
#endif /*GGAF_DX_MESHSETMODEL_H_*/
