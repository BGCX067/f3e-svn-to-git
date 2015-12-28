#ifndef IKeyListener_h__
#define IKeyListener_h__

#include <f3base/Common.h>
#include "KeyEvent.h"

namespace f3
{
	namespace input 
	{

		class DLL IKeyListener
		{
		public:
			virtual bool keyPressed( const KeyEvent &arg ) = 0;
			virtual bool keyReleased( const KeyEvent &arg ) = 0;
		};
	}
}
#endif // IKeyListener_h__
