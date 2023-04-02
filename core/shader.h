

#ifndef IRON_SHADER
#define IRON_SHADER

#include "iron_gl.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "core_structure.h"


class Shader
{
public:
    unsigned int ID;
    Shader(const char* vertex, const char* fragment);

    void use() ;
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const;

    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const;
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const;

    void setMat4(const std::string &name, mat4 value) const;

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif
