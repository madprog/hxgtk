
#include <hxgtk.h>

DEFINE_KIND(k_window);

/*
enum WindowEvent {
	WE_DESTROY,
	WE_CLOSE,
	WE_MINIMIZE,
	WE_MAXIMIZE,
	WE_RIGHTCLICK,
	WE_FILESDROPPED, // data = string_list
	WE_RESTORE
};
*/

//typedef int (*on_event)( window *w, enum WindowEvent e, void* );

struct _window {
	int temp;
	//GtkWidget *gwindow;
	//value cb;
	//GtkWidget *xt_bin;
	//NPWindow npwin;
	//void *flash;
	//on_event evt;
	//on_npevent npevent;
	//private_data *p;
	//enum WindowFlags flags;
};

//static int next_win_id = 0;
//static int num_windows_created = 0;
//value *function_storage = NULL;

//TODO hxgtk_window_new
value hxgtk_window_constructor(value title, value width, value height ) {

	val_check( title, string);
	val_check( width, int);
	val_check( height, int);

	GtkWidget* win;
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(win), val_string(title));
	gtk_window_set_default_size(GTK_WINDOW(win), val_int(width),
				val_int(height));
	//gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
	//	gtk_window_set_icon(GTK_WINDOW(win), create_pixbuf("icon_16.png"));
	//gtk_window_set_decorated(true);
	//gtk_window_set_deletable
	gtk_widget_show_all(win);

	//next_win_id++;

	//window* w = malloc(sizeof(struct _window));
	//w->temp = 23;
	//w->cb = *function_storage;
	//w->evt = function_storage;

	//g_signal_connect(win, "delete_event", G_CALLBACK(delete_event), NULL );
	//g_signal_connect(win, "destroy", G_CALLBACK(cb_destroy), w );
	//g_signal_connect(G_OBJECT(win), "expose-event", G_CALLBACK(expose_cb), sink); // brought to the foreground callback
	//g_signal_connect(G_OBJECT(win), "key-press-event", G_CALLBACK(key_press_event_cb), sink);

	value kwin = alloc_abstract(k_window, win);

	return kwin;
}


static void on_destroy(GtkWidget *widget, gpointer data) {
	//value f = data;
	val_call0(data);
}
static value hxgtk_window_on_destroy( value win, value f ) {
	//int i = 23;
	//g_signal_connect( val_data(win), "destroy", GTK_SIGNAL_FUNC(cb_destroy), GINT_TO_POINTER(i) );
	g_signal_connect( val_data(win), "destroy", GTK_SIGNAL_FUNC(on_destroy), f );
	return val_null;
}

DEFINE_PRIM(hxgtk_window_on_destroy,2);



/*
static value hxgtk_window_show(value win) {
	gtk_widget_show_all(val_data(win));
	return val_null;
}
*/
static value hxgtk_window_destroy(value win) {
	gtk_widget_destroy(val_data(win));
	return val_null;
}



static value hxgtk_window_get_title(value win) {
	return alloc_string(gtk_window_get_title(val_data(win)));
}
static value hxgtk_window_set_title(value win, value t) {
	gtk_window_set_title(val_data(win), val_string(t));
	return t;
}

static value hxgtk_window_get_size(value win) {
	value o = alloc_object(NULL);
	gint _w;
	gint _h;
	gtk_window_get_size(val_data(win),&_w,&_h);
	alloc_field(o, val_id("x"), alloc_int(_w));
	alloc_field(o, val_id("y"), alloc_int(_h));
	return o;
}

static value hxgtk_window_get_resizeable(value win) {
	return alloc_bool(gtk_window_get_resizable(val_data(win)));
}
static value hxgtk_window_set_resizeable(value win, value t) {
	gtk_window_set_resizable(val_data(win),val_bool(t));
	return t;
}

static value hxgtk_window_get_modal(value win) {
	return alloc_bool(gtk_window_get_modal(val_data(win)));
}
static value hxgtk_window_set_modal(value win, value v) {
	gtk_window_set_modal(val_data(win),val_bool(v));
	return v;
}

static value hxgtk_window_get_decorated(value win) {
	return alloc_bool(gtk_window_get_decorated(val_data(win)));
}
static value hxgtk_window_set_decorated(value win, value v) {
	gtk_window_set_decorated(val_data(win),val_bool(v));
	return v;
}

