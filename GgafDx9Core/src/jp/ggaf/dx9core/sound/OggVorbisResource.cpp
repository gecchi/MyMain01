#include "stdafx.h"
OggVorbisResource::OggVorbisResource() : isReady_(false) {
		memset(&oggVorbisFile_, 0, sizeof(OggVorbis_File));
}

void OggVorbisResource::clear() {
	memset(&oggVorbisFile_, 0, sizeof(OggVorbis_File));
	isReady_ = false;
}
