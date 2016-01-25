#pragma once


inline glm::mat4 AiToGlmMatrix(aiMatrix4x4 &aiMat)
{
    aiVector3D aiPos;
    aiQuaternion aiRot;
    aiVector3D aiScale;
    aiMat.Decompose(aiScale, aiRot, aiPos);

    glm::vec3 pos(aiPos.x, aiPos.y, aiPos.z);
    glm::quat rot(aiRot.x, aiRot.y, aiRot.z, aiRot.w);
    glm::vec3 scale(aiScale.x, aiScale.y, aiScale.z);

    return glm::translate(glm::mat4(), pos)
        * glm::mat4_cast(rot)
        * glm::scale(glm::mat4(), scale);
}


inline std::string GetFilename(const std::string& path)
{
    std::string temp = path;

    size_t s = temp.find_last_of("/");
    if (s != std::string::npos)
        temp = temp.substr(s+1, temp.size()-s-1);

    return temp;
}


inline void WriteString(std::ofstream& file, const std::string& string)
{
    unsigned int num = string.size();
    file.write((char*)&num, sizeof(num));
    file.write(string.c_str(), num);
}
