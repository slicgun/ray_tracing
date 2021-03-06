#pragma once

#include<vector>
#include<unordered_map>

#include"Texture/Texture.h"
#include"Material.h"
#include"Shape/Vertex.h"
#include"Shape/Triangle.h"

class Model
{
public:
	Model(const std::string& filepath, const glm::vec3& offset);

	Model(Model& other);
	Model& operator=(const Model& rhs);

	Model(Model&& other);
	Model& operator=(Model&& rhs);

	std::vector<Triangle>::iterator begin() noexcept { return m_triangles.begin(); }
	std::vector<Triangle>::iterator end() noexcept { return m_triangles.end(); }
	const Triangle& operator[] (size_t pos) const { return m_triangles[pos]; }
	const std::vector<Triangle> getTriangles() const { return m_triangles; }

	size_t size() const noexcept { return m_triangles.size(); }

	const Material& getMaterial(int id) { return m_materials[id]; }
private:
	//my stuff
	std::vector<Triangle> m_triangles;
	std::vector<Material> m_materials;
};