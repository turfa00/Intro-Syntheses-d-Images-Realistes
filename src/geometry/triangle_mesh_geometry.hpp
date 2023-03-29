#ifndef __RT_ISICG_TRIANGLE_GEOMETRY__
#define __RT_ISICG_TRIANGLE_GEOMETRY__

#include "base_geometry.hpp"
#include "aabb.hpp"
#include <iostream>
#include <vector>
namespace RT_ISICG
{
	class MeshTriangle;

	class TriangleMeshGeometry : public BaseGeometry
	{
	  public:
		TriangleMeshGeometry()			= delete;
		virtual ~TriangleMeshGeometry() = default;

		TriangleMeshGeometry( const unsigned int p_v0,
							  const unsigned int p_v1,
							  const unsigned int p_v2,
							  MeshTriangle *	 p_refMesh );
		bool intersect( const Ray & p_ray, float & p_t ) const;

		inline const Vec3f & getFaceNormal() const{ 
			return _faceNormal; 
		}

		const AABB getAABB();
		/* Vec3f & updateNormal( float u, float v ) const
		{
			Vec3f & v0 = _refMesh->_vertices[ _v0 ];
			Vec3f & v1 = _refMesh->_vertices[ _v1 ];
			Vec3f & v2 = _refMesh->_vertices[ _v2 ];

			Vec3f n0	= _refMesh->_normals[ _v0 ];
			Vec3f n1	= _refMesh->_normals[ _v1 ];
			Vec3f n2	= _refMesh->_normals[ _v2 ];
			_faceNormal = ( 1 - u - v ) * n0 + u * n1 + v * n2;
			return _faceNormal;
		}*/

	  private:
		MeshTriangle * _refMesh;
		union
		{
			struct
			{
				unsigned int _v0, _v1, _v2;
			};
			unsigned int _v[ 3 ] = { 0, 0, 0 };
		};
		Vec3f _faceNormal;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_TRIANGLE_GEOMETRY__
