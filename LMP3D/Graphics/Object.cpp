#include "Object.h"

#include "Material.h"
#include "Mesh.h"

namespace LMP3D
{
	namespace Graphics
	{
		Object::Object( MeshPtr mesh )
			: m_mesh( mesh )
			, m_angle( 0.0f )
		{
		}

		Object::~Object()
		{
			delete m_mesh;
		}

		void Object::draw()
		{
			glPushMatrix();
			glRotatef( m_angle, m_axis.x, m_axis.y, m_axis.z );
			glTranslatef( m_position.x, m_position.y, m_position.z );
			m_mesh->draw();
			glPopMatrix();
		}
	}
}
