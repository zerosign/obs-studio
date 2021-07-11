#ifdef ENABLE_WAYLAND
#ifdef HAVE_DBUS

#include "nix-window-monitor-wayland.hpp"

GnomeWindowMonitor::GnomeWindowMonitor() {
	GError *error = NULL;

	this->_connection = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);
	g_assert_no_error(error);
	g_assert_nonnull(this->_connection);

	// TODO: this can't be done, since it only allowed for
	//       internal usage this dbus method calls
	//
	// Thus, we need to use org.gnome.Shell.Eval
	//
	// global.get_window_actors().filter(a=>a.meta_window.has_focus()===true)[0]?.get_meta_window()?.get_wm_class()
	//
	this->_proxy = g_dbus_proxy_new_sync(this->_connection,
					     G_DBUS_PROXY_FLAGS_NONE,
					     NULL,
					     "org.gnome.Shell",
					     "/org/gnome/Shell",
					     "org.gnome.Shell",
					     NULL,
					     &error);
	g_assert_no_error(error);
	g_assert_nonnull(proxy);

}

GnomeWindowMonitor::~GnomeWindowMonitor() {
	GError *error = NULL;

	g_object_unref(this->_proxy);
	g_dbus_connection_close_sync(this->_connection, NULL, &error);
	g_assert_no_error(error);
	g_object_unref(this->_connection);
}

void GnomeWindowMonitor::currentWindowTitle(const string &title) {
	GVariant *error;
        GVariant *script = g_variant_new("(s)", "global.get_window_actors().filter(a=>a.meta_window.has_focus()===true)[0]?.get_meta_window()?.get_wm_class()");
	g_assert_nonnull(script);

	result = g_dbus_proxy_call_sync(proxy,
					"Eval",
					script,
					G_DBUS_CALL_FLAGS_NONE,
					-1,
					NULL,
					&error);
	g_assert_no_error(error);
	g_assert_nonnull(result);

	bool ok;
	const gchar *output;

	g_variant_get(result, "(bs)", &ok, &output);

	if(ok) {
		title.assign(output);
	}
}

void GnomeWindowMonitor::windowTitles(const vector<string> &titles) {

	GVariant *result = NULL;
	GVariant *script = g_variant_new("(s)", "global.get_window_actors().map(w=>w.get_meta_window()?.get_wm_class())");


	result = g_dbus_proxy_call_sync(proxy,
					"Eval",
					NULL,
					G_DBUS_CALL_FLAGS_NONE,
					-1,
					NULL,
					&error);

	g_assert_no_error(error);
	g_assert_nonnull(result2);

	gchar *item;

	g_variant_get(result2, "(bs)", &ok, &item);
	g_assert_nonnull(item);

	// TODO: this is too much string operations :')
	if(ok) {
		// WARN: gchar could be in utf8
		string val(item);
		val.erase(0, 1);
		val.erase(val.length()-1, 1);
		// val.erase(std::find(val.begin(), val.end(), '\"'));
		val.erase(std::remove(val.begin(), val.end(), '\"'), val.end());

		istringstream iss(val);
		char delimiter = ',';
		string title;

		while(std::getline(iss, title, delimiter)) {
			titles.push_back(title);
		}

	}
}

#endif
#endif
