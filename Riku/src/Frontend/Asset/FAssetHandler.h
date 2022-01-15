//
// Created by kamil-hp on 27.11.2021.
//

#ifndef RIKU_FASSETHANDLER_H
#define RIKU_FASSETHANDLER_H

#include "FAsset.h"
#include "../../GameLogic/Assets/AssetHandler.h"
#include "../../MiniGame/MiniGameAssets.h"

namespace front {
	class AssetHandler {
		std::map<std::string, Asset> assets;
		const logic::AssetHandler& handler, miniHandler;
        void loadFile(const std::string& path);
	public:
		explicit AssetHandler(const logic::AssetHandler& assetHandler, const logic::AssetHandler& miniHandler);
		void loadFiles();
		const Asset& getAsset(const std::string& parentPath) const;
		bool tryDraw(const std::string& key, const Shader &shader, Transform transform) const;
        const std::map<std::string, Asset>& getMap() const;
	};
}


#endif //RIKU_FASSETHANDLER_H
