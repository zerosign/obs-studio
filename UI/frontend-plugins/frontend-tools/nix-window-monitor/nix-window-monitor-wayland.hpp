#include "nix-window-monitor.hpp"

#ifdef ENABLE_WAYLAND
#ifdef ENABLE_WLR

#include "wayland-client.h"
#include "protocols/wlr-foreign-toplevel-management.h"

// TODO: NEED to add wayland-scanner into pipeline
//
// wayland-scanner -s client-header unstable/wlr-foreign-toplevel-management-unstable-v1.xml

class WlrWindowMonitor : NixWindowMonitor {
public:
	WlrWindowMonitor();
	~WlrWindowMonitor();

	void currentWindowTitle(const string &title);
	void windowTitles(const vector<string> &titles);

private:

};

#endif

#ifdef HAVE_DBUS

#include <gio/gio.h>


// Gnome Window Monitor implementation.
//
// This use org.gnome.Shell.Eval to fetch current window title & all window titles
//
class GnomeWindowMonitor : NixWindowMonitor {
public:
	GnomeWindowMonitor();
	~GnomeWindowMonitor();

	void currentWindowTitle(const string &title);
	void windowTitles(const vector<string> &titles);

private:
	GDBusConnection *_connection;
	GDBuxProxy *_proxy;
};

class PlasmaWindowMonitor : NixWindowMonitor {
public:
	PlasmaWindowMonitor();
	~PlasmaWindowMonitor();

	void currentWindowTitle(const string &title);
	void windowTitles(const vector<string> &titles);

private:
	GDBusConnection *_connection;
	GDBuxProx *_proxy;
};
#endif
#endif
