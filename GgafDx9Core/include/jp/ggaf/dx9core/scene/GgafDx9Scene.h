#ifndef GGAFDX9SCENE_H_
#define GGAFDX9SCENE_H_
namespace GgafDx9Core {

/**
 * GgafDx9Core名前空間、基底シーンクラス.
 * GgafMainScene を継承しただけです。<BR>
 * GgafDx9Core名前空間内では、このクラスを基底シーンとします。<BR>
 */
class GgafDx9Scene : public GgafCore::GgafMainScene {

public:
	GgafDx9Scene(char* prm_name);

	virtual ~GgafDx9Scene();
};


}
#endif /*GGAFDX9SCENE_H_*/
