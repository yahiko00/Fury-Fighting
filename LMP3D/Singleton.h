#ifndef ___LMP3D_Singleton_H___
#define ___LMP3D_Singleton_H___

namespace LMP3D
{
	/**
	@brief
		Simple singleton class.

	@remarks
		In classes that derive from Singleton, you should create two functions:
		- A static initialisation function that will initialise the singleton value, through doGetSingleton()
			(the main reason why it returns a reference to the pointer)
		- A static cleanup function, that will delete the singleton value, still through doGetSingleton()
		It is also advised to make the derived classes constructor and destructor private
		(or at least protected) but not public!
	*/
	template< typename T >
	class Singleton
	{
	protected:
		inline Singleton()
		{
			assert( !doGetSingleton() );
		}

		inline ~Singleton()
		{
			assert( doGetSingleton() );
		}

		static inline T *& doGetSingleton()
		{
			static T * singleton = NULL;
			return singleton;
		}

	public:
		static inline T * getSingleton()
		{
			return doGetSingleton();
		}
	};
}

#endif
