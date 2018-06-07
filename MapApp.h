#include "TabletGraphics.h"

class MapApp : public TabletApp {
	class MapScroll : public TabletGraphicsObject {
		vrlib::Texture* texture;
		float wordToMapScale;
		float mapZoom;
		glm::vec2 centerWorld;
		glm::vec2 worldPos;
	public:
		MapScroll(std::string map, float wordToMapScale, glm::vec2 centerWorld, TabletGraphicsObject* parent);

		void draw(TabletGraphicsRenderInfo renderInfo) override;
		void setWorldPos(glm::vec2 worldPos);
		void setMapZoom(float mapZoom);
	};

	MapScroll* baseMap;
public:

	MapApp();

	void initalize() override;
	void update(float delatMS) override;
};