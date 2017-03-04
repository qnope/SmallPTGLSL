#version 450 core

layout(location = 0) in vec2 clipSpace;
layout(location = 0) out vec3 outColor;

layout(location = 0) uniform mat4 mat;
layout(location = 1) uniform vec3 posCamera;

#define DIFF 0.0
#define SPEC 1.0
#define REFR 2.0

struct Material {
    vec4 emission;
    vec4 albedoType;
};
struct Sphere {
    vec4 positionRadius;
    int materialIndex;
    int padd, padd2, padd3;
};

struct Plane {
    vec4 equation;
    int materialIndex;
    int padd, padd2, padd3;
};

struct Ray {
    vec3 o;
    vec3 d;
};

layout(binding = 0, std430) restrict readonly buffer Spheres {
    Sphere spheres[];
};

layout(binding = 1, std430) restrict readonly buffer Planes {
    Plane planes[];
};

layout(binding = 2, std430) restrict readonly buffer Materials {
    Material materials[];
};

layout(binding = 3, std430) restrict readonly buffer _Random {
    uint nValue;
    uint current;
    float values[];
}Random;

vec2 random()
{
    uint index1 = atomicAdd(Random.current, 2) % Random.nValue;
    uint index2 = (index1 + 1) % Random.nValue;
    return vec2(Random.values[index1], Random.values[index2]);
}

vec3 transformDirToFitToN(vec3 N, vec3 dir) {
    vec3 random = dot(abs(N), vec3(0.0, 1.0, 0.0)) < 0.999 ? vec3(0.0, 1.0, 0.0) : vec3(0.0, 0.0, 1.0);

    vec3 t = normalize(cross(random, N));
    vec3 b = cross(N, t);

    return mat3(t, b, N) * dir;
}

vec3 importanceSamplingDiffuse(vec2 Xi, vec3 n) {
    float phi = 2 * 3.1415926535 * Xi.x;
    float cosTheta = pow(Xi.y, 1.0 / 2.0);
    float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    vec3 dir = vec3(cos(phi) * sinTheta, sin(phi) * sinTheta, cosTheta);
    return transformDirToFitToN(n, dir);
}

float intersectPlane(in const Ray r, in const int index) {
    return -(planes[index].equation.w + dot(r.o, planes[index].equation.xyz)) / dot(r.d, planes[index].equation.xyz);
}

float intersectSphere(in const Ray r, in const int index) {
    const float radiusSquare = spheres[index].positionRadius.w * spheres[index].positionRadius.w;
    const vec3 posToRo = r.o - spheres[index].positionRadius.xyz;
    const float b = dot(r.d, posToRo);
    const float c = dot(posToRo, posToRo) - radiusSquare;
    const float delta = b * b - c;

    if(delta < 0.0)
        return -1.0;

    const float disc = sqrt(delta);
    const float far = (-b + disc);
    float near = (-b - disc);

    if(near < 0.0)
        near = far;
    return near < 1e20 ? near : -1.0;
}

int getNearest(in const Ray r, out float dist, out bool isSphere) {
    dist = 1e30;
    int j = -1;
    isSphere = false;
    for(int i = 0; i < 6; ++i) {
        float t = intersectPlane(r, i);
        if(t > 0.0 && t < dist) {
            dist = t;
            j = i;
        }
    }

    for(int i = 0; i < 3; ++i) {
        float t = intersectSphere(r, i);
        if(t > 0.0 && t < dist) {
            dist = t;
            j = i;
            isSphere = true;
        }
    }
    return j;
}

void main() {
    outColor = vec3(0.0);

    /* GI */

    const int nSamples = 1024;
    int nSample = nSamples;

    while(nSample-- != 0) {
        int nDepth = 6;
        Ray r;
        r.o = posCamera;
        r.d = normalize((inverse(mat) * vec4(clipSpace, 1.0, 1.0)).xyz);
        vec3 multiplicator = vec3(1.0);

        while(nDepth-- != 0) {
            float dist;
            bool isSphere;
            int i = getNearest(r, dist, isSphere);

            if(i != -1) {
                Material m;
                vec3 normal;
                vec3 newPos = r.o + dist * r.d;

                if(isSphere) {
                    m = materials[spheres[i].materialIndex];
                    normal = normalize(newPos - spheres[i].positionRadius.xyz);
                }

                else {
                    m = materials[planes[i].materialIndex];
                    normal = normalize(planes[i].equation.xyz);
                }

                outColor += (multiplicator * m.emission.rgb) / nSamples;

                if(m.albedoType.w == DIFF) {
                    multiplicator *= m.albedoType.rgb;

                    r.d = importanceSamplingDiffuse(random(), normal);
                    r.o = newPos + 0.1 * r.d;
                }

                else if(m.albedoType.w == SPEC) {
                    r.d = normalize(reflect(r.d, normal));
                    r.o = newPos + 0.1 * r.d;
                }

                else {
                    float index = 1.4;

                    if(dot(r.d, normal) < 0.0)
                        r.d = normalize(refract(r.d, normal, 1.0 / index));
                    else
                        r.d = normalize(refract(r.d, -normal, index));
                    r.o = newPos + 0.1 * r.d;
                }
            }
        }
    }

    outColor = pow(outColor, vec3(1 / 2.2));

    /* AO */

   /* const int nSamples = 1024;
    int nSample = nSamples;

    Ray r;
    r.o = posCamera;
    r.d = normalize((inverse(mat) * vec4(clipSpace, 1.0, 1.0)).xyz);
    float dist;
    bool isSphere;
    int i = getNearest(r, dist, isSphere);

    if(i == -1) {
        outColor = vec3(0.0);
    }

    vec3 normal;
    vec3 newPos = r.o + dist * r.d;

    if(isSphere)
        normal = normalize(newPos - spheres[i].positionRadius.xyz);

    else
        normal = normalize(planes[i].equation.xyz);

    float ao = 0.0;

    while(nSample-- != 0) {
        r.d = importanceSamplingDiffuse(random(), normal);
        r.o = newPos + 0.1 * r.d;
        if(getNearest(r, dist, isSphere) != -1)
            ao += clamp(1.0 / (nSamples * (1.0 + .01 * dist)), 0, 1);
    }
    outColor = vec3(1 - ao);*/
}