static value hxgtk_window_get_deleteable(value win) {
	return alloc_bool(gtk_window_get_deletable(val_data(win)));
}
static value hxgtk_window_set_deleteable(value win, value v) {
	gtk_window_set_deletable(val_data(win),val_bool(v));
	return v;
}

static value hxgtk_window_get_role(value win) {
	return alloc_string(gtk_window_get_role(val_data(win)));
}
static value hxgtk_window_set_role(value win, value v) {
	gtk_window_set_role(val_data(win),val_string(v));
	return v;
}

static value hxgtk_window_get_window_type(value win) {
	GtkWindowType t = gtk_window_get_window_type(val_data(win));
	int i = t;
	return alloc_int(i);
}

static value _get_default_size( GtkWindow *win ) {
	value o = alloc_object(NULL);
	gint _w;
	gint _h;
	gtk_window_get_default_size(win, &_w, &_h );
	alloc_field(o, val_id("x"), alloc_int(_w));
	alloc_field(o, val_id("y"), alloc_int(_h));
	return o;
}
static value hxgtk_window_get_default_size(value win) {
	return _get_default_size(val_data(win));
}
static value hxgtk_window_set_default_size(value win, value w,value h) {
	GtkWindow *_win = val_data(win);
	gtk_window_set_default_size(_win,val_int(w),val_int(h));
	return _get_default_size(_win);
}

static value hxgtk_window_get_position(value w) {
	gint _w, _h;
	value o = alloc_object(NULL);
	gtk_window_get_position(val_data(w), &_w, &_h );
	alloc_field(o, val_id("x"), alloc_int(_w));
	alloc_field(o, val_id("y"), alloc_int(_h));
	return o;
}
static value hxgtk_window_set_position(value w, value p ) {
	GtkWindowPosition pos = GTK_WIN_POS_NONE;
	switch(val_int(p)) {
	//case 0 :
	//	pos = GTK_WIN_POS_NONE;
	//	break;
	case 1 :
		pos = GTK_WIN_POS_CENTER;
		break;
	case 2 :
		pos = GTK_WIN_POS_MOUSE;
		break;
	case 3 :
		pos = GTK_WIN_POS_CENTER_ALWAYS;
		break;
	case 4 :
		pos = GTK_WIN_POS_CENTER_ON_PARENT;
		break;
	}
	gtk_window_set_position( val_data(w), pos );
	return val_null;
}

static value hxgtk_window_get_destroy_with_parent(value win) {
	return alloc_bool(gtk_window_get_destroy_with_parent(val_data(win)));
}
static value hxgtk_window_set_destroy_with_parent(value win, value v) {
	gtk_window_set_destroy_with_parent(val_data(win),val_bool(v));
	return v;
}

static value hxgtk_window_is_active(value win) {
	return alloc_bool(gtk_window_is_active(val_data(win)));
}

static value hxgtk_window_has_toplevel_focus(value win) {
	return alloc_bool(gtk_window_has_toplevel_focus(val_data(win)));
}

static value hxgtk_window_present(value win) {
	gtk_window_present(val_data(win));
	return val_null;
}

static value hxgtk_window_present_with_time(value win,value v) {
	gtk_window_present_with_time(val_data(win),val_int(v));
	return val_null;
}

static value hxgtk_window_iconify(value win) {
	gtk_window_iconify(val_data(win));
	return val_null;
}
static value hxgtk_window_deiconify(value win) {
	gtk_window_deiconify(val_data(win));
	return val_null;
}

static value hxgtk_window_stick(value win) {
	gtk_window_stick(val_data(win));
	return val_null;
}
static value hxgtk_window_unstick(value win) {
	gtk_window_unstick(val_data(win));
	return val_null;
}

static value hxgtk_window_maximize(value w) {
	gtk_window_maximize(val_data(w));
	return val_null;
}
static value hxgtk_window_unmaximize(value w) {
	gtk_window_unmaximize(val_data(w));
	return val_null;
}

static value hxgtk_window_fullscreen(value w) {
	gtk_window_fullscreen(val_data(w));
	return val_null;
}
static value hxgtk_window_unfullscreen(value w) {
	gtk_window_unfullscreen(val_data(w));
	return val_null;
}

