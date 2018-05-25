#include "stdafx.h"
#include "HandController.h"
#include <glm\gtc\matrix_transform.hpp>
#include <VrLib\math\Ray.h>
#include <glm\gtx\quaternion.hpp>



using namespace vrlib;
using namespace vrlib::tien;

void HandController::update(float elapsedTime, Scene & scene)
{


}


void HandController::postUpdate(Scene & scene)
{
}

void HandController::drawRay(glm::mat4 view, glm::mat4 proj)
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(proj));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(view));
	glUseProgram(0);
	glDisable(GL_TEXTURE_2D);
	glColor4f(1, 0, 0, 1);
	glDisable(GL_BLEND);
	glLineWidth(10.0f);

	glm::vec3 rayOrigin{ node->transform->transform * glm::vec4(0, 0, 0, 1) };
	//glm::mat4 rotmat = glm::rotate(node->transform->transform, glm::radians(-60.f), glm::vec3(1, 0, 0));
	//glm::vec3 rayFront{rotmat * glm::vec4(0, 0, -1, 1)};
	glm::vec3 rayFront{ node->transform->transform * glm::vec4(0, 0, -1, 1) };
	glm::vec3 rayDir = glm::vec3(rayFront - rayOrigin);
	//glm::vec3 rayDir = glm::vec3(glm::vec4(glm::normalize(rayFront - rayOrigin), 1.f) * glm::rotate(glm::mat4(), -45.f, glm::vec3(1, 0, 0)));


	glm::vec3 rayTarget{ rayOrigin + rayDir * 20.f };
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3fv(glm::value_ptr(rayOrigin));
	glVertex3fv(glm::value_ptr(rayTarget));
	glEnd();
}

void HandController::drawForwardPass() {
	HandRenderContext* context = dynamic_cast<HandRenderContext*>(renderContextForward);
	
}

HandController::HandController(vrlib::Vive::Controller c)
{
	controller = c;
	renderContextForward = HandRenderContext::getInstance();
}


HandController::~HandController() 
{
}

void HandController::HandRenderContext::init()
{
}

void HandController::HandRenderContext::frameSetup(const glm::mat4 & projectionMatrix, const glm::mat4 & viewMatrix)
{
	//renderShader->use();
	//renderShader->setUniform(RenderUniform::projectionMatrix, projectionMatrix);
	//renderShader->setUniform(RenderUniform::viewMatrix, viewMatrix);
	//renderShader->setUniform(RenderUniform::diffuseColor, glm::vec4(1, 1, 1, 1));
	//renderShader->setUniform(RenderUniform::textureFactor, 1.0f);
}


