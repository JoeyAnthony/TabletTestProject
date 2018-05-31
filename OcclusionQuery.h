#pragma once
#include <VrLib\tien\Tien.h>

class OcclusionQuery 
{
private:
	GLuint type = GL_SAMPLES_PASSED;
	GLuint queryID = 0;
	GLint renderedSamples = 0;
	bool hasResults = false;

public:
	void beginQuery();
	void endQuery();
	bool resultsAvailable();
	int getResult();


	OcclusionQuery();
	~OcclusionQuery();
};

