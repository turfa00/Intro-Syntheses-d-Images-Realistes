#ifndef __RT_ISICG_SCENE__
#define __RT_ISICG_SCENE__

#include "defines.hpp"
#include "lights/base_light.hpp"
#include "lights/quad_light.hpp"
#include "objects/base_object.hpp"
#include "bvh.hpp"
#include <exception>
#include <map>
#include <vector>

namespace RT_ISICG
{
	using ObjectMap		  = std::map<const std::string, BaseObject *>;
	using ObjectMapPair	  = ObjectMap::value_type;
	using MaterialMap	  = std::map<const std::string, BaseMaterial *>;
	using MaterialMapPair = MaterialMap::value_type;
	using LightList		  = std::vector<BaseLight *>;

	class Scene
	{
	  public:
		Scene();
		~Scene();

		// Hard coded initialization.
		void init();
		void initTP1();
		void initTP2();
		void initTP3();
		void initTP4();
		void initTP5();
		void initTP6();

		// Initialization from file.
		void init( const std::string & p_path ) { throw std::exception( "Not implemented !" ); }

		void loadFileTriangleMesh( const std::string & p_name, const std::string & p_path );

		const LightList & getLights() const { return _lightList; }
		//const QuadLight & getQuadLight() const { return _lightList.at( i ); }

		// Check for nearest intersection between p_tMin and p_tMax : if found fill p_hitRecord.
		bool intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const;
		bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const;

	  public:
		void _addObject( BaseObject * p_object );
		void _addMaterial( BaseMaterial * p_material );
		void _addLight( BaseLight * p_light );

		void _attachMaterialToObject( const std::string & p_materialName, const std::string & p_objectName );

	  private:
		ObjectMap	_objectMap;
		MaterialMap _materialMap;
		LightList	_lightList;
		//BVH			_bvh;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_SCENE__
