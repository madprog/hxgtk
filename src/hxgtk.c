
#include <hxgtk.h>
#include <glib.h>
#include <locale.h>
#include <neko.h>
#include <neko_vm.h>

typedef struct {
	int init_done;
	pthread_t tid;
	pthread_mutex_t lock;
} ui_data;

static ui_data data = { 0 };

static gint onSyncCall( gpointer data ) {
	value *r = (value*)data;
	value f = *r;
	free_root(r);
	val_call0(f);
	return FALSE;
}

DEFINE_ENTRY_POINT(ui_main);

void ui_main() {
	if (data.init_done)
		return;
	data.init_done = 1;
	if (!g_thread_supported ()) //?
		g_thread_init(NULL);
	gdk_threads_init();
	gtk_init(NULL, NULL);
	setlocale(LC_NUMERIC, "POSIX");
	data.tid = pthread_self();
	pthread_mutex_init(&data.lock, NULL);
}

static value hxgtk_is_main() {
	return alloc_bool( pthread_equal( data.tid, pthread_self() ) );
}

static value hxgtk_main() {
	if (!val_bool(hxgtk_is_main()))
		neko_error();
	gtk_main();
	return val_null;
}

static value hxgtk_quit() {
	if (!val_bool(hxgtk_is_main()))
		neko_error();
	gtk_main_quit();
	return val_null;
}

static value hxgtk_sync(value f) {
	value *r;
	val_check_function(f, 0);
	r = alloc_root(1);
	*r = f;
	pthread_mutex_lock(&data.lock);
	gtk_timeout_add(0, onSyncCall, (gpointer) r);
	pthread_mutex_unlock(&data.lock);
	return val_null;
}

DEFINE_PRIM(hxgtk_is_main, 0);
DEFINE_PRIM(hxgtk_main, 0);
DEFINE_PRIM(hxgtk_quit, 0);
DEFINE_PRIM(hxgtk_sync, 1);
