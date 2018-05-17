#include "stdafx.h"
#include "Tablet.h"

#include <VrLib\tien\components\TransformAttach.h>
#include <glm\gtx\intersect.hpp>

using namespace vrlib;
using namespace vrlib::tien;
using namespace glm;
using vrlib::gl::FBO;
using std::make_unique;

Tablet::Tablet(const PositionalDevice& pointer) : m_pointer(pointer), fbo(resx, resy), fboTexture(&fbo) {	
	material.texture = &fboTexture;
	material.normalmap = nullptr;

	clear({ 1,0,0,1 });

	vrlib::gl::VertexP3N2B2T2T2 v;
	vrlib::gl::setN3(v, glm::vec3(0, 0, 1));
	vrlib::gl::setTan3(v, glm::vec3(1, 0, 0));
	vrlib::gl::setBiTan3(v, glm::vec3(0, 1, 0));

	vec2 sizevec{ size, size * withToHeightRatio };


	vrlib::gl::setP3(v, glm::vec3(-sizevec.x / 2.0f, -sizevec.y / 2.0f, 0));			vrlib::gl::setT2(v, glm::vec2(0, 0));			vertices.push_back(v);
	vrlib::gl::setP3(v, glm::vec3(sizevec.x / 2.0f, -sizevec.y / 2.0f, 0));			vrlib::gl::setT2(v, glm::vec2(1, 0));			vertices.push_back(v);
	vrlib::gl::setP3(v, glm::vec3(sizevec.x / 2.0f, sizevec.y / 2.0f, 0));			vrlib::gl::setT2(v, glm::vec2(1, 1));			vertices.push_back(v);
	vrlib::gl::setP3(v, glm::vec3(-sizevec.x / 2.0f, sizevec.y / 2.0f, 0));			vrlib::gl::setT2(v, glm::vec2(0, 1));			vertices.push_back(v);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	pixelToTexCoordMat = { (1.f / resx) * 2,0,0,0,
							0,(1.f / resy) * 2,0,0,
							0,0,1,0,
							-1,-1,0,1 };
}

void Tablet::clear(vec4 clearColor) {
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, fbo.getWidth(), fbo.getHeight());
	fbo.bind();
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
	fbo.unbind();
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}

void Tablet::update(float elapsedTime, Scene& scene) {
	m_screenPos = { 0,0 };
	m_screenPosInBounds = false;
	if (node == nullptr) return;

	// Calculate screen pos
	const mat4 toTabletSpaceMat = inverse(node->transform->transform);
	const vec3 pointerPos = vec3(toTabletSpaceMat * (m_pointer.getData() * vec4(0, 0, 0, 1)));
	const vec3 pointerFront = vec3(toTabletSpaceMat * (m_pointer.getData() * vec4(0, 0, -1, 1)));
	const vec3 pointerDir = pointerPos - pointerFront;

	auto wp_pointerpos =  m_pointer.getData() *  vec4(0, 0, 0, 1);
	auto wp_pointerfront = m_pointer.getData() * vec4(0, 0, -1, 1);

	//std::cout << "wp_pointerpos (" << wp_pointerpos.x << "," << wp_pointerpos.y << "," << wp_pointerpos.z << ")"  << std::endl;
	//std::cout << "wp_pointerfront (" << wp_pointerfront.x << "," << wp_pointerfront.y << "," << wp_pointerfront.z << ")" << std::endl;
	std::cout << "pointerPos (" << pointerPos.x << "," << pointerPos.y << "," << pointerPos.z << ")" << std::endl;
	//std::cout << "pointerFront (" << pointerFront.x << "," << pointerFront.y << "," << pointerFront.z << ")" << std::endl;
	//std::cout << "dirmag " << length(pointerDir) << std::endl;
	std::cout << "pointerDir (" << pointerDir.x << "," << pointerDir.y << "," << pointerDir.z << ")" << std::endl;


	

	

	float intersectionDistance;
	bool intersectSucces = intersectRayPlane(pointerPos, pointerDir, {}, { 0,0,-1 }, intersectionDistance);
	intersectionDistance *= -1;
	if (intersectSucces == false) return;
	std::cout << "intersection distance" << intersectionDistance << std::endl;

	auto intercectionpos = pointerPos + -intersectionDistance * pointerDir;

	mat4 planePosToPixelCoordMat{resx/size,0,0,0,
								 0,(resy/ withToHeightRatio)/size,0,0,
								 0,0,0,0,
								 resx/2.f,resy/2.f,0,0 };

	std::cout << "interctpoint (" << intercectionpos.x << "," << intercectionpos.y << "," << intercectionpos.z << ")" << std::endl;

	intercectionpos = vec3(planePosToPixelCoordMat * vec4(intercectionpos, 1));

	std::cout << "interctpoint (" << intercectionpos.x << "," << intercectionpos.y << "," << intercectionpos.z << ")" << std::endl;

	m_screenPos = min(max(vec2(intercectionpos), { 0,0 }), { resx,resy });
	m_screenPosInBounds = vec2(intercectionpos) == m_screenPos;
	std::cout << "pos in bounds " << m_screenPosInBounds;

	std::cout << std::endl;

	clear();

	// DRAW 
	{
		int viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glViewport(0, 0, fbo.getWidth(), fbo.getHeight());
		fbo.bind();

		

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(value_ptr(mat4()));
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(value_ptr(pixelToTexCoordMat));
		glUseProgram(0);
		glDisable(GL_TEXTURE_2D);
		glColor4f(0, 0, 0, 1);
		glLineWidth(10.f);
		glBegin(GL_LINES);

		glColor3f(1, 0, 0);
		glVertex3fv(value_ptr(vec3(0, 0, 0)));
		glVertex3fv(value_ptr(vec3(m_screenPos, 0)));

		glColor3f(0, 1, 0);
		glVertex3fv(value_ptr(vec3(resx, 0, 0)));
		glVertex3fv(value_ptr(vec3(m_screenPos, 0)));

		glColor3f(0, 0, 1);
		glVertex3fv(value_ptr(vec3(0, resy, 0)));
		glVertex3fv(value_ptr(vec3(m_screenPos, 0)));

		glColor3f(1, 1, 1);
		glVertex3fv(value_ptr(vec3(resx, resy, 0)));
		glVertex3fv(value_ptr(vec3(m_screenPos, 0)));

		glEnd();

		fbo.unbind();
		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	}


		//covert pointer to local space
		//do a vector plane intersect
		//update screen pos

	//Handle App
}

void Tablet::postUpdate(Scene& scene) {
	
}
