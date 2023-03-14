#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const unsigned int p_v0,
												const unsigned int p_v1,
												const unsigned int p_v2,
												MeshTriangle *	   p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],
												  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );
	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];
		
		//_faceNormal = ( 1 - u - v ) * n0 + u * n1 + v * n2;
		//_faceNormal = ( 1 - u - v ) * v0 + u * v1 + v * v2;
		const float epsilon = 0.0000001;
		Vec3f edge1, edge2, h, s, q;
		float		a, f, u, v;
		edge1 = v1 - v0;
		edge2 = v2 - v0;
		h = glm::cross(d, edge2);
		a = glm::dot(edge1, h);

		if (a > -epsilon && a < epsilon) { return false; // Le rayon est parallèle au triangle.
		}

		f = 1.f / a;
		s = o - v0;
		u = f * glm::dot( s, h );
		_u = u;
		if (u < 0.f || u > 1.f) { return false;
		}
		q = glm::cross( s, edge1 );
		v = f * glm::dot( d, q );
		_v = v;
		if (v < 0.f || u + v > 1.f) { return false;
		}

		float t = f * glm::dot( edge2, q );
		p_t		= t;
		if (t > epsilon) { // Intersection avec le rayon
			return true;
		}
		//On a bien une intersection de droite mais pas de rayon
		return false;
	}

} // namespace RT_ISICG
