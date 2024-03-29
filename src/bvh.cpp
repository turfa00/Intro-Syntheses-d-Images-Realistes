#include "bvh.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include "utils/chrono.hpp"
#include <algorithm>
#include <iterator>
#include <vector>
#include <forward_list>

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

		_root = new BVHNode();
		Chrono chr;
		chr.start();
		_buildRec( _root, 0, _triangles->size(), 0 );
		chr.stop();

		std::cout << "[DONE]: " << chr.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		Vec3f rayOrigin	   = p_ray.getOrigin();
		Vec3f rayDirection = p_ray.getDirection();
		Vec3f tMin		   = ( _root->_aabb.getMin() - rayOrigin ) / rayDirection;
		Vec3f tMax		   = ( _root->_aabb.getMax() - rayOrigin ) / rayDirection;
		Vec3f t1		   = glm::min( tMin, tMax );
		Vec3f t2		   = glm::max( tMin, tMax );
		float tNear		   = glm::max( glm::max( t1.x, t1.y ), t1.z );
		float tFar		   = glm::min( glm::min( t2.x, t2.y ), t2.z );

		if ( tNear <= tFar ) { return true; }
		return false;
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
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
			p_node->_aabb.extend( _triangles->at(i).getAABB() );
		}
		p_node->_firstTriangleId = p_firstTriangleId;
		p_node->_lastTriangleId	 = p_lastTriangleId;

		if ((p_depth < _maxDepth) && (p_lastTriangleId - p_firstTriangleId < _maxTrianglesPerLeaf)) { 
			const int largestAxis = static_cast<const unsigned int>( p_node->_aabb.largestAxis() );
			const float		 milieu		 = p_node->_aabb.centroid()[ largestAxis ];
			std::vector<TriangleMeshGeometry>::iterator idPartition
				= std::partition( _triangles->begin() + p_firstTriangleId,
								  _triangles->begin() + p_lastTriangleId,
								  [ largestAxis, milieu ]( TriangleMeshGeometry & a )
								  { return a.getAABB().centroid()[ largestAxis ] < milieu; } );
			p_node->_left = new BVHNode();
			p_node->_right = new BVHNode();

			int idPartition1 = std::distance( _triangles->begin(), idPartition );

			_buildRec( p_node->_left, p_firstTriangleId, idPartition1, p_node->_depth + 1 );
			_buildRec( p_node->_right, idPartition1, p_lastTriangleId, p_node->_depth + 1 );
		}
		else { 
			p_node->_left = nullptr;
			p_node->_right = nullptr;
		}
	}

	bool BVH::_intersectRec( const BVHNode * p_node,
							 const Ray &	 p_ray,
							 const float	 p_tMin,
							 const float	 p_tMax,
							 HitRecord &	 p_hitRecord ) const
	{
		if (p_node->_aabb.intersect(p_ray, p_tMin, p_tMax)) { 
			return true;
		}
		if ( p_node->_left != nullptr )
			_intersectRec( p_node->_left, p_ray, p_tMin, p_tMax, p_hitRecord);
		if ( p_node->_right != nullptr )
			_intersectRec( p_node->_right, p_ray, p_tMin, p_tMax, p_hitRecord);
		return false;
	}
	bool BVH::_intersectAnyRec( const BVHNode * p_node,
								const Ray &		p_ray,
								const float		p_tMin,
								const float		p_tMax ) const
	{
		if ( p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) ) { return true; }
		if ( p_node->_left != nullptr )
			_intersectAnyRec( p_node->_left, p_ray, p_tMin, p_tMax );
		if ( p_node->_right != nullptr )
			_intersectAnyRec( p_node->_right, p_ray, p_tMin, p_tMax );
		return false;
	}
} // namespace RT_ISICG
