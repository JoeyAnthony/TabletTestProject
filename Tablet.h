#pragma once

#include "stdafx.h"
#include <VrLib\tien\Tien.h>
#include <VrLib\tien\components\MeshRenderer.h>
#include <VrLib\Device.h>
#include <VrLib\Texture.h>
#include <VrLib\gl\FBO.h>
#include <memory>
#include "CameraApp.h"
//#include "../../Applications/chemicalstorage/report.h"

class Tablet : public vrlib::tien::Component, public vrlib::tien::components::MeshRenderer::Mesh {
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

	CameraApp* camapp;
	vrlib::gl::FBO* fbo;
	FboToTexture fboTexture;

	glm::mat4 pixelToTexCoordMat;

	void clear(glm::vec4 clearColor = {0,0,0,1});
public:
	static constexpr int resx = 600, resy = 800;
	static constexpr float widthToHeightRatio = ((float)resy) / resx;
	static constexpr float size = 0.25f;

	Tablet(const vrlib::PositionalDevice& pointer, CameraApp* capp);

	void update(float elapsedTime, vrlib::tien::Scene& scene) override;
	void postUpdate(vrlib::tien::Scene& scene) override;

private:
	const vrlib::PositionalDevice& m_pointer;
	
	glm::vec2 m_screenPos;
	bool m_screenPosInBounds;
};