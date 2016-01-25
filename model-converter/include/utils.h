#pragma once


inline glm::mat4 AiToGlmMatrix(aiMatrix4x4 &aiMat)
{
    aiVector3D aiPos;
    aiQuaternion aiRot;
    aiVector3D aiScale;
    aimat.Decompose(aiScale, aiRot, aiPos);

    glm::vec3 pos(aiPos.x, aiPos.y, aiPos.z);
    glm::quat rot(aiRot.x, aiRot.y, aiRot.z, aiRot.w);
    glm::vec3 scale(aiScale.x, aiScale.y, aiScale.z);

    return glm::translate(glm::mat4(), pos)
        * glm::mat4_cast(rot)
        * glm::scale(glm::mat4(), scale);
}
