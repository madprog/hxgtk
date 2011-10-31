package gtk;

class Lib {
	
	public static inline function init() : Bool return _init()
	public static inline function run() : Bool return _run()
	public static inline function quit() : Bool return _quit()
	
	public static inline function load( f : String, args : Int = 0 ) : Dynamic {
		#if cpp
		return cpp.Lib.load( "gtk", "hxgtk_"+f, args );
		#elseif neko
		return neko.Lib.load( "gtk", "hxgtk_"+f, args );
		#end
	}
	
	static var _init = load( "init" );
	static var _run = load( "run" );
	static var _quit = load( "quit" );
	
}
