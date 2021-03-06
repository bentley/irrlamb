/******************************************************************************
* irrlamb - https://github.com/jazztickets/irrlamb
* Copyright (C) 2015  Alan Witkowski
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/
#pragma once
#include <IGUIStaticText.h>
#include <string>

// Forward Declarations
class _AudioSource;

namespace irr {
	namespace gui {
		class CGUITTFont;
	}
}

// Structures
struct _TutorialText {
	irr::gui::IGUIStaticText *Text;
	float DeleteTime;
	int MessageX;
	int MessageY;
};

const int MGUIET_EMPTY = irr::gui::EGUIET_COUNT+1;

// Empty gui element, good for being a parent
class CGUIEmptyElement : public irr::gui::IGUIElement {

	public:

		CGUIEmptyElement(irr::gui::IGUIEnvironment *Environment, irr::gui::IGUIElement *Parent);
		irr::gui::IGUIEnvironment *GetEnvironment() { return Environment; }
		virtual const irr::c8 *getTypeName() const { return "empty"; }
		virtual bool isPointInside(const irr::core::position2d<irr::s32> &Point) const { return false; }
		virtual bool bringToFront(IGUIElement *Element) {
			bool Result = irr::gui::IGUIElement::bringToFront(Element);
			if(Parent)
				Parent->bringToFront(this);
			return Result;
		}
};

// Classes
class _Interface {

	friend class _PlayState;

	public:

		enum SkinType {
			SKIN_MENU,
			SKIN_GAME,
		};

		enum FontType {
			FONT_SMALL,
			FONT_MEDIUM,
			FONT_LARGE,
			FONT_BUTTON,
			FONT_COUNT,
		};

		enum AlignType {
			ALIGN_LEFT,
			ALIGN_CENTER,
			ALIGN_RIGHT,
		};

		enum ImageType {
			IMAGE_MOUSECURSOR,
			IMAGE_FADE,
			IMAGE_BUTTON_SMALL,
			IMAGE_BUTTON_MEDIUM,
			IMAGE_BUTTON_BIG,
			IMAGE_TEXTBOXSHEET0,
			IMAGE_TEXTBOXSHEET1,
			IMAGE_TEXTBOXSHEET2,
			IMAGE_PAUSE,
			IMAGE_REWIND,
			IMAGE_FASTFORWARD,
			IMAGE_FASTREVERSE,
			IMAGE_INCREASE,
			IMAGE_DECREASE,
			IMAGE_SELECTED,
			IMAGE_BUTTON_UP,
			IMAGE_BUTTON_DOWN,
			IMAGE_COUNT,
		};

		enum SoundType {
			SOUND_CONFIRM,
			SOUND_COUNT,
		};

		int Init();
		int Close();
		void Update(float FrameTime);
		void Draw(float Time, bool FirstLoad);
		void Clear();
		void ChangeSkin(SkinType Type);

		void SetTutorialText(const std::string &Text, float Length);
		void ConvertSecondsToString(float Time, char *String, const char *Prefix="");

		irr::core::recti GetCenteredRect(int PositionX, int PositionY, int Width, int Height);
		irr::core::recti GetRightRect(int PositionX, int PositionY, int Width, int Height);
		irr::core::recti GetRect(int PositionX, int PositionY, int Width, int Height);

		void FadeScreen(float Amount);
		void RenderText(const char *Text, int PositionX, int PositionY, AlignType AlignType, FontType FontType=FONT_SMALL, const irr::video::SColor &Color=irr::video::SColor(255, 255, 255, 255));
		void DrawImage(ImageType Type, int PositionX, int PositionY, int Width, int Height, const irr::video::SColor &Color=irr::video::SColor(255, 255, 255, 255));
		void DrawTextBox(int PositionX, int PositionY, int Width, int Height, const irr::video::SColor &Color=irr::video::SColor(255, 255, 255, 255));

		void LoadSounds();
		void UnloadSounds();
		void PlaySound(SoundType Sound);

		// Attributes
		int CenterX;
		int CenterY;

		irr::gui::CGUITTFont *Fonts[FONT_COUNT];
		irr::video::ITexture *Images[IMAGE_COUNT];

	private:

		_TutorialText TutorialText;
		bool DrawHUD;
		float Timer;

		_AudioSource *Sounds[SOUND_COUNT];

};

// Singletons
extern _Interface Interface;
