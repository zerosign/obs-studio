#include "nix-window-monitor.hpp"
#include <QProcessEnvironment>

//
// This method will create new nix window monitor based on
// value of XDG_SESSION_TYPE & XDG_SESSION_DESKTOP.
//
// Thus window manager or desktop manager need to properly assign
// XDG_SESSION_TYPE & XDG_SESSION_DESKTOP.
//
// NOTE: note that it still need to check at runtime
// whether some requirement (dbus service) exists or not.
//
// returns NULL when it fails
//
static NixWindowMonitor* CreateNixWindowMonitor() {
	NixWindowMonitor* monitor = NULL;

	// check whether current seat is X11 session
	// XDG_SESSION_TYPE
	// XDG_SESSION_DESKTOP

	QProcessEnvironment envs;
	QString session_type;

	envs.value("XDG_SESSION_TYPE", &session_type);

	if(session_type == "x11") {
		monitor = new X11WindowMonitor();
	}
#ifdef ENABLE_WAYLAND
	if(session_type == "wayland") {
		// checks for WLR compatible protocol
		monitor = new WlrWindowMonitor();
	}
#ifdef HAVE_DBUS
	// check for gnome & kde dbus services

	QString session_desktop;

	envs.value("XDG_SESSION_DESKTOP", &session_desktop);

	if(session_desktop == "gnome") {
		// additional checks for Gnome dbus

		monitor = new GnomeWindowMonitor();
	} else if(session_desktop == "plasma") {
		// additional checks for Plasma dbus

		monitor = new PlasmaWindowMonitor();
	}
#endif
#endif
	return monitor;
}
