#pragma once

#include <vector>
#include "ModelData.h"

#include <glm/glm.hpp>


class FileLoader
{
public:
    FileLoader();
	const ModelData* getModel();
	bool loadObject(const char* path);
    FileLoader(const FileLoader&) = delete;
    void operator=(const FileLoader&) = delete;
    virtual ~FileLoader();

private:
	ModelData * data_;
};

