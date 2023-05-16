#ifndef __IMPLICIT_CSG_OBJECT__
#define __IMPLICIT_CSG_OBJECT__

#include "base_object.hpp"
#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitCSGObject : public ImplicitSurface
	{
	  public:
		ImplicitCSGObject()		  = delete;
		virtual ~ImplicitCSGObject() = default;

		ImplicitCSGObject( const std::string &	 p_name,
						   ImplicitSurface & p_objectA,
						   ImplicitSurface & p_objectB, const char p_operation )
			: ImplicitSurface( p_name )
		{
			_objectA = &p_objectA; 
			_objectB = &p_objectB;
			_operation = p_operation;
			std::cout << "here" << _objectA->_sdf( Vec3f( 1.f ) ) << std::endl;
		}
		// Signed Distance Function
		float _sdf( const Vec3f & p_point ) const
		{
			s = _objectA->_sdf( p_point );
			//return _objectA->_sdf( p_point );
			//return _objectA->_sdf( p_point );
			//float sdf = glm::min( _objectA->_sdf( p_point ), _objectB->_sdf( p_point ) );
			// std::cout << _objectA->getName() << std::endl;
			/* if ( _operation == '+' )
			{
				return glm::min( _objectA->_sdf( p_point ), _objectB->_sdf( p_point ) );
			}
			else if ( _operation == '-' ) { return glm::max( -_objectA->_sdf( p_point ), _objectB->_sdf( p_point ) ); }
			else if ( _operation == '*' ) { return glm::max( _objectA->_sdf( p_point ), _objectB->_sdf( p_point ) ); }
			*/
			return 1.f;
		}
		

	  private:
		ImplicitSurface * _objectA;
		ImplicitSurface * _objectB;
		char			_operation;
		mutable float			s;
		const float		  _minDistance = 1e-4f;
	};
} // namespace RT_ISICG

#endif