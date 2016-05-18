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

	//************************************************
	//************************************************
	//************************************************
	
	vector<vec3> locations2;
	vector<vec2> uvs2;
	vector<vec3> normals2;
	vector<vertInd> indices2;

	k = 0;

	inFile.open("models/quad.obj");

	if (inFile.is_open()) {
		cout << "worked" << endl;

		fileData = string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	}
	else return false;

	inFile.close();

	fileData2 = istringstream(fileData);

	cout << "worked2" << endl;
	
	while (getline(fileData2, line)) {
		stringstream ss(line);
		string id;

		ss >> id;

		if (id == "v") {
			float one, two, three;
			ss >> one >> two >> three;
			locations2.push_back(vec3(one, two, three));
		}
		else if (id == "vt") {
			float one, two;
			ss >> one >> two;
			uvs2.push_back(vec2(one, two));
		}
		else if (id == "vn") {
			float one, two, three;
			ss >> one >> two >> three;
			normals2.push_back(vec3(one, two, three));
		}
		else if (id == "f") {
			unsigned int one, two, three;
			char slash;
			for (int i = 0; i < 3; i++) {
				ss >> one >> slash >> two >> slash >> three;
				indices2.push_back(vertInd(one - 1, two - 1, three - 1));
				k++;
			}
		}
	}
	cout << "worked3" << endl;

	vertCount2 = indices2.size();

	vector<Vertex> vertBufData2(vertCount2);
	for (unsigned int i = 0; i < vertCount2; i++) {
		vertBufData2[i] = { locations2[indices2[i].locInd],
			uvs2[indices2[i].uvInd],
			normals2[indices2[i].normInd] };
	}

	cout << "worked4" << endl;

	GLuint vertBuf2;

	glGenVertexArrays(1, &vertArr2);
	glGenBuffers(1, &vertBuf2);

	cout << "worked5" << endl;

	glBindVertexArray(vertArr2);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf2);

	cout << "worked6" << endl;

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) *vertCount2,
		&vertBufData2[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	cout << "worked7" << endl;

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

	glBindVertexArray(1);

	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	cout << "worked8" << endl;
	
	return true;
}

void Model::render(vector<Object>& objects, int numOpt) {
	
	glBindVertexArray(vertArr);

	for (int i = 0; i < objects.size(); i++) {
		if (numOpt == 2) {
			if ((i + 1) % 3 == 0) {
				glBindVertexArray(vertArr2);
			}
			else glBindVertexArray(vertArr);
		}
		else if(numOpt == 3) glBindVertexArray(vertArr2);

		glBindTexture(GL_TEXTURE_2D, objects[i].texID);
		glUniformMatrix4fv(3, 1, GL_FALSE, &objects[i].transform.tfMatrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
	}

	glBindVertexArray(0);

}