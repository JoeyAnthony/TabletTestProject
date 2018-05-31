#include "stdafx.h"
#include "VisibilityTester.h"
#include <VrLib/gl/Vertex.h>
#include <VrLib/Model.h>

using namespace vrlib::tien;
using namespace glm;

bool VisibilityTester::isVisible(float & onScreenValue)
{
	//max amount of pixels vs zero
	return false;
}

void VisibilityTester::drawForwardPass()
{

}

void VisibilityTester::OcclusionDraw(glm::mat4 view, glm::mat4 proj)
{
	std::cout<<"pixels: " << query.getResult() << std::endl;
	
	//render quad
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(proj));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(view * node->transform->transform));
	glUseProgram(0);
	//glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	query.beginQuery();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.4f, 0.4f);
	//front and back
	glVertex3fv(glm::value_ptr(vec3(minbounds.x, minbounds.y, minbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(maxbounds.x, minbounds.y, minbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(maxbounds.x, maxbounds.y, minbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(minbounds.x, maxbounds.y, minbounds.z)));

	glVertex3fv(glm::value_ptr(vec3(minbounds.x, minbounds.y, maxbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(maxbounds.x, minbounds.y, maxbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(maxbounds.x, maxbounds.y, maxbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(minbounds.x, maxbounds.y, maxbounds.z)));

	//right and left
	glVertex3fv(glm::value_ptr(vec3(minbounds.x, minbounds.y, minbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(minbounds.x, maxbounds.y, minbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(minbounds.x, maxbounds.y, maxbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(minbounds.x, minbounds.y, maxbounds.z)));

	glVertex3fv(glm::value_ptr(vec3(maxbounds.x, minbounds.y, minbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(maxbounds.x, maxbounds.y, minbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(maxbounds.x, maxbounds.y, maxbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(maxbounds.x, minbounds.y, maxbounds.z)));

	//up and down
	glVertex3fv(glm::value_ptr(vec3(minbounds.x, minbounds.y, minbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(maxbounds.x, minbounds.y, minbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(maxbounds.x, minbounds.y, maxbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(minbounds.x, minbounds.y, maxbounds.z)));

	glVertex3fv(glm::value_ptr(vec3(minbounds.x, maxbounds.y, minbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(maxbounds.x, maxbounds.y, minbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(maxbounds.x, maxbounds.y, maxbounds.z)));
	glVertex3fv(glm::value_ptr(vec3(minbounds.x, maxbounds.y, maxbounds.z)));
	glEnd();
	query.endQuery();
}

/*
* Treshhold is a value between 1 and 0 where 1 means that all pixels have to be on screen
*/
VisibilityTester::VisibilityTester(float tresh, components::ModelRenderer* model) : treshold(tresh), modelRenderer(model)
{
	minbounds = model->model->aabb.bounds[0];
	maxbounds = model->model->aabb.bounds[1];

	minbounds -= 0.01;
	maxbounds += 0.01;
}

VisibilityTester::VisibilityTester(float tresh, vrlib::tien::components::ModelRenderer* model, CameraApp* camapp) : VisibilityTester(tresh, model)
{
	camapp->addOcclusionObject(this);
}

VisibilityTester::~VisibilityTester()
{
	//delete query and mesh
}
