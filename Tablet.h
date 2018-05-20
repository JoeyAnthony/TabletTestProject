#pragma once

#include "stdafx.h"
#include <VrLib\tien\Tien.h>
#include <VrLib\tien\components\MeshRenderer.h>
#include <VrLib\Device.h>
#include <VrLib\Texture.h>
#include <VrLib\gl\FBO.h>
#include <memory>

class Tablet : public vrlib::tien::Component, public vrlib::tien::components::MeshRenderer::Mesh {
	
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

	// The input devices
	const vrlib::PositionalDevice& m_pointer;

	// The runtime input values
	glm::ivec2 m_screenPos;
	bool m_screenPosInBounds;

	void updateInput();
	void updateScreen();
	void clear(glm::vec4 clearColor = {0,0,0,1});

public:

	Tablet(glm::ivec2 resolution, float size, const vrlib::PositionalDevice& pointer);

	void update(float elapsedTime, vrlib::tien::Scene& scene) override;
	void postUpdate(vrlib::tien::Scene& scene) override;
};