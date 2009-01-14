#ifndef GGAFDX9MAINACTOR_H_
#define GGAFDX9MAINACTOR_H_


class GgafDx9MainActor : public GgafDx9MeshActor,
                         public GgafDx9DynaMeshActor,
                         public GgafDx9SpriteActor,
                         public GgafDx9CubeActor,
                         public GgafDx9SquareActor {

public:
	DWORD _dwFrameOffset;

//	StgChecker* _pChecker;

	GgafDx9MainActor(int prm_type, string prm_name, string prm_model, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);


	virtual void initialize() {};

	virtual void processBehavior() {};

	virtual void processJudgement() {};

	virtual void processDrawPrior() {
		GgafDx9UntransformedActor::processDrawPrior();
	};

	virtual void processDrawMain() {
		switch (_type) {
			case ACTORTYPE_MESH:
				GgafDx9MeshActor::processDrawMain();
				break;
			case ACTORTYPE_DYNAMESH:
				GgafDx9DynaMeshActor::processDrawMain();
				break;
			case ACTORTYPE_SPRITE:
				GgafDx9SpriteActor::processDrawMain();
				break;
			case ACTORTYPE_CUBE:
				GgafDx9CubeActor::processDrawMain();
				break;
			case ACTORTYPE_SQUARE:
				GgafDx9SquareActor::processDrawMain();
				break;
			default:
				_TRACE_("GgafDx9MainActor::processDrawMain 不明なタイプ _type="<<_type);
				break;
		}
	};


	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual void processOnHit(GgafActor* prm_pActor_Opponent) {};

	virtual ~GgafDx9MainActor();
};


#endif /*GGAFDX9MAINACTOR_H_*/
