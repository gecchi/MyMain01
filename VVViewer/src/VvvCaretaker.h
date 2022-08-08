#ifndef VVVCARETAKER_H_
#define VVVCARETAKER_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

#include "scene/VvvSpacetime.h"

#undef pCARETAKER
#define pCARETAKER ((VVViewer::VvvCaretaker*)GgafCore::Caretaker::ask())

namespace VVViewer {

/**
 * VVViewer管理者 .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCaretaker : public GgafLib::DefaultCaretaker {

public:
    static bool is_wm_dropfiles_;
    static char dropfiles_[2048];

public:
    /**
     * コンストラクタ .
     */
    VvvCaretaker();

    /**
     * この世生成方法の実装 .
     * 管理者クラスを作成するには、「この世」の生成方法を実装する必要があります。
     * @return 生成した「この世」
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual VvvSpacetime* getSpacetime() override {  //共変の戻り値
        return (VvvSpacetime*)_pSpacetime;
    }

    virtual ~VvvCaretaker();
};

}
#endif /*VVVCARETAKER_H_*/
