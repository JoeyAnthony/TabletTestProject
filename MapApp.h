#include "TabletGraphics.h"

#include <VrLib\tien\Node.h>

class MainApp;

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

	TabletGraphicsComonents::Square* background;
	MapScroll* baseMap;
	TabletGraphicsComonents::Square* cursor;
	TabletGraphicsComonents::Button* mainMenuButton;

	vrlib::tien::Node* node;
	MainApp* mainApp;
public:

	MapApp(vrlib::tien::Node* node);

	void initalize() override;
	bool linkToApps() override;
	void update(float delatMS) override;
};