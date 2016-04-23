//AUTHOR: Zane Draper
//
//PURPOSE: Load and maintain shaders
//
//**********************************

#include "ShaderManager.h"


//ShaderManager Constructor
ShaderManager::ShaderManager()
{
	program = 0;
}

//ShaderManager Deconstructor
ShaderManager::~ShaderManager()
{
}

//Method: Load Shaders
bool ShaderManager::loadShaders(const char* vertexFile, const char* fragmentFile) {
	GLuint vertexShader = loadShader(vertexFile, GL_VERTEX_SHADER);
	GLuint fragmentShader = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

	if (vertexShader == 0 || fragmentShader == 0) return 0;

	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	GLint linked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (linked == false) {
		GLint length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		GLchar* logOut;
		glGetProgramInfoLog(program, length, 0, logOut);

		cout << 2 << endl;
		cout << logOut << endl;

		glDeleteProgram(program);
		delete[] logOut;

		return false;
	}

	else return true;
}

//Loads an individual shader based off of filename
GLuint ShaderManager::loadShader(const char* file, GLenum shaderType) {

	ifstream inFile;
	string line;
	char* charArrPtr;
	GLint compiled = 0;

	inFile.open(file, ios::binary);

	if (inFile.is_open()) {
		inFile.seekg(0, ios::end);
		int length = (int)inFile.tellg();
		inFile.seekg(0, ios::beg);

		charArrPtr = new char[length + 1];

		inFile.read(charArrPtr, length);
		charArrPtr[length] = 0;

		inFile.close();
	}
	else {
		cout << "Failure" << endl;
		return false;
	}

	GLuint tempShader = glCreateShader(shaderType);

	const GLchar* chars = (const GLchar*)charArrPtr;
	glShaderSource(tempShader, 1, &chars, 0);

	glCompileShader(tempShader);
	glGetShaderiv(tempShader, GL_COMPILE_STATUS, &compiled);

	delete[] chars;

	if (compiled == false) {
		GLint length = 0;
		glGetShaderiv(tempShader, GL_INFO_LOG_LENGTH, &length);

		GLchar* logOut = new char[length];

		glGetShaderInfoLog(tempShader, length, 0, logOut);

		cout << 1 << endl;
		cout << logOut << endl;

		glDeleteShader(tempShader);
		delete[] logOut;

		return 0;
	}

	else return tempShader;

}

//Returns the class program
GLuint ShaderManager::getProgram() const {
	return program;
}
