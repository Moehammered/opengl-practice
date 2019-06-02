#include "VertexArrayObject.h"
#include <string>
#include <iostream>
#include <sstream>
#include <ostream>

VertexArrayObject::VertexArrayObject()
{
	vao = vbo = ebo = 0;
	initialise();
}


VertexArrayObject::~VertexArrayObject()
{
}

void VertexArrayObject::setupBuffers(BufferProperty * const properties, GLuint propertyCount)
{
	//setup vbo, ebo, and VAO
	if (!properties) //can't setup with no properties given
		return;

	this->properties.reserve(propertyCount);
	this->properties.insert(this->properties.begin(), properties, properties + propertyCount);
	bindVAO();
	GLuint bufferID = 0;
	for (GLuint i = 0; i < propertyCount; ++i)
	{
		//figure out the buffer
		BufferProperty& prop = properties[i];
		switch (prop.bufferTarget)
		{
			case GL_ARRAY_BUFFER:
				bufferID = vbo;
				break;
			case GL_ELEMENT_ARRAY_BUFFER:
				bufferID = ebo;
				break;
			default: //skip it as it's unsupported for now
				bufferID = 0;
				printf("\nBuffer target[%i] not yet supported. Skipping setup.\n\n",
					prop.bufferTarget);
				printBufferProperty(prop);
				continue;
		}

		glBindBuffer(prop.bufferTarget, bufferID);
		glBufferData(prop.bufferTarget, prop.bufferSize, prop.data, prop.usage);
		glBindBuffer(prop.bufferTarget, 0);
		printBufferProperty(prop);
	}
	unbind();
}

void VertexArrayObject::setupAttributes(VertexAttributes * const attributes, GLuint attribCount)
{
	//setup vbo attribute pointers here!
	if (!attributes) //can't setup with no attributes given
		return;

	this->attributes.reserve(attribCount);
	this->attributes.insert(this->attributes.begin(), attributes, attributes + attribCount);
	bindVAO();
	bindVBO();
	for (GLuint i = 0; i < attribCount; ++i)
	{
		VertexAttributes att = attributes[i];
		glVertexAttribPointer(att.position, att.componentCount, att.type, 
			att.normalised, att.stride, att.componentOffset);
		printVertexAttribute(att);
		glEnableVertexAttribArray(att.position);
	}

	unbind();
}

void VertexArrayObject::enableAttribute(GLuint attribNumber)
{
	bindVAO();
	bindVBO();
	glEnableVertexAttribArray(attribNumber);
	unbind();
}

void VertexArrayObject::disableAttribute(GLuint attribNumber)
{
	bindVAO();
	bindVBO();
	glDisableVertexAttribArray(attribNumber);
	unbind();
}

void VertexArrayObject::copyDataToBuffer(GLenum target, const GLvoid * data, GLsizeiptr dataSize)
{
	//figure out type
	switch (target)
	{
	case GL_ARRAY_BUFFER:
		bindVBO();
		glBufferSubData(target, 0, dataSize, data);
		glBindBuffer(target, 0);
		break;
	case GL_ELEMENT_ARRAY_BUFFER:
		bindVAO();
		bindEBO();
		glBufferSubData(target, 0, dataSize, data);
		glBindVertexArray(0);
		glBindBuffer(target, 0);
		break;
	default: //skip it as it's unsupported for now
		std::cout << "UNSUPPORTED TYPE TO COPY DATA TO BUFFER!\n\n";
		return;
	}
}

void VertexArrayObject::bindVAO()
{
	glBindVertexArray(vao);
}

void VertexArrayObject::bindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexArrayObject::bindEBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void VertexArrayObject::unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const std::vector<BufferProperty>& VertexArrayObject::Properties()
{
	return properties;
}

const std::vector<VertexAttributes>& VertexArrayObject::Attributes()
{
	return attributes;
}

void VertexArrayObject::initialise()
{
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);
}

void VertexArrayObject::printBufferProperty(BufferProperty & prop)
{
	std::string output;
	output += "\nBuffer Property Info - ";
	//figure out type
	switch (prop.bufferTarget)
	{
	case GL_ARRAY_BUFFER:
		output += "{VERTEX BUFFER OBJECT PROPERTY}\n";
		break;
	case GL_ELEMENT_ARRAY_BUFFER:
		output += "{ELEMENT BUFFER OBJECT PROPERTY}\n";
		break;
	default: //skip it as it's unsupported for now
		output += "{UNSUPPORTED BUFFER OBJECT PROPERTY [" + std::to_string(prop.bufferTarget) + "]\n";
		break;
	}
	output += "Data size:\t" + std::to_string(prop.bufferSize) + " bytes\n";
	output += "Data location:\t";
	std::stringstream ss;
	ss << prop.data;
	output += prop.data == nullptr ? "nullptr\n" : ss.str() + "\n";
	output += "Buffer usage:\t";
	switch (prop.usage)
	{
		case GL_STATIC_DRAW:
		case GL_STATIC_COPY:
		case GL_STATIC_READ:
			output += "STATIC\n";
			break;
		case GL_DYNAMIC_COPY:
		case GL_DYNAMIC_DRAW:
		case GL_DYNAMIC_READ:
			output += "DYNAMIC\n";
			break;
		default:
			output += "UNKNOWN/UNSUPPORTED[" + std::to_string(prop.usage) + "]\n";
			break;
	}

	std::cout << output << std::endl;
}

void VertexArrayObject::printVertexAttribute(VertexAttributes & attr)
{
	std::stringstream ss;
	ss << "\nVertex Attribute Info - " << attr.position << "\n";
	ss << "Component Count:\t" << attr.componentCount << "\n";
	ss << "Data type:\t\t";
	std::string typeName;
	switch (attr.type)
	{
		case GL_UNSIGNED_INT_10F_11F_11F_REV:
			typeName = "GL_UNSIGNED_INT_10F_11F_11F_REV";
			break;
		case GL_UNSIGNED_INT_2_10_10_10_REV:
			typeName = "GL_UNSIGNED_INT_2_10_10_10_REV";
			break;
		case GL_INT_2_10_10_10_REV:
			typeName = "GL_INT_2_10_10_10_REV";
			break;
		case GL_DOUBLE:
			typeName = "GL_DOUBLE";
			break;
		case GL_FLOAT:
			typeName = "GL_FLOAT";
			break;
		case GL_HALF_FLOAT:
			typeName = "GL_HALF_FLOAT";
			break;
		case GL_UNSIGNED_BYTE:
			typeName = "GL_UNSIGNED_BYTE";
			break;
		case GL_BYTE:
			typeName = "GL_BYTE";
			break;
		case GL_SHORT:
			typeName = "GL_SHORT";
			break;
		case GL_UNSIGNED_SHORT:
			typeName = "GL_UNSIGNED_SHORT";
			break;
		case GL_UNSIGNED_INT:
			typeName = "GL_UNSIGNED_INT";
			break;
		case GL_INT:
			typeName = "GL_INT";
			break;
		default:
			typeName = "Unknown/Unsupported Type[" + std::to_string(attr.type) + "]";
			break;
	}
	ss << typeName << "\n";
	ss << "Normalised Values?\t" << (attr.normalised ? "Yes" : "No") << "\n";
	ss << "Data stride:\t\t" << attr.stride << "\n";
	ss << "Data offset:\t\t" << attr.componentOffset << "\n";

	std::cout << ss.str() << std::endl;
}
