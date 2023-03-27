#include "bvh.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include "utils/chrono.hpp"

namespace RT_ISICG
{
	void BVH::build( std::vector<TriangleMeshGeometry> * p_triangles )
	{
		std::cout << "Building BVH..." << std::endl;
		if ( p_triangles == nullptr || p_triangles->empty() )
		{
			throw std::exception( "BVH::build() error: no triangle provided" );
		}
		_triangles = p_triangles;

		Chrono chr;
		chr.start();

		/// TODO

		chr.stop();

		std::cout << "[DONE]: " << chr.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		/// TODO
		Vec3f rayOrigin	   = p_ray.getOrigin();
		Vec3f rayDirection = p_ray.getDirection();
		Vec3f tMin		   = ( _root->_aabb.getMin() - rayOrigin ) / rayDirection;
		Vec3f tMax		   = ( _root->_aabb.getMax() - rayOrigin ) / rayDirection;
		Vec3f t1		   = glm::min( tMin, tMax );
		Vec3f t2		   = max( tMin, tMax );
		float tNear		   = glm::max( glm::max( t1.x, t1.y ), t1.z );
		float tFar		   = glm::min( glm::min( t2.x, t2.y ), t2.z );

		if ( tNear <= tFar ) { return true; }
		return false;
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		Vec3f rayOrigin	   = p_ray.getOrigin();
		Vec3f rayDirection = p_ray.getDirection();
		Vec3f tMin		   = ( _root->_aabb.getMin() - rayOrigin ) / rayDirection;
		Vec3f tMax		   = ( _root->_aabb.getMax() - rayOrigin ) / rayDirection;
		Vec3f t1		   = glm::min( tMin, tMax );
		Vec3f t2		   = max( tMin, tMax );
		float tNear		   = glm::max( glm::max( t1.x, t1.y ), t1.z );
		float tFar		   = glm::min( glm::min( t2.x, t2.y ), t2.z );

		if ( tNear <= tFar ) { return true; }
		return false;
	}

	void BVH::_buildRec( BVHNode *			p_node,
						 const unsigned int p_firstTriangleId,
						 const unsigned int p_lastTriangleId,
						 const unsigned int p_depth )
	{
		for (int i = p_firstTriangleId; i < p_lastTriangleId; i++) {
			TriangleMeshGeometry triangle = _triangles->at( i );
			std::vector<Vec3f>	 vertices = triangle.getVertices();
			for (int j = 0; j <= 3; j++) {
				p_node->_aabb.extend( vertices.at( j ) );
			}
		}
		int depth = p_depth + 1;
		if (depth <= _maxDepth) { 
			int axePartition = p_node->_aabb.largestAxis();
			Vec3f milieu		 = p_node->_aabb.centroid();
			int	  idPartition	   = 0;
			_buildRec( p_node->_left, p_firstTriangleId, idPartition, depth );
			_buildRec( p_node->_right, p_firstTriangleId, p_lastTriangleId, depth );
		}
		/// TODO
	}

	bool BVH::_intersectRec( const BVHNode * p_node,
							 const Ray &	 p_ray,
							 const float	 p_tMin,
							 const float	 p_tMax,
							 HitRecord &	 p_hitRecord ) const
	{
		/// TODO
		return false;
	}
	bool BVH::_intersectAnyRec( const BVHNode * p_node,
								const Ray &		p_ray,
								const float		p_tMin,
								const float		p_tMax ) const
	{
		/// TODO
		return false;
	}
} // namespace RT_ISICG
