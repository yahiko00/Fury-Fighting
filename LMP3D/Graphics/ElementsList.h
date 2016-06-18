#ifndef ___LMP3D_Graphics_ElementsList_H___
#define ___LMP3D_Graphics_ElementsList_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		template< typename T >
		class ElementsList
		{
		private:
			typedef T * ElementPtr;
			typedef std::map< std::string, ElementPtr > ElementMap;
			typedef typename ElementMap::iterator Iterator;
			typedef typename ElementMap::const_iterator ConstIterator;

		public:
			ElementsList()
			{
			}

			~ElementsList()throw()
			{
				for ( Iterator it = m_elements.begin(); it != m_elements.end(); ++it )
				{
					delete it->second;
				}
			}

			ElementPtr addElement( std::string const & name )
			{
				ConstIterator it = m_elements.find( name );

				if ( m_elements.find( name ) == m_elements.end() )
				{
					it = m_elements.insert( std::make_pair( name, new T ) ).first;
				}

				return it->second;
			}

			ElementPtr getElement( std::string const & name )const
			{
				ElementPtr ret = NULL;
				ConstIterator it = m_elements.find( name );

				if ( it != m_elements.end() )
				{
					ret = it->second;
				}

				return ret;
			}

		private:
			ElementMap m_elements;
		};
	}
}

#endif
