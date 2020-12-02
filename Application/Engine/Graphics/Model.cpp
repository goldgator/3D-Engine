#include "pch.h"
#include "Model.h"
#include <sstream>

namespace nc
{
	bool Model::Load(const std::string& filename,
		std::vector<glm::vec3>& positions,
		std::vector<glm::vec3>& normals,
		std::vector<glm::vec2>& texcoords)
	{
		std::vector<glm::vec3> model_positions;
		std::vector<glm::vec3> model_normals;
		std::vector<glm::vec2> model_texcoords;

		std::ifstream stream(filename, std::ios::binary);
		if (!stream.is_open())
		{
			SDL_Log("Error opening model file: %s", filename.c_str());
			return false;
		}

		std::istringstream blah("iejfs");

		// read the model data
		std::string line;
		while (std::getline(stream, line))
		{
			if (line.substr(0, 2) == "v ") {
				std::istringstream string_stream(line.substr(2));
				glm::vec3 position;
				string_stream >> position.x;
				string_stream >> position.y;
				string_stream >> position.z;

				model_positions.push_back(position);

			}
			else if (line.substr(0, 3) == "vn ") {
				std::istringstream string_stream(line.substr(3));
				glm::vec3 position;
				string_stream >> position.x;
				string_stream >> position.y;
				string_stream >> position.z;

				model_normals.push_back(position);

			}
			else if (line.substr(0, 3) == "vt ") {
				std::istringstream string_stream(line.substr(3));
				glm::vec3 position;
				string_stream >> position.x;
				string_stream >> position.y;
				string_stream >> position.z;

				model_texcoords.push_back(position);
			}
			else if (line.substr(0, 2) == "f ") {
				std::istringstream stream{ line.substr(2) };
				std::string str;
				while (std::getline(stream, str, ' '))
				{
					std::istringstream stream(str);
					std::string indexString;

					size_t i = 0;
					unsigned int index[3] = { 0, 0, 0 }; // position, texcoord, normal
					// read each index separated by '/'
					while (std::getline(stream, indexString, '/'))
					{
						if (!indexString.empty())
						{
							std::istringstream indexStream{ indexString };
							indexStream >> index[i];
						}
						i++;
					}

					if (index[0])
					{
						glm::vec3 position = model_positions[index[0] - 1];
						positions.push_back(position);
					}

					if (index[1])
					{
						glm::vec2 position = model_texcoords[index[1] - 1];
						texcoords.push_back(position);
					}

					if (index[2])
					{
						glm::vec3 position = model_normals[index[2] - 1];
						normals.push_back(position);
					}
				}

			}
		}

		stream.close();
		return true;
	}
}

