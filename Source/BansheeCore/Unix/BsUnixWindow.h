//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "Prerequisites/BsPrerequisitesUtil.h"
#include "Math/BsVector2I.h"
#include <X11/X.h>
#include <X11/Xutil.h>

namespace bs
{
	/** @addtogroup Internal-Utility
	 *  @{
	 */

	/** @addtogroup Platform-Utility-Internal
	 *  @{
	 */

	/**	Descriptor used for creating a platform specific native window. */
	struct WINDOW_DESC
	{
		INT32 x, y;
		UINT32 width, height;
		UINT32 screen;
		String title;
		bool showDecorations;
		bool allowResize;
		bool modal;
		::Window parent;
		XVisualInfo visualInfo;
		SPtr<PixelData> background;
	};

	/**	Represents a X11 window. */
	class BS_UTILITY_EXPORT LinuxWindow
	{
	public:
		LinuxWindow(const WINDOW_DESC& desc);
		~LinuxWindow();

		/**	Returns position of the left-most border of the window, relative to the screen. */
		INT32 getLeft() const;

		/**	Returns position of the top-most border of the window, relative to the screen. */
		INT32 getTop() const;

		/**	Returns width of the window in pixels. */
		UINT32 getWidth() const;

		/**	Returns height of the window in pixels. */
		UINT32 getHeight() const;

		/** Hides the window. */
		void hide();

		/** Shows (unhides) the window. */
		void show();

		/**	Minimizes the window. */
		void minimize();

		/**	Maximizes the window over the entire current screen. */
		void maximize();

		/**	Restores the window to original position and size if it is minimized or maximized. */
		void restore();

		/** Closes the window. Window becomes unusable past this call. */
		void close();

		/**	Change the size of the window. */
		void resize(UINT32 width, UINT32 height);

		/**	Reposition the window. */
		void move(INT32 left, INT32 top);

		/** Sets the icon to display for the window. */
		void setIcon(const SPtr<PixelData>& icon);

		/**	Converts screen position into window local position. */
		Vector2I screenToWindowPos(const Vector2I& screenPos) const;

		/**	Converts window local position to screen position. */
		Vector2I windowToScreenPos(const Vector2I& windowPos) const;

		/**
		 * @name Internal
		 * @{
		 */

		/** Unregisters the window from the manager. Should be called before the window is destroyed. */
		void _cleanUp();

		/**
		 * Sets a portion of the window in which the user can click and drag in order to move the window. This is needed
		 * when window has no title bar, yet you still want to allow the user to drag it by clicking on some specific area
		 * (e.g. a title bar you manually render).
		 *
		 * @param[in]	rect	Area of the window (relative to the window origin in top-left corner) in which the drag
		 * 						operation in allowed.
		 */
		void _setDragZone(const Rect2I& rect);

		/**
		 * Notifies the window that user has started dragging the window using the custom drag zone. Provided coordinates
		 * specify the location of the drag start. They are relative to the window top left origin.
		 */
		bool _dragStart(int32_t x, int32_t y);

		/**
		 * Notifies the window that the user has moved the cursor while dragging the window. The provided coordinates are
		 * relative to the window top left origin.
		 */
		void _dragUpdate(int32_t x, int32_t y);

		/** Notifies the window the user has stopped the window drag operation. */
		void _dragEnd();

		/** Returns the internal X11 window handle. */
		::Window _getXWindow() const;

		/** Toggles between fullscreen and windowed mode. */
		void _setFullscreen(bool fullscreen);

		/** @} */

	private:
		/** Checks if the window is currently maximized. */
		bool isMaximized() const;

		/** Checks if the window is currently minimized (iconified). */
		bool isMinimized();

		/**
		 * Maximizes a window if @p enable is true. If false restores the window to size/position before maximization
		 * occurred.
		 */
		void maximize(bool enable);

		/**
		 * Minimizes a window if @p enable is true. If false restores the window to size/position before minimization
		 * occurred.
		 */
		void minimize(bool enable);

		/**
		 * Shows or hides window decorations. Decorations include window title bar, border and similar. Essentially anything
		 * not part of the main rendering area.
		 */
		void setShowDecorations(bool show);

		/**
		 * Switches the window between modal and normal mode. Modal window prevents input to their parent window until
		 * it is dismissed.
		 */
		void setIsModal(bool modal);

		struct Pimpl;
		Pimpl* m;
	};

	/** @} */
	/** @} */
}

