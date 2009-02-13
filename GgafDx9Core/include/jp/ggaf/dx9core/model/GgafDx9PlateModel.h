#ifndef GGAFDX9PLATEMODEL_H_
#define GGAFDX9PLATEMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9PlateActor�p���f���N���X.
 */
class GgafDx9PlateModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;
    friend class GgafDx9PlateActor;
protected:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_platemodel_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9PlateModel(char* prm_platemodel_name);

public:

    /** VERTEX��FVF */
    static DWORD FVF;

    /** �e�N�X�`��(�A�j���[�V�����p�^�[���j */
    GgafDx9TextureConnection* _pTexture;

    /** �A�j���[�V���[���̂��߂̃e�N�X�`���̍��W�̔z��i�v�f���̓A�j���[�V�������j */
    GgafDx9RectUV* _paRectUV;

    /** �O��\����UV */
    GgafDx9RectUV* _pRectUV_drawlast;

    /** �S�A�j���p�^�[���� */
    int _iPatternNo_Max;
    float _fSize_PlateModelWidth;
    float _fSize_PlateModelHeight;
    int _iRowNum_TextureSplit;
    int _iColNum_TextureSplit;

    /**
     * GgafDx9PlateModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDx9PlateActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9PlateModelManager�ł���<BR>
     */
    virtual ~GgafDx9PlateModel(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9PLATEMODEL_H_*/
