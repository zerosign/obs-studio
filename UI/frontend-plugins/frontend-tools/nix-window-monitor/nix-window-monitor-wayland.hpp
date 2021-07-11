#include "nix-window-monitor.hpp"

#ifdef ENABLE_WAYLAND
class WlrWindowMonitor : NixWindowMonitor {
public:
	WlrWindowMonitor();
	~WlrWindowMonitor();

	void currentWindowTitle(const string &title);
	void windowTitles(const vector<string> &titles);
};

#ifdef HAVE_DBUS
class GnomeWindowMonitor : NixWindowMonitor {
public:
	GnomeWindowMonitor();
	~GnomeWindowMonitor();

	void currentWindowTitle(const string &title);
	void windowTitles(const vector<string> &titles);
};

class PlasmaWindowMonitor : NixWindowMonitor {
public:
	PlasmaWindowMonitor();
	~PlasmaWindowMonitor();

	void currentWindowTitle(const string &title);
	void windowTitles(const vector<string> &titles);
};
#endif
#endif
