#include "shader.hpp"

Shader &Shader::Use() {
  glUseProgram(this->ID);
  return *this;
}

void Shader::Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource) {
  unsigned int vertex, fragment, geometry;

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexSource, NULL);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentSource, NULL);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");

  if (geometrySource != nullptr) {
    geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &geometrySource, NULL);
    glCompileShader(geometry);
    checkCompileErrors(geometry, "GEOMETRY");
  }

  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertex);
  glAttachShader(this->ID, fragment);
  if (geometrySource != nullptr)
    glAttachShader(this->ID, geometry);
  glLinkProgram(this->ID);
  checkCompileErrors(this->ID, "PROGRAM");

  glDeleteShader(vertex);
  glDeleteShader(fragment);
  if (geometrySource != nullptr)
    glDeleteShader(geometry);
}

void Shader::SetFloat(const char *name, float value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetInt(const char *name, int value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetVec2f(const char *name, float x, float y, bool useShader) {
    if (useShader)
    this->Use();
  glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::SetVec2f(const char *name, const glm::vec2 &value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::SetVec3f(const char *name, float x, float y, float z, bool useShader) {
  if (useShader)
    this->Use();
  glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::SetVec3f(const char *name, const glm::vec3 &value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::SetVec4f(const char *name, float x, float y, float z, float w, bool useShader) {
  if (useShader)
    this->Use();
  glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::SetVec4f(const char *name, const glm::vec4 &value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMat4(const char *name, const glm::mat4 &matrix, bool useShader) {
  if (useShader)
    this->Use();
  glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type
        << "\n" << infoLog
        << "\n -- --------------------------------------------------- -- "
        << std::endl;
    }
  } else {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::PROGRAM: Link-time error: Type: " << type
        << "\n" << infoLog
        << "\n -- --------------------------------------------------- -- "
        << std::endl;
    }
  }
}
