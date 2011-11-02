package gtk;

enum WindowType {
	toplevel;
	popup;
}

enum WindowPosition {
	none;
	center;
	mouse;
	center_always;
	center_parent;
}

class Window {
	
	public var title(getTitle,setTitle) : String;
	public var size(getSize,null) : {width:Int,height:Int};
	public var resizeable(getResizeable,setResizeable) : Bool;
	public var modal(getModal,setModal) : Bool;
	public var decorated(getDecorated,setDecorated) : Bool;
	public var deletable(getDeleteable,setDeleteable) : Bool;
	//public var acceptFocus(getAcceptFocus,setAcceptFocus) : Bool;
	public var role(getRole,setRole) : String;
	public var windowType(getWindowType,null) : WindowType;
	//public var screen(getScreen,setScreen) : Screen;
	public var destroyWithParent(getDestroyWithParent,setDestroyWithParent) : Bool;
	public var iconName(getIconName,setIconName) : String;
	public var opacity(getOpacity,setOpacity) : Float;
	
	var __i : Void;
	
	public function new( title : String, width : Int = 320, height : Int = 240 ) {
		__i = _constructor( untyped title.__s, width, height, handleClose );
	}
	
	function handleClose() {
		trace("TODO handleClose");
	}
	
	inline function getTitle() : String return _get_title(__i)
	inline function setTitle(v:String) return _set_title(__i,untyped v.__s)
	inline function getSize() : {width:Int,height:Int} return _get_size(__i)
	inline function getResizeable() : Bool return _get_resizeable(__i)
	inline function setResizeable(v:Bool) : Bool return _set_resizeable(__i,v)
	inline function getModal() return _get_modal(__i)
	inline function setModal(v:Bool) return _set_modal(__i,v)
	inline function getDecorated() : Bool return _get_decorated(__i)
	inline function setDecorated(v:Bool) : Bool return _set_decorated(__i,v)
	inline function getDeleteable() : Bool return _get_deleteable(__i)
	inline function setDeleteable(v:Bool) : Bool return _set_deleteable(__i,v)
	inline function getRole() : String return _get_role(__i)
	inline function setRole(v:String) : String return _set_role(__i,untyped v.__s)
	inline function getWindowType() : WindowType return Type.createEnumIndex(WindowType,_get_window_type(__i))
	inline function getDestroyWithParent() : Bool return _get_destroy_with_parent(__i)
	inline function setDestroyWithParent(v:Bool) : Bool return _set_destroy_with_parent(__i,v)
	inline function getIconName() : String return _get_icon_name(__i)
	inline function setIconName(v:String) return _set_icon_name(__i,untyped v.__s)
	inline function getOpacity() : Float return _get_opacity(__i)
	inline function setOpacity(v:Float) return _set_opacity(__i,v)
	
	public inline function getDefaultSize() : {width:Int,height:Int} return _get_default_size(__i)
	public inline function setDefaultSize(x:Int,y:Int) return _set_default_size(__i,x,y)
	public inline function getPosition() : WindowPosition return _get_position(__i)
	public inline function setPosition(v:WindowPosition) _set_position(__i,Type.enumIndex(v))
	public inline function isActive() : Bool return _is_active(__i)
	public inline function hasToplevelFocus() : Bool return _has_toplevel_focus(__i)
	public inline function present() _present(__i)
	public inline function presentWithTime(timestamp:Int) _present_with_time(__i,timestamp)
	public inline function iconify() _iconify(__i)
	public inline function deiconify() _deiconify(__i)
	public inline function stick() _stick(__i)
	public inline function unstick() _unstick(__i)
	public inline function maximize() _maximize(__i)
	public inline function unmaximize() _unmaximize(__i)
	public inline function fullscreen() _fullscreen(__i)
	public inline function unfullscreen() _unfullscreen(__i)
	public inline function setKeepAbove() _set_keep_above(__i)
	public inline function setKeepBelow() _set_keep_below(__i)
	public inline function resize(w:Int,h:Int) _resize(__i,w,h)
	
	static var _constructor = gtk.Lib.load( "window_constructor", 4 );
	
	static var _get_title = x( "get_title" );
	static var _set_title = x( "set_title", 1 );
	static var _get_size = x( "get_size" );
	static var _get_resizeable = x( "get_resizeable" );
	static var _set_resizeable = x( "set_resizeable", 1 );
	static var _get_modal = x( "get_modal" );
	static var _set_modal = x( "set_modal", 1 );
	static var _get_decorated = x( "get_decorated" );
	static var _set_decorated = x( "set_decorated", 1 );
	static var _get_deleteable = x( "get_deleteable" );
	static var _set_deleteable = x( "set_deleteable", 1 );
	static var _get_role = x( "get_role" );
	static var _set_role = x( "set_role", 1 );
	static var _get_window_typ = x( "get_window_type" );
	static var _get_window_type = x( "get_window_type" );
	static var _get_default_size = x( "get_default_size" );
	static var _set_default_size = x( "set_default_size", 2 );
	static var _get_position = x( "get_position" );
	static var _set_position = x( "set_position", 1 );
	static var _get_destroy_with_parent = x( "get_destroy_with_parent" );
	static var _set_destroy_with_parent = x( "set_destroy_with_parent", 1 );
	static var _is_active = x( "is_active" );
	static var _has_toplevel_focus = x( "has_toplevel_focus" );
	static var _present = x( "present" );
	static var _present_with_time = x( "present" );
	static var _iconify = x( "iconify" );
	static var _deiconify = x( "deiconify" );
	static var _stick = x( "stick" );
	static var _unstick = x( "unstick" );
	static var _maximize = x( "maximize" );
	static var _unmaximize = x( "unmaximize" );
	static var _fullscreen = x( "fullscreen" );
	static var _unfullscreen = x( "unfullscreen" );
	static var _set_keep_above = x( "set_keep_above", 1 );
	static var _set_keep_below = x( "set_keep_below", 1 );
	static var _resize = x( "resize", 2 );
	static var _get_icon_name = x( "get_icon_name" );
	static var _set_icon_name = x( "set_icon_name", 1 );
	static var _get_opacity = x( "get_opacity" );
	static var _set_opacity = x( "set_opacity", 1 );
	
	static inline function x( f : String, n : Int = 0 ) : Dynamic return gtk.Lib.load( "window_"+f, n+1 )
	
}
