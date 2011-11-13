package gtk;

class Lib {
	
	public static inline function isMainThread() : Bool return _is_main_thread()
	public static inline function main() _main()
	public static inline function quit() _quit()
	public static inline function sync(f:Void->Void) _sync(f)
	
	public static inline function load( f : String, args : Int = 0 ) : Dynamic {
		#if cpp
		return cpp.Lib.load( "gtk", "hxgtk_"+f, args );
		#elseif neko
		return neko.Lib.load( "gtk", "hxgtk_"+f, args );
		#end
	}
	
	static var _is_main_thread = load("is_main",0);
	static var _main = load( "main" );
	static var _quit = load( "quit" );
	static var _sync = load("sync",1);
	
}
