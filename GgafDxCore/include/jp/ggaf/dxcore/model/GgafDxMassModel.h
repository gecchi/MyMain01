#ifndef GGAFDXCORE_GGAFDXMASSMODEL_H_
#define GGAFDXCORE_GGAFDXMASSMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

#define GGAFDXMASS_MAX_INSTACE_NUM 512

/**
 * Mass���b�V�����f���N���X(GgafDxMeshActor�p) .
 * @version 1.00
 * @since 2016/02/26
 * @author Masatoshi Tsuge
 */
class GgafDxMassModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:
    /**
     * ���_���C�A�E�g�i�C���X�^���X�j���
     */
    class VertexInstaceDataInfo {
    public:
        /** �C���X�^���X�f�[�^�̒��_���C�A�E�g�z�� */
        D3DVERTEXELEMENT9* paElement;
        /** �C���X�^���X�f�[�^�̒��_���C�A�E�g�̗v�f�� */
        int element_num;
        /** �C���X�^���X�f�[�^�̂P���_�̃T�C�Y */
        UINT size_vertex_unit_instacedata;
        /** �f�o�C�X�ɗ������ރC���X�^���X�f�[�^�����݂���擪�A�h���X */
        void* pInstancedata;
        VertexInstaceDataInfo() {
            paElement = nullptr;
            element_num = 0;
            size_vertex_unit_instacedata = 0;
            pInstancedata = nullptr;
        }
        ~VertexInstaceDataInfo() {
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
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_model;
    /** �f�o�C�X�̒��_�o�b�t�@�i�C���X�^���X�F���[���h�ϊ��s����A�}�e���A���J���[���j */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_instacedata;
    /** �f�o�C�X�̃C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;
    /** �f�o�C�X�̃V�F�[�_�[���͒��_�t�H�[�}�b�g */
    LPDIRECT3DVERTEXDECLARATION9 _pVertexDeclaration;

    /** �P���_�̃T�C�Y�i���f���j */
    UINT _size_vertex_unit_model;
    /** �P���_�̃T�C�Y�i�C���X�^���X�j */
    UINT _size_vertex_unit_instacedata;
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
    void (*_pFunc_getVertexInstaceData)(void* prm, VertexInstaceDataInfo* out_info);

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxMassModel(const char* prm_model_name);

    /**
     * ���_���C�A�E�g�i�C���X�^���X�f�[�^�j���擾�R�[���o�b�N�֐���o�^���� .
     * Model�N���X�̃R���X�g���N�^���ŌĂяo���A�o�^���Ă��������B
     * @param prm_pFunc_getVertexInstaceData ���_���C�A�E�g�i�C���X�^���X�f�[�^�j���擾�R�[���o�b�N�֐�
     */
    inline void registerCallback_VertexInstaceDataInfo(void (*prm_pFunc_getVertexInstaceData)(void*, VertexInstaceDataInfo*)) {
#ifdef MY_DEBUG
        if (_pFunc_getVertexInstaceData && _pFunc_getVertexInstaceData != prm_pFunc_getVertexInstaceData) {
            throwGgafCriticalException("���ɒ��_���C�A�E�g�͍쐬�ς݂ɂ�������炸�A�ʂ̒�`�֐���ݒ肵�悤�Ƃ��܂����B(1)");
        }
#endif
        _pFunc_getVertexInstaceData = prm_pFunc_getVertexInstaceData;
        if (_pFunc_getVertexInstaceData && _pFunc_getVertexModel) {
            if (_pVertexBuffer_instacedata == nullptr) {
                createVertexElements();
            }
        }
    }
    /**
     * ���_���C�A�E�g�i���f���j���擾�R�[���o�b�N�֐���o�^���� .
     * Actor�N���X�̃R���X�g���N�^���ŌĂяo���A�o�^���Ă��������B
     * @param prm_pFunc_getVertexModel  ���_���C�A�E�g�i���f���f�[�^�j���擾�R�[���o�b�N�֐�
     */
    inline void registerCallback_VertexModelInfo(void (*prm_pFunc_getVertexModel)(void*, VertexModelInfo*)) {
#ifdef MY_DEBUG
        if (_pFunc_getVertexModel && _pFunc_getVertexModel != prm_pFunc_getVertexModel) {
            throwGgafCriticalException("���ɒ��_���C�A�E�g�͍쐬�ς݂ɂ�������炸�A�ʂ̒�`�֐���ݒ肵�悤�Ƃ��܂����B(2)");
        }
#endif
        _pFunc_getVertexModel = prm_pFunc_getVertexModel;
        if (_pFunc_getVertexInstaceData && _pFunc_getVertexModel) {
            if (_pVertexBuffer_instacedata == nullptr) {
                createVertexElements();
            }
        }
    }

    /**
     * ���f���̒��_���C�A�E�g�A���_�C���X�^���X�f�[�^�̍쐬 .
     */
    void createVertexElements();

    virtual void resetStreamSourceFreq();

    virtual void onDeviceLost() override;

    virtual void release() override;


    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxMassModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXMESHSETMODEL_H_*/
