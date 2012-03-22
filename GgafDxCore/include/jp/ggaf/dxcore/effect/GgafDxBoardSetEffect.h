#ifndef GGAFDXBOARDSETEFFECT_H_
#define GGAFDXBOARDSETEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxBoardSet用モデルクラス.
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDxBoardSetEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _ah_offset_u[28];
    D3DXHANDLE _ah_offset_v[28];
    D3DXHANDLE _ah_transformed_X[28];
    D3DXHANDLE _ah_transformed_Y[28];
    D3DXHANDLE _ah_alpha[28];
    D3DXHANDLE _ah_depth_Z[28];

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxBoardSetEffect(char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxEffectManagerである<BR>
     */
    virtual ~GgafDxBoardSetEffect(); //デストラクタ

};

}
#endif /*GGAFDXBOARDSETEFFECT_H_*/
