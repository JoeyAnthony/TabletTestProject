#pragma once

#include "TabletGraphics.h"

#include "stdafx.h"
#include <VrLib\tien\Tien.h>
#include <VrLib\tien\components\MeshRenderer.h>
#include <VrLib\Device.h>
#include <VrLib\Texture.h>
#include <VrLib\gl\FBO.h>
#include <memory>
#include <initializer_list>

class Tablet : public vrlib::tien::Component, public vrlib::tien::components::MeshRenderer::Mesh {
public: // This class is public to allow easy acces from TabletGraphics
	// We use this class to convert our FBO to a texture for the mesh
	// @NOTE: this class originated in NetworkEngine/PanelComponent.h/PanelComponent
	// @TODO: maybe put this class in TIEN?
	class FboToTexture : public vrlib::Texture
	{
	public:
		vrlib::gl::FBO* fbo;
		FboToTexture(vrlib::gl::FBO* fbo) : fbo(fbo), vrlib::Texture(nullptr)
		{
		}

		inline void bind() override
		{
			fbo->use();
		}

	};
private:
	// Resolution related variables
	// m_size gives us the size of the x-axis and we use m_withToHeightRato -- wich is calculated by res.y/res.x -- to determine the size of the y-axis
	const glm::ivec2 m_resolution;
	const float m_size;
	const float m_withToHeightRatio;
	
	// FBO related variables
	vrlib::gl::FBO m_fbo;
	FboToTexture m_fboTexture;

	// Constant matrixes to handle conversions
	const glm::mat4 m_pixelToTexCoordMat;
	const glm::mat4 m_planePosToPixelCoordMat;
	glm::mat4 m_activeTransfrom;

	// The input devices
	const vrlib::PositionalDevice& m_pointer;
	const vrlib::DigitalDevice& m_trigger;

	// The runtime input values
	glm::ivec2 m_screenPos;
	bool m_screenPosInBounds;
	TabletGraphicsObject* m_mouseDownObject = nullptr;

	struct updateResult {
		bool tookHover;
		bool tookClick;
	};

	void updateInput();
	updateResult updateGraphicsObject(TabletGraphicsObject* obj, float deltaMs, glm::ivec2 mousePos, bool inBounds, bool active, bool mouseDown);
	void updateApps(float deltaMs);
	void drawGraphicsObject(TabletGraphicsObject* obj, glm::mat4 transform);
	void updateScreen();
	void clear(glm::vec4 clearColor = {0,0,0,1});

	// The apps that run on the tablet
	std::vector<TabletApp*> apps;
	TabletApp* activeApp;
public:

	Tablet(glm::ivec2 resolution, float size, const vrlib::PositionalDevice& pointer, const vrlib::DigitalDevice& trigger, std::initializer_list<TabletApp*> apps);

	void update(float elapsedTime, vrlib::tien::Scene& scene) override;
	void postUpdate(vrlib::tien::Scene& scene) override;

	glm::mat4 getPixelToTexCoordMat() { return m_pixelToTexCoordMat; }
	glm::mat4 getActiveTransform() { return m_activeTransfrom; }

	template <typename A>
	A * getApp() {
		for (auto& c : apps)
		{
			A* r = dynamic_cast<A*>(&c);
			if (r)
				return r;
		}
		return nullptr;
	}

	void setActiveApp(TabletApp* app);
};