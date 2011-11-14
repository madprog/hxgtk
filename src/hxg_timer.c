
#include <hxg.h>
#include <hxgtk.h>
#include <glib.h>

//#define val_timer(x) ((timer*)val_data(x))

struct _timer {
	gint id;
	gint ms;
	value *cb;
};

DEFINE_KIND(k_timer);

gint _cb(gpointer data) {
	//value ret = val_call1(*function_storage,alloc_string("Hello"));
	//timer *t = data;
	//val_call0( *t->cb );
	value *cb = data;
	val_call0( *cb);
	return TRUE;
}

static value hxg_timer_new( value _ms, value cb ) {
	val_check(_ms,int);
	gint ms = val_int(_ms);
	timer *t;
	t = malloc(sizeof(struct _timer));
	t->ms = ms;
	t->cb = alloc_root(1);
	*t->cb = cb;
	//gtk_timeout_add( ms, _cb, (gpointer)t );
	//gtk_timeout_add( ms, _cb, (gpointer)t->cb );
	gint id = gtk_timeout_add( ms, _cb, (gpointer)t->cb );
	t->id = id;
	return alloc_abstract(k_timer, t);
}

static value hxg_timer_stop(value t) {
	timer *timer = val_data(t);
	//timer * timer = val_timer(t);
	gint id = timer->id;
	gtk_timeout_remove(id);
	//gtk_timeout_destroy(id);
	return val_null;
}

/*
static value hxg_timer_continue(value t) {
	g_timer_continue(val_data(t));
	return val_null;
}

static value hxg_timer_elapsed(value t, value microseconds) {
	g_timer_elapsed(val_data(t));
	return val_null;
}

static value hxg_timer_reset(value t) {
	g_timer_reset(val_data(t));
	return val_null;
}

static value hxg_timer_destroy(value t) {
	g_timer_destroy(val_data(t));
	return val_null;
}
*/

DEFINE_PRIM( hxg_timer_new, 2);
//DEFINE_PRIM( hxg_timer_start, 1);
DEFINE_PRIM( hxg_timer_stop, 1);
/*
DEFINE_PRIM( hxg_timer_continue, 1);
DEFINE_PRIM( hxg_timer_elapsed, 2);
DEFINE_PRIM( hxg_timer_reset, 1);
DEFINE_PRIM( hxg_timer_destroy, 1);
*/
