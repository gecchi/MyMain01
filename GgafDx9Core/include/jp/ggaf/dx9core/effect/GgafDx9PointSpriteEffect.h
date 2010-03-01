#ifndef GGAFDX9POINTSPRITEEFFECT_H_
#define GGAFDX9POINTSPRITEEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9PointSprite�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDx9PointSpriteEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hPowerBlink;
    D3DXHANDLE _hBlinkThreshold;
    D3DXHANDLE _hMatView;
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hOffsetU;
    D3DXHANDLE _hOffsetV;
    D3DXHANDLE _hAlpha;
    D3DXHANDLE _hDist_VpPlnFront;
public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDx9PointSpriteEffect(char* prm_effect_name);


    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9PointSpriteEffectManager�ł���<BR>
     */
    virtual ~GgafDx9PointSpriteEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9POINTSPRITEEFFECT_H_*/
