﻿#ifndef GGAFDX9MESHSETEFFECT_H_
#define GGAFDX9MESHSETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9MeshSet用エフェクトクラス .
 * @version 1.00
 * @since 2009/06/15
 * @author Masatoshi Tsuge
 */
class GgafDx9MeshSetEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hPowerBlink;
    D3DXHANDLE _hBlinkThreshold;
    D3DXHANDLE _hMatView;
    //D3DXHANDLE _hMatWorld;
    D3DXHANDLE _ahMatWorld[16];
    D3DXHANDLE _ahMaterialDiffuse[16];
    D3DXHANDLE _ahOffsetU[16];
    D3DXHANDLE _ahOffsetV[16];
    D3DXHANDLE _h_nVertexs;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDx9MeshSetEffect(char* prm_effect_name);


    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9MeshSetEffectManagerである<BR>
     */
    virtual ~GgafDx9MeshSetEffect(); //デストラクタ

};

}
#endif /*GGAFDX9MESHSETEFFECT_H_*/
