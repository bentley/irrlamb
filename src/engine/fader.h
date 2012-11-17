/*************************************************************************************
*	irrlamb - http://irrlamb.googlecode.com
*	Copyright (C) 2011  Alan Witkowski
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************************/
#ifndef FADER_H
#define FADER_H

// Libraries
#include "singleton.h"
#include <irrlicht.h>

// Classes
class FaderClass {

	public:

		enum StateType {
			STATE_NONE,
			STATE_WAITFRAME,
			STATE_FADING,
		};

		int Init();
		int Close();

		void Update(float FrameTime);
		void Draw();

		bool IsDoneFading() { return State == STATE_NONE; }
		void Start(float Speed);

	private:

		// Update
		float TimeStep, TimeStepAccumulator;

		// State
		int State;
		float Fade, Speed;

		// Resources
		irr::video::ITexture *FadeImage;
};

// Singletons
typedef SingletonClass<FaderClass> Fader;

#endif