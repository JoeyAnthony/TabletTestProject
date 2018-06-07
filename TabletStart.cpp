#include "stdafx.h"
#include "TabletStart.h"
#include <VrLib\Log.h>
#include <VrLib\json.hpp>
#include <fstream>
#include <VrLib\Device.h>

#include <VrLib\tien\components\TransformAttach.h>
#include <VrLib\tien\components\ModelRenderer.h>

#include "VisibilityTester.h"

#include "Tablet.h"
#include "MainApp.h"
#include "CameraApp.h"


using vrlib::logger;
using namespace vrlib::tien;

void TabletStart::init()
{
	logger << "Initialized" << logger.newline;
	vive.init();
	Engine.init();

	loadScene();

	Engine.start();
}

void TabletStart::preFrame(double frameTime, double totalTime)
{
	Engine.update((float)frameTime / 1000.0f);
}

void TabletStart::latePreFrame()
{

}

void TabletStart::draw(const glm::mat4 & projectionMatrix, const glm::mat4 & modelViewMatrix)
{
	Engine.render(projectionMatrix, modelViewMatrix);
	hand->drawRay(modelViewMatrix, projectionMatrix);
}

void TabletStart::loadScene()
{
	Engine.scene.reset();

	std::ifstream str = std::ifstream("../Development/Applications/TabletTestProject/data/TabletTestProject/Scenes/TabletWorld.json");
	json scene = json::parse(str);
	Engine.scene.fromJson(scene["scene"], scene, [](auto) {return nullptr; });

	hand = new HandController(vive.controllers[1]);

	Node* rightHand = new Node("RightHand", &Engine.scene);
	rightHand->addComponent(new components::Transform(glm::vec3(2, 0, 0)));
	rightHand->addComponent(new components::TransformAttach(vive.controllers[1].transform));
	rightHand->addComponent(hand);
	rightHand->addComponent(new components::ModelRenderer("data/vrlib/rendermodels/vr_controller_vive_1_5/vr_controller_vive_1_6.obj"));

	
	Node* leftHand = new Node("LeftHand", &Engine.scene);
	auto a = [this](const Scene& scene, const glm::mat4 &projectionMatrix, const glm::mat4 &modelViewMatrix, Node* cameraNode, int renderId) {this->Engine.renderer.render(scene, projectionMatrix, modelViewMatrix, cameraNode, renderId); };
	CameraApp* camApp = new CameraApp(leftHand, a);
	
	leftHand->addComponent(new components::Transform(glm::vec3(-2, 0, 0)));
	leftHand->addComponent(new components::TransformAttach(vive.controllers[0].transform));
	Tablet* tablet = new Tablet({ 1080,1920 }, 1, vive.controllers[1].transform, vive.controllers[1].triggerButton, {new MainApp(), camApp});
	leftHand->addComponent(tablet);
	//auto mr = new ShadelessMeshRenderer(tablet);
	//leftHand->addComponent(mr);

	//leftHand->addComponent(new components::ModelRenderer("data/vrlib/rendermodels/vr_controller_vive_1_5/vr_controller_vive_1_6.obj"));

	Node* testobj = new Node("Testobj", &Engine.scene);
	testobj->addComponent(new components::Transform(glm::vec3(0, 0, -2)));
	vrlib::tien::components::ModelRenderer* m = new components::ModelRenderer("data/Models/Environment/Building Blocks/Dungeon/wall_1.fbx");
	testobj->addComponent(m);
	testobj->addComponent(new VisibilityTester(0.75f, m, camApp));
}



TabletStart::TabletStart()
{
	clearColor = glm::vec4(0.2, 0.5, 0.4, 1.0);
}

TabletStart::~TabletStart()
{
}
