#include "stdafx.h"
#include "Utils.h"

const glm::vec3 g_axisX(1.f, 0.f, 0.f);

// Left hand open gesture transformation, thanks to https://github.com/spayne and his soft_knuckles repository
extern const vr::VRBoneTransform_t g_openHandGesture[31U] = {
    { { 0.000000f, 0.000000f, 0.000000f, 1.000000f }, { 1.000000f, -0.000000f, -0.000000f, 0.000000f } },
    { { -0.034038f, 0.026503f, 0.174722f, 1.000000f }, { -0.055147f, -0.078608f, -0.920279f, 0.379296f } },
    { { -0.012083f, 0.028070f, 0.025050f, 1.000000f }, { 0.464112f, 0.567418f, 0.272106f, 0.623374f } },
    { { 0.040406f, 0.000000f, -0.000000f, 1.000000f }, { 0.994838f, 0.082939f, 0.019454f, 0.055130f } },
    { { 0.032517f, 0.000000f, 0.000000f, 1.000000f }, { 0.974793f, -0.003213f, 0.021867f, -0.222015f } },
    { { 0.030464f, -0.000000f, -0.000000f, 1.000000f }, { 1.000000f, -0.000000f, -0.000000f, 0.000000f } },
    { { 0.000632f, 0.026866f, 0.015002f, 1.000000f }, { 0.644251f, 0.421979f, -0.478202f, 0.422133f } },
    { { 0.074204f, -0.005002f, 0.000234f, 1.000000f }, { 0.995332f, 0.007007f, -0.039124f, 0.087949f } },
    { { 0.043930f, -0.000000f, -0.000000f, 1.000000f }, { 0.997891f, 0.045808f, 0.002142f, -0.045943f } },
    { { 0.028695f, 0.000000f, 0.000000f, 1.000000f }, { 0.999649f, 0.001850f, -0.022782f, -0.013409f } },
    { { 0.022821f, 0.000000f, -0.000000f, 1.000000f }, { 1.000000f, -0.000000f, 0.000000f, -0.000000f } },
    { { 0.002177f, 0.007120f, 0.016319f, 1.000000f }, { 0.546723f, 0.541276f, -0.442520f, 0.460749f } },
    { { 0.070953f, 0.000779f, 0.000997f, 1.000000f }, { 0.980294f, -0.167261f, -0.078959f, 0.069368f } },
    { { 0.043108f, 0.000000f, 0.000000f, 1.000000f }, { 0.997947f, 0.018493f, 0.013192f, 0.059886f } },
    { { 0.033266f, 0.000000f, 0.000000f, 1.000000f }, { 0.997394f, -0.003328f, -0.028225f, -0.066315f } },
    { { 0.025892f, -0.000000f, 0.000000f, 1.000000f }, { 0.999195f, -0.000000f, 0.000000f, 0.040126f } },
    { { 0.000513f, -0.006545f, 0.016348f, 1.000000f }, { 0.516692f, 0.550143f, -0.495548f, 0.429888f } },
    { { 0.065876f, 0.001786f, 0.000693f, 1.000000f }, { 0.990420f, -0.058696f, -0.101820f, 0.072495f } },
    { { 0.040697f, 0.000000f, 0.000000f, 1.000000f }, { 0.999545f, -0.002240f, 0.000004f, 0.030081f } },
    { { 0.028747f, -0.000000f, -0.000000f, 1.000000f }, { 0.999102f, -0.000721f, -0.012693f, 0.040420f } },
    { { 0.022430f, -0.000000f, 0.000000f, 1.000000f }, { 1.000000f, 0.000000f, 0.000000f, 0.000000f } },
    { { -0.002478f, -0.018981f, 0.015214f, 1.000000f }, { 0.526918f, 0.523940f, -0.584025f, 0.326740f } },
    { { 0.062878f, 0.002844f, 0.000332f, 1.000000f }, { 0.986609f, -0.059615f, -0.135163f, 0.069132f } },
    { { 0.030220f, 0.000000f, 0.000000f, 1.000000f }, { 0.994317f, 0.001896f, -0.000132f, 0.106446f } },
    { { 0.018187f, 0.000000f, 0.000000f, 1.000000f }, { 0.995931f, -0.002010f, -0.052079f, -0.073526f } },
    { { 0.018018f, 0.000000f, -0.000000f, 1.000000f }, { 1.000000f, 0.000000f, 0.000000f, 0.000000f } },
    { { -0.006059f, 0.056285f, 0.060064f, 1.000000f }, { 0.737238f, 0.202745f, 0.594267f, 0.249441f } },
    { { -0.040416f, -0.043018f, 0.019345f, 1.000000f }, { -0.290331f, 0.623527f, -0.663809f, -0.293734f } },
    { { -0.039354f, -0.075674f, 0.047048f, 1.000000f }, { -0.187047f, 0.678062f, -0.659285f, -0.265683f } },
    { { -0.038340f, -0.090987f, 0.082579f, 1.000000f }, { -0.183037f, 0.736793f, -0.634757f, -0.143936f } },
    { { -0.031806f, -0.087214f, 0.121015f, 1.000000f }, { -0.003659f, 0.758407f, -0.639342f, -0.126678f } }
};

