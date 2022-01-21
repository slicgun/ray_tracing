#include "CornellBoxExample.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include<stb_image_write.h>
#include<vector>
#include<glm/geometric.hpp>

#include"Log.h"
#include"Renderer/IntersectionTests.h"
#include"Model/Material.h"

glm::vec3 BlinnPhongg(const glm::vec3& cameraPos, const glm::vec3& pixelPos, const glm::vec3& lightPos, const glm::vec3& normal, const Material& mat);

CornellBoxExample::CornellBoxExample(Image& img)
	:Example(img), m_cornellBox("res/models/CornellBoxOriginal/CornellBoxOriginal.obj", {0, -1, -1.2})
{
	m_camera.position = {0, 0, 0};
	m_camera.target = {0, 0, -1};

	m_camera.lookAt = glm::normalize(m_camera.target - m_camera.position);
	m_camera.right = glm::normalize(glm::cross({0, 1, 0}, m_camera.lookAt));
	m_camera.up = glm::cross(m_camera.lookAt, m_camera.right);
}

void CornellBoxExample::draw()
{
	for(unsigned y = 0; y < m_image.height * m_image.channels; y += m_image.channels)
		for(unsigned x = 0; x < m_image.width * m_image.channels; x += m_image.channels)
		{
			glm::ivec2 pixel;
			pixel.x = x / m_image.channels;
			pixel.y = y / m_image.channels;

			for(unsigned i = 0; i < m_cornellBox.size(); i += 3)
			{
				Ray r = getRayThroughPixel(pixel.x, pixel.y);
				float u, v, t;
				if(Intersection::Triangle::mollerTrumbore(r, t, m_cornellBox[i], m_cornellBox[i + 1], m_cornellBox[i + 2], u, v))
				{
					float depth = r(t).z;
					int depthBufferIndex = index(pixel.x, pixel.y);

					if(depth < m_depthBuffer[depthBufferIndex])
					{
						glm::vec3 color = {255, 255, 255};
						m_depthBuffer[depthBufferIndex] = depth;
						//glm::vec3 color = m_texture.getColor((1 - v - u) * m_cube[i].uv + u * m_cube[i + 1].uv + v * m_cube[i + 2].uv);
						Material mat = m_cornellBox.getMaterial(m_cornellBox[i].materialID);
						glm::vec3 light = BlinnPhongg(m_camera.position, r(t), {0, 0.96, -1.5}, m_cornellBox[i].normal, mat);
						light = mat.ka;
						//light = 1;
						setPixelColor(x, y, glm::vec3{255, 255, 255} * light);
					}
				}
				else
				{
					//
				}
			}
		}
	stbi_write_png("output/cornellBox.png", m_image.width, m_image.height, m_image.channels, m_image.data, m_image.step);
}

glm::vec3 BlinnPhongg(const glm::vec3& cameraPos, const glm::vec3& pixelPos, const glm::vec3& lightPos, const glm::vec3& normal, const Material& mat)
{
	static float kd = 0.8f; //diffuse reflectance
	static float ks = 1.2f; //specular reflectance
	static float ka = 0.1f; //ambient reflectance
	static float shininess = 32;

	glm::vec3 lightDir = lightPos - pixelPos;

	//diffuse
	glm::vec3 N = glm::normalize(normal);
	glm::vec3 L = glm::normalize(lightDir);
	glm::vec3 diffuse = mat.kd * glm::max(glm::dot(N, L), 0.f);

	//specular
	glm::vec3 reflection = 2.f * glm::dot(L, N) * (N - L);
	glm::vec3 viewDir = glm::normalize(cameraPos - pixelPos);
	glm::vec3 specular = mat.ks + glm::pow(glm::max(glm::dot(viewDir, reflection), 0.f), mat.ns);

	glm::vec3 ambient = mat.ka * 0.1f;

	return glm::min(diffuse + specular + ambient, {1, 1, 1});
}

//there are 32 material ids
//96 verts
//96 / 3 = 32
//so material id for each tri