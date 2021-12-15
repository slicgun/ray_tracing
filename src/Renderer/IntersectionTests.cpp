#include "IntersectionTests.h"

#include<glm/geometric.hpp>

bool Intersection::triangle_halfPlane(Ray& r, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2)
{
	//ray-plane intersection
	glm::vec3 v0v1 = v1 - v0;
	glm::vec3 v0v2 = v2 - v0;
	glm::vec3 normal = glm::cross(v0v1, v0v2);

	float deno = glm::dot(normal, r.direction);
	float numerator = (glm::dot(normal, v0) + glm::dot(normal, r.origin));

	if(deno <= 0.0001) //divide by 0 = :(, this also means that r is (almost) perpendicular and will never hit
		return false;
	float t = numerator / deno;

	if(t < 0) //plane is behind ray's origin and therefore camera
		return false;

	glm::vec3 hit = r(t);

	glm::vec3 e0 = v1 - v0;
	glm::vec3 e1 = v2 - v1;
	glm::vec3 e2 = v0 - v2;

	glm::vec3 c0 = hit - v0;
	glm::vec3 c1 = hit - v1;
	glm::vec3 c2 = hit - v2;

	//3 half plane tests
	return glm::dot(normal, glm::cross(e0, c0)) > 0
		&& glm::dot(normal, glm::cross(e1, c1)) > 0
		&& glm::dot(normal, glm::cross(e2, c2)) > 0;
}

bool Intersection::triangle_barycentric(Ray& r, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2)
{
	return false;
}