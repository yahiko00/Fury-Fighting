#ifndef ___LMP3D_Event_H___
#define ___LMP3D_Event_H___

#include "Common.h"

namespace LMP3D
{
	namespace Windows
	{
		typedef enum State
		{
			State_Released,
			State_Pressed,
			State_Held,
		}	State;

		typedef enum Button
		{
			Button_A,
			Button_B,
			Button_C,
			Button_D,
			Button_L1,
			Button_L2,
			Button_R1,
			Button_R2,
			Button_DPadUp,
			Button_DPadDown,
			Button_DPadLeft,
			Button_DPadRight,
			Button_Start,
			Button_Select,
			Button_Count,
			Button_Min = Button_A,
			Button_Max = Button_Count - 1
		}	Button;

		struct Event
		{
			Event();

			bool quit;
			State buttonState[Button_Count];
			Position leftAxisState;
			Position rightAxisState;
		};
	}
}

#endif
