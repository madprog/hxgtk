
#include <hxgtk.h>

gboolean active = false;

value hxgtk_init() {
	if (!g_thread_supported ())
		g_thread_init(NULL);
	gtk_init(NULL, NULL);
	return val_null;
}

value hxgtk_run() {
	active = true;
	gtk_main();
	return val_null;
}

value hxgtk_quit() {
	if( active ) {
		active = false;
		gtk_main_quit();
	}
	return val_null;
}

DEFINE_PRIM( hxgtk_init, 0);
DEFINE_PRIM( hxgtk_run, 0);
DEFINE_PRIM( hxgtk_quit, 0);
