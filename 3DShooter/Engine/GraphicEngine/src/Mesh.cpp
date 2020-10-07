#include "../lib/Mesh.h"

Mesh::Mesh() :
	va(), vb(), ib(), layout()
{}

void Mesh::load(Vertex * vertices)
{
	drawn_obj_count = 0;// vertices->get_index_buffer()->get_size();

	vb.load(vertices);
	//ib.load(vertices->get_index_buffer());

	vb.generate_buffers();
	ib.generate_buffers();

	layout.load(GL_FLOAT, 3);
	layout.load(GL_FLOAT, 4);
	va.add_buffer(& vb, & ib, & layout);

	va.unbind();
	vb.unbind();
	ib.unbind();
}

Mesh::~Mesh()
{
	
}

void Mesh::draw()
{
	va.bind();

	glDrawElements(GL_TRIANGLES, drawn_obj_count, GL_UNSIGNED_INT, nullptr);

	va.unbind();
}