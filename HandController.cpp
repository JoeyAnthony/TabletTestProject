#include "stdafx.h"
#include "HandController.h"
#include <glm\gtc\matrix_transform.hpp>
#include <VrLib\math\Ray.h>
#include <glm\gtx\quaternion.hpp>



using namespace vrlib;
using namespace vrlib::tien;

void HandController::update(float elapsedTime, Scene & scene)
{

#ifdef WIN32

	auto& pos = node->transform->getGlobalPosition();
	if (GetAsyncKeyState('I'))
		node->transform->setGlobalPosition(pos + glm::vec3(0, 0, -1) * elapsedTime);
	if (GetAsyncKeyState('K'))
		node->transform->setGlobalPosition(pos + glm::vec3(0, 0, 1) * elapsedTime);
	if (GetAsyncKeyState('L'))
		node->transform->setGlobalPosition(pos + glm::vec3(1, 0, 0) * elapsedTime);
	if (GetAsyncKeyState('J'))
		node->transform->setGlobalPosition(pos + glm::vec3(-1, 0, 0) * elapsedTime);
	if (GetAsyncKeyState('U'))
		node->transform->setGlobalPosition(pos + glm::vec3(0, 1, 0) * elapsedTime);
	if (GetAsyncKeyState('N'))
		node->transform->setGlobalPosition(pos + glm::vec3(0, -1, 0) * elapsedTime);

	
#endif		

	//node->transform->transform = glm::rotate(node->transform->transform, 3.f * elapsedTime, glm::vec3(0, 1, 0));
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

	glm::vec3 rayOrigin{node->transform->transform * glm::vec4(0, 0, 0, 1)};
	glm::mat4 rotmat = glm::rotate(node->transform->transform, glm::radians(-60.f), glm::vec3(1, 0, 0));
	glm::vec3 rayFront{rotmat * glm::vec4(0, 0, -1, 1)};
	glm::vec3 rayDir = glm::vec3(rayFront - rayOrigin);
	//glm::vec3 rayDir = glm::vec3(glm::vec4(glm::normalize(rayFront - rayOrigin), 1.f) * glm::rotate(glm::mat4(), -45.f, glm::vec3(1, 0, 0)));


	glm::vec3 rayTarget{ rayOrigin + rayDir * 20.f };
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3fv(glm::value_ptr(rayOrigin));
	glVertex3fv(glm::value_ptr(rayTarget));
	glEnd();
}

void HandController::drawDeferredPass() {
	//glm::vec4 dir{ 0,0,-1,0 };
	//dir = glm::rotate(node->transform->rotation, dir);

	//glm::vec3 trueDir{ dir };
	//glColor3f(1.f/244, 1.f/66, 1.f/223);
	//glBegin(GL_LINES);
	//auto& pos = node->transform->position;
	//glVertex3f(pos.x, pos.y, pos.z);
	//pos += trueDir * 100.f;
	//glVertex3f(pos.x, pos.y, pos.z);
	//glEnd();
	//use classic opengl to render the pointer line from the hands if it's teleporting

}


HandController::HandController(vrlib::Vive::Controller c)
{
	controller = c;

		

}


HandController::~HandController() 
{
}
