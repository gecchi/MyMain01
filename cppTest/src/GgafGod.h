#ifndef GGAFGOD_H_
#define GGAFGOD_H_
namespace GgafCore {


class GgafGod : public GgafObject {

public:


	/**
	 * コンストラクタ.
	 * 別スレッドで工場を稼動させます。
	 */
	GgafGod();

	virtual ~GgafGod();
};


}
#endif /*GGAFGOD_H_*/
