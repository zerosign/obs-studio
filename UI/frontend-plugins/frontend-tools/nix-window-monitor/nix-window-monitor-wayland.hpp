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
// Gnome should use dbus call to
//
// https://gitlab.gnome.org/GNOME/gnome-shell/-/blob/master/data/dbus-interfaces/org.gnome.Shell.Introspect.xml#L37-59
//
// In gnome we could call GetWindows introspections then filter the window that
// has focus. The lifecycle of dbus connection are the same as the lifecycle of this
// object.
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
