#ifndef GGAFDXCORE_GGAFDXEFFECT_H_
#define GGAFDXCORE_GGAFDXEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif
#include <string>

#define Obj_GgafDxEffect                    (0x2U)            //0b 00000000 00000000 00000000 00000010
#define Obj_GgafDxMeshEffect                (0x4U)            //0b 00000000 00000000 00000000 00000100
#define Obj_GgafDxD3DXAniMeshEffect         (0x8U)            //0b 00000000 00000000 00000000 00001000
#define Obj_GgafDxMeshSetEffect             (0x10U)           //0b 00000000 00000000 00000000 00010000
#define Obj_GgafDxMassMeshEffect            (0x20U)           //0b 00000000 00000000 00000000 00100000
#define Obj_GgafDxMorphMeshEffect           (0x40U)           //0b 00000000 00000000 00000000 01000000
#define Obj_GgafDxCubeMapMeshEffect         (0x80U)           //0b 00000000 00000000 00000000 10000000
#define Obj_GgafDxCubeMapMeshSetEffect      (0x100U)          //0b 00000000 00000000 00000001 00000000
#define Obj_GgafDxCubeMapMorphMeshEffect    (0x200U)          //0b 00000000 00000000 00000010 00000000
#define Obj_GgafDxWorldBoundEffect          (0x400U)          //0b 00000000 00000000 00000100 00000000
#define Obj_GgafDxSpriteEffect              (0x800U)          //0b 00000000 00000000 00001000 00000000
#define Obj_GgafDxSpriteSetEffect           (0x1000U)         //0b 00000000 00000000 00010000 00000000
#define Obj_GgafDxBoardEffect               (0x2000U)         //0b 00000000 00000000 00100000 00000000
#define Obj_GgafDxBoardSetEffect            (0x4000U)         //0b 00000000 00000000 01000000 00000000
#define Obj_GgafDxMassEffect                (0x8000U)         //0b 00000000 00000000 10000000 00000000
#define Obj_GgafDxMassBoardEffect           (0x10000U)        //0b 00000000 00000001 00000000 00000000
#define Obj_GgafDxPointSpriteEffect         (0x20000U)        //0b 00000000 00000010 00000000 00000000
#define Obj_GgafDxMassSpriteEffect          (0x40000U)        //0b 00000000 00000100 00000000 00000000
#define Obj_GgafDxMassMorphMeshEffect       (0x80000U)        //0b 00000000 00001000 00000000 00000000
#define Obj_GgafDxMassPointSpriteEffect     (0x100000U)       //0b 00000000 00010000 00000000 00000000
#define Obj_GgafDxPointSpriteSetEffect      (0x200000U)       //0b 00000000 00100000 00000000 00000000
#define Obj_GgafDxFramedBoardEffect       (0x400000U)       //0b 00000000 01000000 00000000 00000000

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

//protected:
//    static D3DXMACRO _aD3DXMacro_Defines[3];

public:
    D3DXHANDLE _h_alpha_master;
    /** [r]エフェクト定義の識別名。(50文字まで) */
    char* _effect_name;
    /** [r]エフェクト */
    ID3DXEffect* _pID3DXEffect;
    /** [r]エフェクトインスタンス種類 */
    uint32_t _obj_effect;
#ifdef MY_DEBUG
    bool _begin;
#endif

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト定義の識別名。".fx"を追加するとエフェクトファイル名になる。
     */
    explicit GgafDxEffect(const char* prm_effect_name);

    char* getName() {
        return _effect_name;
    }

    /**
     * 1フレームに1回実行するだけで良いエフェクトパラメータを
     * このメソッドに記述する。
     */
    virtual void setParamPerFrame() = 0;

    void setAlphaMaster(float prm_master_alpha);

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxEffectManagerである<BR>
     */
    virtual ~GgafDxEffect();
};

}
#endif /*GGAFDXCORE_GGAFDXEFFECT_H_*/
