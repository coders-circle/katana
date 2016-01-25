#pragma once

// STL

#include <iostream>
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


// GLEW

#include <GL/glew.h>


// common include files that may be needed by almost every source.

#include <utils/Exception.h>
#include <utils/ListUtils.h>
#include <utils/FileUtils.h>
#include <utils/Manager.h>
