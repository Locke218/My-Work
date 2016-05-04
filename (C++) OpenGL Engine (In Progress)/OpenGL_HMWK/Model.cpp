#include "Model.h"



Model::Model()
{
	vertArr = 0;
	vertCount = 0;
}


Model::~Model()
{
}

bool Model::buffer() {
	vector< vec3> locs =
	{ { 1, 1, 0 },
	{ -1, 1, 0 },
	{ -1, -1, 0 },
	{ 1, -1, 0 }, };

	vector< vec2> uvs =
	{ { 1, 1 },
	{ 0, 1 },
	{ 0, 0 },
	{ 1, 0 }, };

	vector <unsigned int> locInds =
	{ 0, 1, 2, 0, 2, 3 };

	vertCount = locInds.size();

	vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++) {
		vertBufData[i].loc = locs[locInds[i]];
		vertBufData[i].uv = uvs[locInds[i]];
	}

	GLuint vertBuf;

	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) *vertCount,
		&vertBufData[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		0);

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof(vec3));

	glBindVertexArray(0);

	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	return true;
}

void Model::render(vector<Object>& objects) {

	glBindVertexArray(vertArr);

	for (int i = 0; i < 11; i++) {
		glBindTexture(GL_TEXTURE_2D, objects[i].texID);
		glUniformMatrix4fv(2, 1, GL_FALSE, &objects[i].transform.tfMatrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
	}
	glBindVertexArray(0);

}