size_t ReadEnumVector(const std::string &f_val, const std::vector<std::string> &f_vec)
{
    size_t l_result = std::numeric_limits<size_t>::max();
    for(auto iter = f_vec.begin(), iterEnd = f_vec.end(); iter != iterEnd; ++iter)
    {
        if(!iter->compare(f_val))
        {
            l_result = std::distance(f_vec.begin(), iter);
            break;
        }
    }
    return l_result;
}

void ConvertMatrix(const vr::HmdMatrix34_t &f_matVR, glm::mat4 &f_mat)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++) f_mat[i][j] = f_matVR.m[j][i];
    }
    for(int i = 0; i < 3; i++) f_mat[i][3] = 0.f;
    f_mat[3][3] = 1.f;
}
void ConvertMatrix(const Leap::Matrix &f_leapMat, glm::mat4 &f_mat)
{
    Leap::FloatArray l_array = f_leapMat.rigidInverse().toArray4x4();
    std::memcpy(&f_mat, l_array.m_array, sizeof(glm::mat4));
}

void ConvertQuaternion(const glm::quat& f_glmQuat, vr::HmdQuaternionf_t &f_vrQuat)
{
    f_vrQuat.x = f_glmQuat.x;
    f_vrQuat.y = f_glmQuat.y;
    f_vrQuat.z = f_glmQuat.z;
    f_vrQuat.w = f_glmQuat.w;
}
void ConvertQuaternion(const vr::HmdQuaternionf_t &f_vrQuat, glm::quat& f_glmQuat)
{
    f_glmQuat.x = f_vrQuat.x;
    f_glmQuat.y = f_vrQuat.y;
    f_glmQuat.z = f_vrQuat.z;
    f_glmQuat.w = f_vrQuat.w;
}

void ConvertVector3(const vr::HmdVector4_t &f_vrVec, glm::vec3 &f_glmVec)
{
    for(size_t i = 0U; i < 3U; i++) f_glmVec[i] = f_vrVec.v[i];
}
void ConvertVector3(const glm::vec3 &f_glmVec, vr::HmdVector4_t &f_vrVec)
{
    for(size_t i = 0U; i < 3U; i++) f_vrVec.v[i] = f_glmVec[i];
}

void SwitchBoneAxes(glm::quat &f_rot)
{
    std::swap(f_rot.x, f_rot.z);
    f_rot.y *= -1.f;
}
void FixAuxBoneTransformation(glm::vec3 &f_pos, glm::quat &f_rot)
{
    f_pos.y *= -1.f;
    f_pos.z *= -1.f;
    f_rot.y *= -1.f;
    f_rot.z *= -1.f;
    f_rot = glm::rotate(f_rot, glm::pi<float>(), g_axisX);
}