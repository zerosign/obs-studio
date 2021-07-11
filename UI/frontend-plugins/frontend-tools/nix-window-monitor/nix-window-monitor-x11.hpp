#include "nix-window-monitor.hpp"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted

class X11WindowMonitor : NixWindowMonitor {
public:
	X11WindowMonitor();
	~X11WindowMonitor();

	void currentWindowTitle(const string &title);
	void windowTitles(const vector<string> &titles);

private:
	bool ewmhIsSupported(const Display *display);
	std::string getWindowTitle(const Display *display);
	std::vector<Window> getTopLevelWindows(const Display *display, size_t idx);

	Display *_display = 0;
};
