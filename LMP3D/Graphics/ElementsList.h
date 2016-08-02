#ifndef ___LMP3D_Graphics_ElementsList_H___
#define ___LMP3D_Graphics_ElementsList_H___

#include "GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			A wrapper around std::map to ease its use with named elements.
		*/
		template< typename T >
		class ElementsList
		{
		private:
			typedef T * ElementPtr;
			typedef std::map< std::string, ElementPtr > ElementMap;
			typedef typename ElementMap::iterator Iterator;
			typedef typename ElementMap::const_iterator ConstIterator;

		public:
			/**
			@brief
				Constructor.
			*/
			inline ElementsList()
			{
			}
			/**
			@brief
				Destructor, deletes all elements.
			*/
			inline ~ElementsList()throw()
			{
				for ( Iterator it = m_elements.begin(); it != m_elements.end(); ++it )
				{
					delete it->second;
				}
			}
			/**
			@brief
				Adds an element if it is not already in the map.
			@param[in] name
				The element name.
			@return
				The added element, or the existing one.
			*/
			inline ElementPtr addElement( std::string const & name )
			{
				ConstIterator it = m_elements.find( name );

				if ( m_elements.find( name ) == m_elements.end() )
				{
					it = m_elements.insert( std::make_pair( name, new T ) ).first;
				}

				return it->second;
			}
			/**
			@brief
				Removes an element if it is in the map.
			@param[in] name
				The element name.
			*/
			inline void removeElement( std::string const & name )
			{
				Iterator it = m_elements.find( name );

				if ( m_elements.find( name ) != m_elements.end() )
				{
					m_elements.erase( it );
				}
			}
			/**
			@brief
				Gets an element from the map.
			@param[in] name
				The element name.
			@return
				The found element, NULL if not found.
			*/
			inline ElementPtr getElement( std::string const & name )const
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
