package g;

class Timer {
	
	var  __i : Void;
	
	public function new( time_ms : Int ) {
		__i = _new( time_ms, _onTimer );
	}
	
	public dynamic function run() {}
	
	public function stop() _stop(__i)
	
	public static function delay( f : Void->Void, time_ms : Int ) {
		var t = new Timer(time_ms);
		t.run = function() {
			t.stop();
			f();
		};
		return t;
	}
	
	function _onTimer() {
		run();
	}
	
	public static inline function stamp() : Float {
		#if neko
		return neko.Sys.time();
		#elseif cpp
		return untyped __global__.__time_stamp();
		#end
	}
	
	static var _new = neko.Lib.load( "gtk", "hxg_timer_new", 2 );
	static var _stop = x( "stop" );
	
	static inline function x( f : String, n : Int = 0 ) : Dynamic
		return neko.Lib.load( "gtk", "hxg_timer_"+f, n+1 )
	
}
