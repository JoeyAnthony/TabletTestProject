#pragma once
#include <VrLib\HtcVive.h>
#include <VrLib\tien\Tien.h>
#include <VrLib\tien\Scene.h>
#include <VrLib\tien\Component.h>

class HandController : public vrlib::tien::components::Renderable
{

private:
	class HandRenderContext : public vrlib::tien::components::Renderable::RenderContext, public vrlib::Singleton<HandRenderContext>
	{
	public:
		enum class RenderUniform
		{
			modelMatrix,
			projectionMatrix,
			viewMatrix,
			normalMatrix,
			s_texture,
			s_normalmap,
			s_specularmap,
			diffuseColor,
			textureFactor,
			boneMatrices,
			shinyness,
		};

		void init() override;
		vrlib::gl::Shader<RenderUniform>* renderShader;
		void frameSetup(const glm::mat4 & projectionMatrix, const glm::mat4 & viewMatrix) override;
	};

	vrlib::Vive::Controller controller;
	float debugspeed = 0.3f;

public:
	void initHand();
	void update(float elapsedTime, vrlib::tien::Scene& scene) override;
	void postUpdate(vrlib::tien::Scene& scene) override;

	void drawRay(glm::mat4 view, glm::mat4 proj);

	void drawDeferredPass() override {};
	void drawForwardPass() override;
	void drawShadowMap() override {};

	HandController(vrlib::Vive::Controller c);
	~HandController();
};

