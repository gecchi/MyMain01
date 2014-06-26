#ifndef GGAFDXCORE_GGAFDXEFFECT_H_
#define GGAFDXCORE_GGAFDXEFFECT_H_
#include "jp/ggaf/core/GgafObject.h"

#include <d3dx9.h>
#include <string>
#ifdef __GNUG__
    #undef __null
    #undef __in
    #undef __out
#endif
namespace GgafDxCore {

/**
 * エフェクト基底クラス.
 * キャラ(アクター)のエフェクトを保持するクラスです。<BR>
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDxEffect : public GgafCore::GgafObject {
    friend class GgafDxEffectManager;

    static std::string getEffectFileName(std::string prm_file);

protected:
    static D3DXMACRO _aD3DXMacro_Defines[3];

public:
    D3DXHANDLE _h_alpha_master;
    /** [r]エフェクト定義の識別名。(50文字まで) */
    char* _effect_name;
    /** [r]エフェクト */
    ID3DXEffect* _pID3DXEffect;
#ifdef MY_DEBUG
    bool _begin;
#endif

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト定義の識別名。".fx"を追加するとエフェクトファイル名になる。
     */
    GgafDxEffect(char* prm_effect_name);

    char* getName() {
        return _effect_name;
    }

    /**
     * 1フレームに1回実行するだけで良いエフェクトパラメータを
     * このメソッドに記述する。
     */
    virtual void setParamPerFrame() = 0;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxEffectManagerである<BR>
     */
    virtual ~GgafDxEffect();
};

}
#endif /*GGAFDXCORE_GGAFDXEFFECT_H_*/