static value hxgtk_window_set_keep_above(value win, value v) {
	gtk_window_set_keep_above(val_data(win),val_bool(v));
	return val_null;
}
static value hxgtk_window_set_keep_below(value win, value v) {
	gtk_window_set_keep_below(val_data(win),val_bool(v));
	return val_null;
}

static value hxgtk_window_resize(value win, value w, value h) {
	gtk_window_resize(val_data(win), val_int(w), val_int(h));
	return val_null;
}

static value hxgtk_window_get_icon_name(value win) {
	return alloc_string(gtk_window_get_icon_name(val_data(win)));
}
static value hxgtk_window_set_icon_name(value win, value v) {
	gtk_window_set_icon_name(val_data(win), val_string(v) );
	return val_null;
}

static value hxgtk_window_get_opacity(value win) {
	return alloc_float(gtk_window_get_opacity(val_data(win)));
}
static value hxgtk_window_set_opacity(value win, value v) {
	gtk_window_set_opacity(val_data(win), val_float(v) );
	return val_null;
}



DEFINE_PRIM( hxgtk_window_constructor, 3);
////DEFINE_PRIM( hxgtk_window_show, 1);
DEFINE_PRIM( hxgtk_window_destroy, 1);

DEFINE_PRIM( hxgtk_window_get_title, 1);
DEFINE_PRIM( hxgtk_window_set_title, 2);
DEFINE_PRIM( hxgtk_window_get_size, 1);
DEFINE_PRIM( hxgtk_window_get_resizeable, 1);
DEFINE_PRIM( hxgtk_window_set_resizeable, 2);
DEFINE_PRIM( hxgtk_window_get_modal, 1);
DEFINE_PRIM( hxgtk_window_set_modal, 2);
//DEFINE_PRIM( hxgtk_window_get_gravity, 1);
//DEFINE_PRIM( hxgtk_window_set_gravity, 2);
//DEFINE_PRIM( hxgtk_window_get_screen, 1);
//DEFINE_PRIM( hxgtk_window_set_screen, 2);
//DEFINE_PRIM( hxgtk_window_get_focus, 1);
//DEFINE_PRIM( hxgtk_window_set_focus, 2);
DEFINE_PRIM( hxgtk_window_get_decorated, 1);
DEFINE_PRIM( hxgtk_window_set_decorated, 2);
DEFINE_PRIM( hxgtk_window_get_deleteable, 1);
DEFINE_PRIM( hxgtk_window_set_deleteable, 2);
//DEFINE_PRIM( hxgtk_window_get_icon, 1);
//DEFINE_PRIM( hxgtk_window_set_icon, 2);
//DEFINE_PRIM( hxgtk_window_get_type_hint, 1);
//DEFINE_PRIM( hxgtk_window_set_type_hint, 2);
//DEFINE_PRIM( hxgtk_window_get_skip_taskbar_hint, 1);
//DEFINE_PRIM( hxgtk_window_set_skip_taskbar_hint, 2);
//DEFINE_PRIM( hxgtk_window_get_skip_pager_hint, 1);
//DEFINE_PRIM( hxgtk_window_set_skip_pager_hint, 2);
//DEFINE_PRIM( hxgtk_window_get_urgency_hint, 1);
//DEFINE_PRIM( hxgtk_window_set_urgency_hint, 2);
//DEFINE_PRIM( hxgtk_window_get_accept_focus, 1);
//DEFINE_PRIM( hxgtk_window_set_accept_focus, 1);
//DEFINE_PRIM( hxgtk_window_get_focus_on_map, 1);
//DEFINE_PRIM( hxgtk_window_set_focus_on_map, 1);
//DEFINE_PRIM( hxgtk_window_get_start_id, 1);
//DEFINE_PRIM( hxgtk_window_set_start_id, 2);
DEFINE_PRIM( hxgtk_window_get_role, 1);
DEFINE_PRIM( hxgtk_window_set_role, 2);
//DEFINE_PRIM( hxgtk_window_get_group, 1);
DEFINE_PRIM( hxgtk_window_get_window_type, 1);
//DEFINE_PRIM( hxgtk_window_get_default_icon, 1);
//DEFINE_PRIM( hxgtk_window_set_default_icon, 1);
//DEFINE_PRIM( hxgtk_window_get_mnemonics_visible, 1);
//DEFINE_PRIM( hxgtk_window_set_mnemonics_visible, 2);
/////DEFINE_PRIM( hxgtk_window_get_has_resize_grip, 1);
/////DEFINE_PRIM( hxgtk_window_set_has_resize_grip, 2);
////DEFINE_PRIM( hxgtk_window_get_application, 1);
////DEFINE_PRIM( hxgtk_window_set_application, 2);
////DEFINE_PRIM( hxgtk_window_set_wmclass, 2);setPosition
//DEFINE_PRIM( hxgtk_window_add_accel_group, 2);
//DEFINE_PRIM( hxgtk_window_remove_accel_group, 2);
//DEFINE_PRIM( hxgtk_window_activate_focus, 1);
//DEFINE_PRIM( hxgtk_window_activate_default, 1);
DEFINE_PRIM( hxgtk_window_get_default_size, 1);
DEFINE_PRIM( hxgtk_window_set_default_size, 3);
//DEFINE_PRIM( hxgtk_window_set_default_geometry, 3);
//DEFINE_PRIM( hxgtk_window_set_geometry_hints, 4);
DEFINE_PRIM( hxgtk_window_get_position, 1);
DEFINE_PRIM( hxgtk_window_set_position, 2);
//DEFINE_PRIM( hxgtk_window_set_transient_for, 2);
DEFINE_PRIM( hxgtk_window_get_destroy_with_parent, 1);
DEFINE_PRIM( hxgtk_window_set_destroy_with_parent, 2);
DEFINE_PRIM( hxgtk_window_is_active, 1);
DEFINE_PRIM( hxgtk_window_has_toplevel_focus, 1);
//DEFINE_PRIM( hxgtk_window_list_toplevels, 1);
//DEFINE_PRIM( hxgtk_window_add_mnemonic, 3);
//DEFINE_PRIM( hxgtk_window_remove_mnemonic, 3);
//DEFINE_PRIM( hxgtk_window_mnemonic_activate, 3);
//DEFINE_PRIM( hxgtk_window_activate_key, 2);
//DEFINE_PRIM( hxgtk_window_propagate_key_event, 2);
//DEFINE_PRIM( hxgtk_window_get_default_widget, 1);
DEFINE_PRIM( hxgtk_window_present, 1);
DEFINE_PRIM( hxgtk_window_present_with_time, 2);
DEFINE_PRIM( hxgtk_window_iconify, 1);
DEFINE_PRIM( hxgtk_window_deiconify, 1);
DEFINE_PRIM( hxgtk_window_stick, 1);
DEFINE_PRIM( hxgtk_window_unstick, 1);
DEFINE_PRIM( hxgtk_window_maximize, 1);
DEFINE_PRIM( hxgtk_window_unmaximize, 1);
DEFINE_PRIM( hxgtk_window_fullscreen, 1);
DEFINE_PRIM( hxgtk_window_unfullscreen, 1);
DEFINE_PRIM( hxgtk_window_set_keep_above, 2);
DEFINE_PRIM( hxgtk_window_set_keep_below, 2);
//DEFINE_PRIM( hxgtk_window_begin_resize_drag, 6);
//DEFINE_PRIM( hxgtk_window_begin_move_drag, 6);
//DEFINE_PRIM( hxgtk_window_has_group, 1);
//DEFINE_PRIM( hxgtk_window_move, 3);
//DEFINE_PRIM( hxgtk_window_hxgtk_parse_geometry, 2);
////DEFINE_PRIM( hxgtk_window_reshow_with_initial_size, 1);
DEFINE_PRIM( hxgtk_window_resize, 3);
//DEFINE_PRIM( hxgtk_window_resize_to_geometry, 3);
//DEFINE_PRIM( hxgtk_window_get_default_icon_list, 1);
//DEFINE_PRIM( hxgtk_window_set_default_icon_from_file, 3);
DEFINE_PRIM( hxgtk_window_get_icon_name, 1);
DEFINE_PRIM( hxgtk_window_set_icon_name, 2);
DEFINE_PRIM( hxgtk_window_get_opacity, 1);
DEFINE_PRIM( hxgtk_window_set_opacity, 2);
//DEFINE_PRIM( hxgtk_window_set_auto_startup_notification, 2);
///////DEFINE_PRIM( hxgtk_window_resize_grip_is_visible, 1);
///////////DEFINE_PRIM( hxgtk_window_get_resize_grip_area, 2);
////////////DEFINE_PRIM( hxgtk_window_set_has_user_ref_count, 2);
