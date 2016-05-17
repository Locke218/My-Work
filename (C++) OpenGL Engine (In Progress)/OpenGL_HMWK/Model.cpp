#include "Model.h"



Model::Model()
{
	vertArr = 0;
	vertCount = 0;
}


Model::~Model()
{
}

bool Model::buffer(string objFile) {
	vector<vec3> locations;
	vector<vec2> uvs;
	vector<vec3> normals;
	vector<vertInd> indices;

	int k = 0;

	ifstream inFile;
	string fileData;

	inFile.open("models/" + objFile);

	if (inFile.is_open()) {
		cout << "worked" << endl;

		fileData = string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	}
	else return false;

	inFile.close();

	istringstream fileData2(fileData);
	string line;

	while (getline(fileData2, line)) {
		stringstream ss(line);
		string id;

		ss >> id;

		if (id == "v") {
			float one, two, three;
			ss >> one >> two >> three;
			locations.push_back(vec3(one, two, three));
		}
		else if (id == "vt") {
			float one, two;
			ss >> one >> two;
			uvs.push_back(vec2(one, two));
		}
		else if (id == "vn") {
			float one, two, three;
			ss >> one >> two >> three;
			normals.push_back(vec3(one, two, three));
		}
		else if (id == "f") {
			unsigned int one, two, three;
			char slash;
			for (int i = 0; i < 3; i++) {
				ss >> one >> slash >> two >> slash >> three;
				indices.push_back(vertInd(one - 1, two - 1, three - 1));
				k++;
			}
		}
	}

	vertCount = indices.size();

	vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++) {
		vertBufData[i] = { locations[indices[i].locInd],
							uvs[indices[i].uvInd],
							normals[indices[i].normInd] };
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

	glEnableVertexAttribArray(2);

	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)20);

	glBindVertexArray(0);

	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	return true;
}

void Model::render(vector<Object>& objects) {

	glBindVertexArray(vertArr);

	for (int i = 0; i < objects.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, objects[i].texID);
		glUniformMatrix4fv(3, 1, GL_FALSE, &objects[i].transform.tfMatrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
	}

	glBindVertexArray(0);

}