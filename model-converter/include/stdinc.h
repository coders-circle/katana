#pragma once

// STL

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <typeinfo>
#include <algorithm>


// GLM

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>


// ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


// common include files that may be needed by almost every source.

#include <utils.h>
