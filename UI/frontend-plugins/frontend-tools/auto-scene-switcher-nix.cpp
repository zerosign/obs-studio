#include <util/platform.h>
#include "auto-scene-switcher.hpp"
#include "nix-window-monitor/nix-window-monitor.hpp"

static NixWindowMonitor * monitor = NULL;

NixWindowMonitor * getWindowMonitor() {
	if(monitor != NULL) {
		return monitor;
	}

	monitor = CreateNixWindowMonitor();

	return monitor;
}

void CleanupSceneSwitcher() {
	if(monitor != NULL) {
		delete monitor;
	}
}

void GetWindowList(vector<string> &windows) {
	NixWindowMonitor *local_monitor = getWindowMonitor();

	if(local_monitor == NULL) {
		return;
	}

	local_monitor->windowTitles(windows);

}

void GetCurrentWindowTitle(string &title) {
	NixWindowMonitor *local_monitor = getWindowMonitor();

	if(local_monitor == NULL) {
		return;
	}

	local_monitor->currentWindowTitle(title);
}
