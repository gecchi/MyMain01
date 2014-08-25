#ifndef GGAFDXCORE_GGAFDXMORPHER_H_
#define GGAFDXCORE_GGAFDXMORPHER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafValueTransitioner.hpp"

namespace GgafDxCore {

/**
 * モーフィング支援クラス .
 * GgafDxMorphMeshActor のメンバの<BR>
 * 重み _weight[] <BR>
 * を簡単に操作するために設計。<BR>
 * 尚 _weight[] は、[0]は未使用、[1]～[n]がモーフターゲット1～nの重み <BR>
 * @version 1.00
 * @since 2009/05/11
 * @author Masatoshi Tsuge
 */
class GgafDxMorpher : public GgafCore::GgafValueTransitioner<float, (MAX_MORPH_TARGET+1) > {

private:
    /** [r]モーファーの助手A */
    GgafDxMorpherAssistantA* _pAsstA;

public:
    /** [r]対象アクター */
    GgafDxMorphMeshActor* const _pActor;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_pActor 適用Actor
     */
    explicit GgafDxMorpher(GgafDxMorphMeshActor* prm_pActor);

    /**
     * モーファーの助手A(なめらかモーフ)を取得 .
     * @return モーファーの助手A
     */
    GgafDxMorpherAssistantA* asst();

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    void behave(int s = 1, int n = MAX_MORPH_TARGET) override;

    virtual ~GgafDxMorpher();
};

}
#endif /*GGAFDXCORE_GGAFDXMORPHER_H_*/

