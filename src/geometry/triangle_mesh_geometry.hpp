#ifndef __RT_ISICG_TRIANGLE_GEOMETRY__
#define __RT_ISICG_TRIANGLE_GEOMETRY__

#include "base_geometry.hpp"

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

		inline const Vec3f & getFaceNormal() const { 
			Vec3f n0	= _refMesh->_normals[ _v0 ];
			Vec3f n1	= _refMesh->_normals[ _v1 ];
			Vec3f n2	= _refMesh->_normals[ _v2 ];
			_faceNormal = ( 1 - _u - _v ) * n0 + _u * n1 + _v * n2;
			return _faceNormal; 
		}

	  private:
		MeshTriangle * _refMesh;
		union
		{
			struct
			{
				unsigned int _v0, _v1, _v2;
				float _u, _v;
			};
			unsigned int _v[ 3 ] = { 0, 0, 0 };
		};
		Vec3f _faceNormal;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_TRIANGLE_GEOMETRY__
